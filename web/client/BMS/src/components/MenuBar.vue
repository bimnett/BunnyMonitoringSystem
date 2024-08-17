<template>

    <div class="menuBar">

        <ul>
            <li><router-link to="/">Home</router-link></li>
            <li><router-link to="/nutrition">Nutrition</router-link></li>
        </ul>

    </div>

</template>


<script>

export default {

    name: 'MenuBar'
}

</script>



<style scoped>

.menuBar {
  height: 75px;
  background-color: #F0AF3F;
  text-align: center;
  display: flex;
  align-items: center;
  justify-content: center;
  font-family: 'Poppins', sans-serif;
}

ul {
  list-style-type: none;
  padding: 0;
  margin: 0;
  display: flex;
}

li {
  margin: 0 15px;
}

li a {
  color: #141422;
  text-decoration: none; /* Remove default underline from links */
  font-size: 18px;
  font-weight: 600; /* Make the text bold */
  position: relative; /* Necessary for the underline animation */
  display: inline-block;
}

li a::after {
  content: '';
  position: absolute;
  left: 50%;
  bottom: -3px; /* Adjust the position of the underline */
  width: 0;
  height: 2px; /* Thickness of the underline */
  background-color: #141422; /* Color of the underline */
  transition: width 0.3s ease, left 0.3s ease;
}

li a:hover::after {
  width: 100%;
  left: 0;
}


</style>