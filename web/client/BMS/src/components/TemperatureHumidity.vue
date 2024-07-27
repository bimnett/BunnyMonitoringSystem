<template>
    
    <div id="environmentData">

      <div id="temperature"> {{ temperature }} °C</div>
      <div id="humidity"> {{ humidity }}% </div> 

    </div>
  

</template>


<script>

export default {

  data() {

    return {

      temperature: null,
      humidity: null
    }
  },

  mounted() {

    this.setupWebSocket();
  },

  methods: {
    setupWebSocket() {

        const ws = new WebSocket('ws://localhost:3000');
        
        ws.onmessage = (event) => {

            const { topic, message } = JSON.parse(event.data);

            if (topic === 'bms/environment/temperature') {
                this.temperature = message;
            } else if (topic === 'bms/environment/humidity') {
                this.humidity = message;
            }
        };
        
        ws.onerror = (error) => {
            console.error("WebSocket error:", error);
        };
        
        ws.onclose = () => {
            console.log("WebSocket connection closed.");
        };
    }
  },

  name: 'TemperatureHumidity'
}

</script>


<style scoped>

  #temperature, #humidity {

    text-align: center;
    caret-color: transparent;
    margin-right: 20px;
  }

  #environmentData {

    display: flex;
    justify-content: center;
    align-items: center;
  }

</style>