<template>
  <div id="app">
    <banner></banner>
    <menus :menu="menu" :remove="RemoveList"></menus>
    <add-menu :add="AddList"></add-menu>
  </div>
</template>

<script>
import Banner from './components/Banner'
import Menus from './components/Menus'
import AddMenu from './components/AddMenu'

export default {
  data () {
    return {
      menu: []
    }
  },
  components: {
    Banner,
    Menus,
    AddMenu
  },
  methods: {
    AddList: function (name) {
      var newData = {
        name: name
      }
      this.menu.push(newData)
    },
    RemoveList: function (index) {
      this.menu.splice(index, 1)
    }
  }
}
</script>

<style>
html {
  height: 100%;
}

body {
  display: flex;
  align-items: center;
  justify-content: center;
  height: 100%;
}

#app {
  color: #2c3e50;
  margin-top: -100px;
  max-width: 600px;
  font-family: Source Sans Pro, Helvetica, sans-serif;
  text-align: center;
}

#app a {
  color: #42b983;
  text-decoration: none;
}

.logo {
  width: 100px;
  height: 100px
}
</style>
