import { ref, onMounted } from 'vue'

export function useEnvironmentData() {
  const temperature = ref(null)
  const humidity = ref(null)

  function setupWebSocket() {
    const ws = new WebSocket('ws://localhost:3000')
    
    ws.onmessage = (event) => {
      const { topic, message } = JSON.parse(event.data)
      if (topic === 'bms/environment/temperature') {
        temperature.value = message
      } else if (topic === 'bms/environment/humidity') {
        humidity.value = message
      }
    }
    
    ws.onerror = (error) => {
      console.error("WebSocket error:", error)
    }
    
    ws.onclose = () => {
      console.log("WebSocket connection closed.")
    }
  }

  onMounted(() => {
    setupWebSocket()
  })

  return {
    temperature,
    humidity
  }
}