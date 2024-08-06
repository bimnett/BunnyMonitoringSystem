<template>

  <div id="app">
    
      <router-view></router-view>

  </div>

</template>


<script>

import HomeView from './views/HomeView.vue';

export default {

  name: 'App',

  components: {
    HomeView
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