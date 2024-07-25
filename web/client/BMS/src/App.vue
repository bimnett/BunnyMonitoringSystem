<template>

    <div id="app">
        <nav>
            <router-link to="/">Home</router-link>
        </nav>
        <router-view></router-view>
    </div>

</template>


<script>

export default {
  name: 'App'
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
  align-items: center;
  height: 100vh; /* Ensure the app takes the full viewport height */
}

nav {
  display: flex;
  margin-top: 20px;
}

nav a {
  text-decoration: none;
  color: orange;
}

a.router-link-active {
  font-weight: bold;
}
</style>
