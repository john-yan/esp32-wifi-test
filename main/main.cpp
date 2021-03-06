/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "esp32-wifi.h"
#include "nvs_flash.h"

static Wifi wifi;

void ReadyCallback(void*) {
  printf("wifi is ready.\n");
  fflush(stdout);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  esp_restart();
}

extern "C" void app_main(void) {
  //Initialize NVS
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  wifi.onReady(ReadyCallback, NULL);
  wifi.init();
}
