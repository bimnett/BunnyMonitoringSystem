<template>

  <div id="app">
    
      <MenuBar />
      <router-view></router-view>

  </div>

</template>


<script>

import MenuBar from './components/MenuBar.vue'

export default {

  name: 'App',

  components: {
    MenuBar,
  }
}

</script>


<style>
body {
margin: 0;
padding: 0;
background-color: #1e1e2f;
}
</style>