#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ps3.h"
#include "esp_system.h"
#include "nooch_mqtt_event_handler.h"

#define TAG_BT "PS3 Controller"

void controller_event_cb(ps3_t ps3, ps3_event_t event);