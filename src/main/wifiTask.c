#include "config.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include <esp_wifi_types_generic.h>

static const char *TAG = "WIFI";

static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data) {
  if (event_base == WIFI_EVENT) {
    switch (event_id) {
    case WIFI_EVENT_STA_START:
      ESP_LOGI(TAG, "STA_START");
      break;

    case WIFI_EVENT_STA_CONNECTED:
      ESP_LOGI(TAG, "CONNECTED");
      break;

    case WIFI_EVENT_STA_DISCONNECTED: {
      wifi_event_sta_disconnected_t *event = event_data;
      ESP_LOGI(TAG, "DISCONNECTED, reason=%d", event->reason);
      break;
    }
    }
  }

  if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {

    ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;

    ESP_LOGI(TAG, "Got IP: " IPSTR, IP2STR(&event->ip_info.ip));
  }
}

// Handles WiFi connection
void wifiTask(void *pvParameters) {

  ESP_LOGI(TAG, "=====================");
  ESP_LOGI(TAG, "WiFi Task succesfully created");

  ESP_ERROR_CHECK(esp_netif_init());
  ESP_ERROR_CHECK(esp_event_loop_create_default());

  esp_netif_create_default_wifi_sta();

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&cfg));

  ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID,
                                             &wifi_event_handler, NULL));

  ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP,
                                             &wifi_event_handler, NULL));

  wifi_config_t wifi_config = {
      .sta =
          {
              .ssid = WIFI_SSID,
              .password = WIFI_PASSWORD,
          },
  };

  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
  ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
  ESP_ERROR_CHECK(esp_wifi_start());

  ESP_LOGI(TAG, "Connecting to \"%s\"...", WIFI_SSID);
  ESP_ERROR_CHECK(esp_wifi_connect());

  while (1) {
    vTaskDelay(pdMS_TO_TICKS(200000));
  }
}
