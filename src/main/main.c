#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
static const char *TAG = "MAIN";

void startingUp(void) {

  ESP_LOGI(TAG, "=====================");
  ESP_LOGI(TAG, "Start");
}

void app_main(void) { startingUp(); }
