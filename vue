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

 vm (short for ViewModel)
accept the same options object (except for a few root-specific options)
vm.a = 2
data.a // => 2
// ... and vice-versa
data.a = 3
vm.a // => 3
data are only reactive if they existed when the instance was created

Vue properties and methods:
    $
    vm.$data === data
    vm.$el === document.getElementByID('example')

// $watch is an instance method
vm.$watch('a', function(newValue, oldValue) {
    // `vm.a` changes
}

data observation
compile the template
mount the instance to the DOM
update DOM when data changes

lifecycle hooks

created: function() {
    // this.a
}

created, mounted, updated, destroyed

Don't arrow function, arrow functions bound to parent context,
this will not be Vue instance

beforeCreate
created

beforeMount
mounted

beforeUpdate
updated

beforeDestroy
destroyed


<span v-once>{{ neverChange }}</span>
<div v-html="rawHtml"></div>

# Attributes
v-bind

JavaScript Expression:
{{ ok ? 'YES' : 'NO' }}
v-bind:id="'list-' + id"
whitelist of globals

Directives
a single JavaScript expression(except v-for)

# Arguments
v-bind:href="url"
v-on:click="listneToDOMEvent"

#Modifiers
v-on:submit.prevent="onSubmit"
v-on, v-model

v-bind ,
v-on, @

Computed Properties

computed: {
}
vm.reverseMessage deponds on vm.message

Computed Caching vs Methods
computed properties are cached based on their dependencies.


Watched Property
it is often a better idea to use a computed property rather than an imperative watch callback

Computed properties are by default getter-only, but you can also provide a setter when you need it

computed: {
    fullName: {
        get: function() {
        },
        set: function(newValue) {
        }
    }
}

f
perform asynchronous or expensive operations in response to changing data

vm.$watch API

v-bind:class="{ active: isActive }"
class="static" v-bind:class="{}"

v-bind:class="classObject"
v-bind:class="[activeClass, errorClass]"
v-bind:class="[isActive ? activeClass : '', errorClass]"
v-bind:class="[{ active: isActive }, errorClass]"

When you use the class attribute on a custom component, those classes will be added to the component’s root element. Existing classes on this element will not be overwritten

v-bind:style
You can use either camelCase or kebab-case (use quotes with kebab-case) for the CSS property names

vendor prefixes

<div v-bind:style="{ display: ['-webkit-box', '-ms-flexbox', 'flex'] }"></div>


{{#if ok}}<h1>Yes</h1>{{/if}}
<h1 v-if="ok">yes</h1>
<h1 v-else>no</h1>

toggle more than one element
<template v-if="ok">
    <h1>Title</h1>
    <p>Paragraph</p>
    <p>Paragraph</p>
</template>

v-else-if
key="username-input"
key="email-input"

<h1 v-show="ok">Hello!</h1>, controll display
no support template and v-else

v-if: lazy destroyed and re-created
v-if has higher toggle costs 
while v-show has higher initial render costs(toggle选此)

<li v-for="(item, index) in items">
<div v-for="item of items"></div>
<div v-for="(value, key) in object">
<div v-for="(value, key, index) in object">
Object.keys()
<div v-for="item in items" :key="item.id">
<input placeholder="Enter your username" key="username-input">

item.message.match(/Foo/)


Caveats:
    vm.items[indexOfItem] = newValue
        Vue.set(example1.items, indexOfItem, newValue)
        example1.items.splice(indexOfItem, 1, newValue)
    vm.items.length = newLength
        example.items.splice(newLength)

add reactive properties to a nested object using the Vue.set(object, key, value)
Vue.set(vm.userProfile, 'age', 27)
vm.$set == Vue.set
this.$set(this.userProfile, 'age', 27)

Object.assign(), _.extend()
Object.assign(this.userProfile, {
  age: 27,
  favoriteColor: 'Vue Green'
})
this.userProfile = Object.assign({}, this.userProfile, {
  age: 27,
  favoriteColor: 'Vue Green'
})

this.numbers.filter

<span v-for="n in 10">{{ n }} </span>
<template v-for="item in items">
<li v-for="todo in todos" v-if="!todo.isComplete">
  {{ todo }}
</li>

<my-component v-for="item in items" :key="item.id"></my-component>

<my-component
  v-for="(item, index) in items"
  v-bind:item="item"
  v-bind:index="index"
  v-bind:key="item.id"
></my-component>

v-on:remove="todos.splice(index, 1)"
$emit(\'remove\')
if (event) {
    event.target.tagName
}
warn('Form cannot be submitted yet.', $event)
event.preventDefault()
event.stopPropagation()

.stop
.prevent
.capture
.self
.once

v-on:keyup.13="submit"
v-on:keyup.enter="submit"
@keyup.enter="submit"

.enter
.tab
.delete ("Delete" and "Backspace")
.esc
.space
.up
.down
.left
.right

// enable v-on:keyup.f1
Vue.config.keyCodes.f1 = 112

.ctrl
.alt
.shift
.meta

<!-- Alt + C -->
<input @keyup.alt.67="clear">

<!-- Ctrl + Click -->
<div @click.ctrl="doSomething">Do something</div>

.middle

















