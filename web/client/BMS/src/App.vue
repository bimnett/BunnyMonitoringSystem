<template>

    <div id="app">

        <nav>
            <router-link to="/">Home</router-link>
        </nav>
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
body, html {
  height: 100%;
  margin: 0;
}

#app {
  display: flex;
  flex-direction: column;
  height: 100vh; /* Ensure the app takes the full viewport height */
}

nav {
  height: 60px; /* Set the height to 60px */
  background-color: orange; /* Set the background color to orange */
  display: flex;
  align-items: center;
  justify-content: center; /* Center the content horizontally */
  margin-bottom: 40px;
}

nav a {
  text-decoration: none;
  color: black; /* Change the link color to white for better contrast */
}

a.router-link-active {
  font-weight: bold;
}
</style>
