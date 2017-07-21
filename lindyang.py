from bisect import bisect_left


class LabelSentenceWordIndexFixer(object):
    MISMATCH_TAV = 1  # 1 << 0
    MISMATCH_PREATTR = 2  # 1 << 1
    MISMATCH_BAD_ZERO = 4  # 1 << 2
    UNKNOWN_ENTITY = -10000
    OPERATOR_MAP = {
        "+": "+", "-": "--",
        "x": "x", "/": "//",
        "=": "=", "≈": "≈",
        '>': '<', '<': '>',
        '>=': '<=', '<=': '>=',
        "GR": "~GR", "DR": "~DR", "CGR": "~CGR",
    }
    OPERATOR_SET = {
        '+', '-', '--', 'x', '/', '//',
        '=', '≈', '>', '<', '>=', '<=',
        'GR', '~GR', 'DR', '~DR', 'CGR', '~CGR'
    }
    TYP_MAP = {
        1: 'times', 2: 'preattributes', 3: 'attributes', 4: 'values'
    }

    def __init__(self, data: dict, clear_prea: bool=True):
        self._data = data
        self._clear_prea = clear_prea
        self.mismatch_flag = 0
        self.words = []
        self.positions = [0]
        self.len_words = 0
        self._next_relation_index = 0
        self._paw_relations = []
        self._paw_map = {}

    @property
    def data(self) -> dict:
        return self._data

    def fix(self) -> dict:
        self.fill_words()
        if self._clear_prea:
            self.remove_unused_prea()

        self.fix_word_index_for_tav(self._data["times"])  # T
        self.fix_word_index_for_p(self._data["preattributes"])  # P
        self.fix_word_index_for_tav(self._data["attributes"])  # A
        self.fix_word_index_for_tav(self._data["values"])  # V

        self.fix_index_for_tuple_tav(self._data["quadruples"])
        self.fix_index_for_relation(self._data["relations"])

        self.fix_word_index_for_relation(self._data["relations"])  # R

        self.fix_relation_left_right_order()
        return self._data

    def fill_words(self):
        while self._data["words"][-1] in ['?', '@']:  # IndexError
            self._data["words"].pop()
        self.words = self._data["words"]
        self.len_words = len(self.words)
        # self.positions = [0]
        for i, word in enumerate(self.words, 1):
            self.positions.append(self.positions[i - 1] + len(word))

    def remove_unused_prea(self):
        preattributes = {}
        if self._data["quadruples"]:
            for quad in self._data["quadruples"]:
                for key in map(str, quad.get("preattributes", [])):
                    preattributes[key] = self._data["preattributes"][key]
        else:
            for rel in self._data["relations"]:
                for side in ["left", "right"]:
                    if rel[side] < 0 and (-rel[side]) & 0xF == 2:
                        key = str((-rel[side]) >> 4)
                        preattributes[key] = self._data["preattributes"][key]
        # endif
        self._data["preattributes"] = preattributes

    def fix_word_index_for_tav(self, map_: dict):
        # word_index may not change. p.s. -1
        for val in map_.values():
            try:
                val['word_index'] = self.positions.index(val['position'])
            except ValueError:
                self.mismatch_flag |= self.MISMATCH_TAV
                break
            else:
                if val["value"] != self.words[val["word_index"]]:
                    self.mismatch_flag |= self.MISMATCH_TAV
                    break

    def _positions_index(self, position: int) -> int:
        # IndexError
        index = bisect_left(self.positions, position)
        # if index != self.len_words and self.positions[index] == position:
        if self.positions[index] == position:
            return index
        raise ValueError

    def fix_word_index_for_p(self, map_: dict):
        # "word_index": may not change. p.s. []
        for val in map_.values():
            try:
                start = self._positions_index(val['position'])
                end = self._positions_index(val['position'] + len(val['value']))
            except ValueError:
                self.mismatch_flag |= self.MISMATCH_PREATTR
                break
            else:
                if val['value'] == ''.join(self.words[start:end]):
                    val['word_index'] = list(range(start, end))
                else:
                    self.mismatch_flag |= self.MISMATCH_PREATTR
                    break

    def fix_index_for_tuple_tav(self, tuples):
        for quad in tuples:
            for key in ["time", "attribute", "value"]:
                if quad[key] == 0:
                    quad[key] = self.UNKNOWN_ENTITY

    def fix_index_for_relation(self, relations: list):
        if relations:
            offset = 3 * self.len_words
            if offset > min([val["index"] for val in relations]):
                for val in relations:
                    val["index"] += offset
                    for side in ['left', 'right']:
                        if val[side] > 0:
                            val[side] += offset

    def _make_paw_paw(self, word_index: list) -> int:
        left = word_index[0]  # IndexError
        for right in word_index[1:]:
            key = '{}:{}'.format(left, right)
            index = self._paw_map.get(key)
            if not index:
                self._paw_relations.append({
                    "index": self._next_relation_index, "operator": "paw&paw",
                    "left": left, "right": right
                })
                self._paw_map[key] = self._next_relation_index
                left = self._next_relation_index
                self._next_relation_index += 1
            else:
                left = index
        return left

    def _relation_side(self, relation: dict, side: str) -> bool:
        value = relation[side]
        if value < 0 and value != self.UNKNOWN_ENTITY:
            # key, typ = self.key_and_typ(_value)
            value = -value
            key, typ = str(value >> 4), value & 0xF
            try:
                word_index = self._data[self.TYP_MAP[typ]][key]['word_index']  # int(TAV) or list(P)
            except KeyError:
                word_index = -1
            if typ != 2:  # TAV
                relation[side] = word_index
            else:  # P
                relation[side] = self._make_paw_paw(word_index)
        elif value in [0, self.UNKNOWN_ENTITY]:
            if relation['operator'] == 't&a':
                relation[side] = self.UNKNOWN_ENTITY
            else:
                self.mismatch_flag |= self.MISMATCH_BAD_ZERO
                return False
        return True

    def fix_word_index_for_relation(self, relations: list):
        self._next_relation_index = self.len_words

        for relation in relations:
            if not self._relation_side(relation, 'left'):
                break
            if not self._relation_side(relation, 'right'):
                break

        self._data['relations'] = self._paw_relations + relations
        # for paw_relation in self._paw_relations:
        #   relations.insert(0, paw_relation)

    def __relation_with_word_nodes(self) -> list:
        _relations = [{"index": self.UNKNOWN_ENTITY, "operator": '', "left": -1, "right": -1, "level": -1, "word_indexes": []}]
        for i in range(self.len_words):
            _relations.append({"index": i, "operator": '', "left": -1, "right": -1, "level": -1, "word_indexes": [i]})
        return _relations + self._data["relations"]

    def _relation_add_word_index_level(self):
        """
        relation['word_index'] is all word in this relation, sorted
        level of a relation:
            start from quadruple, level = 1, each layer level + 1
        """
        relations = self.__relation_with_word_nodes()  # type: list
        relations_index_map = {relation["index"]: relation for relation in relations}
        relations_index_map[-1] = relations_index_map[self.len_words - 1]
        for relation in relations[self.len_words:]:
            word_indexes = relations_index_map[relation['left']]['word_indexes'] + \
                           relations_index_map[relation['right']]['word_indexes']
            word_indexes.sort()
            relation['word_indexes'] = word_indexes
            if relation['operator'] in {'t&a', 'p&v'}:
                relation['level'] = 1
            elif relation["operator"] in self.OPERATOR_SET:
                relation["level"] = max(
                    relations_index_map[relation["left"]]["level"],
                    relations_index_map[relation["right"]]["level"]
                ) + 1

    def _fix_relation_left_right_order(self):
        relations = self.__relation_with_word_nodes()
        relations_index_map = {relation["index"]: relation for relation in relations}
        relations_index_map[-1] = relations_index_map[self.len_words - 1]
        for relation in relations[self.len_words:]:
            if relation['operator']:
                left_node, right_node = relations_index_map[relation["left"]], relations_index_map[relation["right"]]
                if relation["operator"] in self.OPERATOR_MAP:
                    if left_node["level"] <= right_node["level"] and left_node["word_indexes"] >= right_node["word_indexes"]:
                        relation["left"], relation["right"] = relation["right"], relation["left"]
                        relation["operator"] = self.OPERATOR_MAP[relation["operator"]]
                elif relation["operator"] in ["paw&paw", "pa&pa"]:
                    if left_node["word_indexes"] > right_node["word_indexes"]:
                        relation["left"], relation["right"] = relation["right"], relation["left"]
        # end
        for relation in relations:
            relation.pop("level", 0)
            relation.pop("word_indexes", 0)

    def fix_relation_left_right_order(self):
        """
        对于 + - * / CGR paw&paw, pa&pa 这一类的关系(除了 pa&a, t&a, p&v 之外的所有关系)
        left 的 level一定要比 right的level大，如果两个一样大，那么left一定要在句子的左边. 什么是句子的左边：
            left有一堆 word_index lw=[1, 3, 5], right 有一堆word_index rw=[1,4,5], lw<rw说明left在句子左边.
        如果不满足要求，需要 调换left 和 right，并把 operator 变成 相反的 operator
        """
        self._relation_add_word_index_level()
        self._fix_relation_left_right_order()
