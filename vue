v-bind:title="message"
v-if="seen"
transition effects
v-for="todo in todos"
v-on:click="reverseMessage"
data: {}
methods: {
    // reverseMessage: function() {}
    reverseMessage() {}
}

message.split('').reverse().join('')

双向绑定
v-model directive that makes two-way binding between form input and app state a breeze
v-model 的更改也会更改 app 的数据

component is essentially a Vue instance with pre-defined options

Vue.component('todo-item', {
    props: ['todo'],   // parent pass data to
    template: '<li>{{ todo.text }}</li>'
})

<ol>
    <todo-item
        v-for="item in todos"
        v-bind:todo="item"
        v-bind:key="item.id"
    ></todo-item>
</ol>

props 通过bind传递

 Slot API, is
 cross-component data flow
 custom event communication
 build tool integrations


