<template>
  

</template>


<script>

export default {

  data() {

    return {

      temperature: null,
      humidity: null
    }
  },

  watch: {
    temperature(newValue) {
      this.$emit('temperature-update', newValue);
    },
    humidity(newValue) {
      this.$emit('humidity-update', newValue);
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