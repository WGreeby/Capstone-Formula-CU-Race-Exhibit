#include "nooch_ps3_event_handler.h"

void controller_event_cb(ps3_t ps3, ps3_event_t event){
    // if ( ps3.status.battery >= ps3_status_battery_high )
    //     ESP_LOGI(TAG_BT, "The controller still has sufficient battery charge");
    
    // if ( ps3.status.charging )
    //     ESP_LOGI(TAG_BT, "Controller is charging");
    if( ps3.analog.button.r2){
        // driveForward((uint32_t)ps3.analog.button.r2);
       // ESP_LOGI(TAG_BT, "Driving forward");
       // ESP_LOGI(TAG_BT, "%d",ps3.analog.button.r2);
    }
    if( ps3.button.l2){
        //driveBackward(ps3.button.l2);
        // ESP_LOGI(TAG_BT, "Driving backward");
    }
    if ( ps3.button.triangle )
        // ESP_LOGI(TAG_BT, "Currently pressing the trangle button");

    if ( ps3.analog.stick.lx < 0 ){
        //send_ps3_val(ps3.analog.stick.lx);
        // ESP_LOGI(TAG_BT, "%d", ps3.analog.stick.lx);
    }

    if ( event.button_down.cross ){
        ESP_LOGI(TAG_BT, "The user started pressing the X button");
        esp_mqtt_client_config_t mqtt_cfg = {
        //.broker.address.uri = CONFIG_BROKER_URL,
            .broker.address.hostname = "172.21.74.110",
            .broker.address.port = 1883,
            .broker.address.transport = MQTT_TRANSPORT_OVER_TCP,
        };
        esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
        uint32_t msg_id = esp_mqtt_client_publish(client, "boost", "1", 1, 0, 0);
        ESP_LOGI(TAG_BT, "%d", msg_id);
        //esp_mqtt_client_start(client);
        //esp_mqtt_client_disconnect(client);
        
    }
    if ( event.button_up.cross )
        ESP_LOGI(TAG_BT, "The user released the X button");

    // if ( event.analog_changed.stick.lx )
    
    //     ESP_LOGI(TAG, "The user has moved the left stick sideways");
    
    // if( ps3.status.charging)
    //     ESP_LOGI(TAG_BT, "The controller is charging");
}