<template>
  <div class="hello">
    <h1>AddMenu</h1>
    <input v-model="input" type="text">
    <button @click="add(input)">Add</button>
  </div>
</template>

<script>
export default {
  props: ['add'],
  data () {
    return {
      input: ''
    }
  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
h1 {
  color: #42b983;
}
</style>
