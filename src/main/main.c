#include <stdio.h>

#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "MAIN";

// --------------------------
// Pins 

void startingUp(void)
{
    ESP_LOGI(TAG, "=====================");
    ESP_LOGI(TAG, "Starting Up!");
}

// --------------------------
// Tasks
// Handles WiFi connection
void wifiTask(void *pvParameters)
{
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Controls LED status indications
// Blink table:
// | Blinks | Meaning |
// |--------|---------|
// |   x    |    x    |
void ledTask(void *pvParameters)
{
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Measures humidity and temperature
void measureTask(void *pvParameters)
{
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// --------------------------
// Entry Point
void app_main(void)
{
    startingUp();

    // Create application tasks
    // xTaskCreate(task_function, task_name, stack_size, parameters, priority, task_handle);
    xTaskCreate(wifiTask, "WiFi Task", 4096, NULL, 4, NULL);
    xTaskCreate(measureTask, "Measure Task", 4096, NULL, 3, NULL);
    xTaskCreate(ledTask, "LED Task", 2048, NULL, 2, NULL);
}
