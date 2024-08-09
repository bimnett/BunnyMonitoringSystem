import { ref, onMounted } from 'vue'
import { AWS_EC2_PUB_IP, PORT } from '@/assets/client_secrets.js'

export function useEnvironmentData() {
  const temperature = ref(null)
  const humidity = ref(null)

  function setupWebSocket() {
    const ws = new WebSocket(`ws://${AWS_EC2_PUB_IP}:${PORT}`);
    
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