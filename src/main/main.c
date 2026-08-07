#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include <stdio.h>

#include "config.h"
#include "information.h"
#include "wifiTask.h"

static const char *TAG = "MAIN";

#define shortDelay 500
#define longDelay 1000

// --------------------------
// Pins
#define LED_GPIO GPIO_NUM_0

// --------------------------
// Tasks

// Controls LED status indications
// See blink table

QueueHandle_t ledQueue;
void ledTask(void *pvParameters) {
  gpio_config_t io_conf = {
      .pin_bit_mask = (1ULL << LED_GPIO),
      .mode = GPIO_MODE_OUTPUT,
      .pull_up_en = GPIO_PULLUP_DISABLE,
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .intr_type = GPIO_INTR_DISABLE,
  };

  gpio_config(&io_conf);

  ESP_LOGI(TAG, "=====================");
  ESP_LOGI(TAG, "Led Task succesfully created");

  int info;

  while (1) {
    if (xQueueReceive(ledQueue, &info, portMAX_DELAY)) {
      ESP_LOGI(TAG, "%s", InformationMatrix[info].message);
      for (int i = 0; i < InformationMatrix[info].shortBip; i++) {
        gpio_set_level(LED_GPIO, 1);
        vTaskDelay(pdMS_TO_TICKS(shortDelay));
        gpio_set_level(LED_GPIO, 0);
        vTaskDelay(pdMS_TO_TICKS(shortDelay));
      }
      vTaskDelay(pdMS_TO_TICKS(2000));

      for (int i = 0; i < InformationMatrix[info].longBip; i++) {
        gpio_set_level(LED_GPIO, 1);
        vTaskDelay(pdMS_TO_TICKS(longDelay));
        gpio_set_level(LED_GPIO, 0);
        vTaskDelay(pdMS_TO_TICKS(longDelay));
      }
    }
  }
}

// Measures humidity and temperature
void measureTask(void *pvParameters) {
  while (1) {
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

// --------------------------
// Entry Point
void app_main(void) {

  // Initialize NVS
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
      ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  // Create application tasks
  // xTaskCreate(task_function, task_name, stack_size, parameters, priority,
  // task_handle);
  ESP_LOGI(TAG, "%s", WIFI_SSID);
  ESP_LOGI(TAG, "%s", WIFI_PASSWORD);

  ledQueue = xQueueCreate(5, sizeof(int));
  xTaskCreate(ledTask, "LED Task", 2048, NULL, 2, NULL);

  xTaskCreate(wifiTask, "WiFi Task", 4096, NULL, 4, NULL);
  xTaskCreate(measureTask, "Measure Task", 4096, NULL, 3, NULL);

  int info = 0;
  xQueueSend(ledQueue, &info, portMAX_DELAY);
}
