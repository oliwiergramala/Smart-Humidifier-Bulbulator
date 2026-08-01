#include <stdio.h>

#include "driver/gpio.h"
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "MAIN";

// --------------------------
// Pins 

#define LED_GPIO GPIO_NUM_0


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


typedef struct{ 
	int shortBip;
	int longBip;
	char message[50];
}LEDInformation;

// Controls LED status indications
// Blink table:
// | Short Blinks | Longs Blinks |  Message |

LEDInformation InformationMatrix[] = {
	{1, 0, "Ok"},
	{3, 3, "Wi-Fi Connection error"},
	{2, 0, "Sending data"},
	{2, 3, "Measuring error"},
	{5, 1, "PANIC"}
};

void ledTask(void *pvParameters)
{
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
    while (1)
    {
	ESP_LOGI(TAG, "message=%s", InformationMatrix[1].message);
        gpio_set_level(LED_GPIO, 1); // ON
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_set_level(LED_GPIO, 0); // OFF
        vTaskDelay(pdMS_TO_TICKS(500));
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
void startingUp(void)
{
    ESP_LOGI(TAG, "=====================");
    ESP_LOGI(TAG, "Starting Up!");
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
