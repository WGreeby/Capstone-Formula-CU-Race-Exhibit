#include "driver/gpio.h"
#include "esp_partition.h"
#include "esp_tls.h"
#include "esp_ota_ops.h"
#include <sys/param.h>
#include "esp_mac.h"
#include "sdkconfig.h"
#include "nooch_mqtt_event_handler.h"
#include "nooch_wifi_main.h"
#include "nooch_ps3_event_handler.h"
#include "management_buffer.h"
#include "drive_control.h"
#include "driver/adc.h"
#include "driver/ledc.h"


// #include <stdio.h>
// #include <stdint.h>
// #include <stddef.h>
// #include <string.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
//#include "freertos/event_groups.h"
// #include "freertos/semphr.h"
// #include "freertos/queue.h"
// #include "esp_log.h"
// #include "esp_system.h"
// #include "esp_wifi.h"
// #include "esp_event.h"
// #include "esp_netif.h"
// #include "protocol_examples_common.h"
// #include "nvs_flash.h"
// #include "lwip/err.h"
// #include "lwip/sys.h"
// #include "lwip/sockets.h"
// #include "lwip/dns.h"
// #include "lwip/netdb.h"
// #include "mqtt_client.h"
//static const char *TAG = "example";
/* Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
// void send_ps3_val(int8_t data){
//     int msg_id;
//     esp_mqtt_client_config_t mqtt_cfg = {
//         //.broker.address.uri = CONFIG_BROKER_URL,
//         .broker.address.hostname = "172.21.74.110",
//         .broker.address.port = 1883,
//         .broker.address.transport = MQTT_TRANSPORT_OVER_TCP,
//     };
//     esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
//     esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
//     esp_mqtt_client_start(client);
//     // esp_mqtt_client_register_event(client, MQTT_EVENT_SUBSCRIBED, mqtt_event_handler, NULL);
// }


void app_main(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    init_hw();
    // ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
    // wifi_init_sta();
    // mqtt_app_start();
  //PCB REV1 78:21:84:d6:f6:5a            PCB REV 1
  //Tim a4:cf:12:04:cc:ca
  //Gannon a4:cf:12:04:d1:9e
    //uint8_t gannon_mac_addr[8] = { 0xa4, 0xcf, 0x12, 0x04, 0xcc, 0xca};
    uint8_t pcbrev1_mac_addr[8] = { 0x78, 0x21, 0x84, 0xd6, 0xf6, 0x5a };
    //uint8_t gannon_mac_addr[8] = { 0xa4, 0xcf, 0x12, 0x04, 0xd1, 0x9e};
    ps3SetBluetoothMacAddress( pcbrev1_mac_addr );
    ps3SetEventCallback(controller_event_cb);
    ps3Init();
    
    while(!ps3IsConnected()){
        vTaskDelay(10 / portTICK_PERIOD_MS);
        //ESP_LOGI(TAG,"HERE");
    }
    ESP_LOGI("","HERE");
    ps3SetLed(1);

    while (1) {
        drive(0);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}