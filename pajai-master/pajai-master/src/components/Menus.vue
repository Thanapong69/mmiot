<template>
<div class="hello">
  <h1>Menu</h1>
  <!-- <v-for="list in menu"> -->
    <list v-for="list in menu" :list="list" :remove="remove" :index="$index"></list>
  </div>
</div>
</template>

<script>
import List from './List'
export default {
  props: ['menu', 'remove'],
  data () {
    return {}
  },
  components: {
    List
  }
}
</script>

<style scoped>
h1 {
  color: #42b983;
}
</style>
