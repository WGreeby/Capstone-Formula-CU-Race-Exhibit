#include "drive_control.h"

#define SAMPLE_CNT 1
#define LEDC_GPIO_LEFT 27
#define LEDC_GPIO_RIGHT 26
#define LEDC_GPIO_FWD 25
#define LEDC_GPIO_BKWD 33

extern volatile ps3_t ps3;

static const adc1_channel_t adc_channel = ADC_CHANNEL_4;
static ledc_channel_config_t ledc_channel_steer_left;
static ledc_channel_config_t ledc_channel_steer_right;
static ledc_channel_config_t ledc_channel_forward;
static ledc_channel_config_t ledc_channel_backward;
static const char* TAG3 = "MyModule";

void init_hw(void) {
    adc1_config_width(ADC_WIDTH_BIT_10);
    adc1_config_channel_atten(adc_channel, ADC_ATTEN_DB_11);

    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_10_BIT,
        .freq_hz = 1000,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .clk_cfg = LEDC_AUTO_CLK,
    };

    ledc_timer_config(&ledc_timer);
    ledc_channel_steer_left.channel = LEDC_CHANNEL_0;
    ledc_channel_steer_left.duty = 0;
    ledc_channel_steer_left.gpio_num = LEDC_GPIO_LEFT;
    ledc_channel_steer_left.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel_steer_left.hpoint = 0;
    ledc_channel_steer_left.timer_sel = LEDC_TIMER_0;
    ledc_channel_config(&ledc_channel_steer_left);
    ledc_channel_steer_right.channel = LEDC_CHANNEL_1;
    ledc_channel_steer_right.duty = 0;
    ledc_channel_steer_right.gpio_num = LEDC_GPIO_RIGHT;
    ledc_channel_steer_right.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel_steer_right.hpoint = 0;
    ledc_channel_steer_right.timer_sel = LEDC_TIMER_0;
    ledc_channel_config(&ledc_channel_steer_right);
    ledc_channel_forward.channel = LEDC_CHANNEL_2;
    ledc_channel_forward.duty = 0;
    ledc_channel_forward.gpio_num = LEDC_GPIO_FWD;
    ledc_channel_forward.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel_forward.hpoint = 0;
    ledc_channel_forward.timer_sel = LEDC_TIMER_0;
    ledc_channel_config(&ledc_channel_forward);
    ledc_channel_backward.channel = LEDC_CHANNEL_3;
    ledc_channel_backward.duty = 0;
    ledc_channel_backward.gpio_num = LEDC_GPIO_BKWD;
    ledc_channel_backward.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel_backward.hpoint = 0;
    ledc_channel_backward.timer_sel = LEDC_TIMER_0;
    ledc_channel_config(&ledc_channel_backward);
}

void drive(uint32_t adc_val){
        uint32_t adc_val2 =0;
        for (int i = 0; i < SAMPLE_CNT; ++i) {
                adc_val2 += adc1_get_raw(adc_channel);
        }
        adc_val2 /= SAMPLE_CNT;
        // ESP_LOGI(TAG3, "Current ADC Value: %lu", adc_val2);

        //ESP_LOGI(TAG3, "Current stick Value: %d", ps3.analog.stick.lx);

        uint32_t target_adc = 0;
        if(ps3.analog.stick.lx >= -64){
                target_adc = 615 - (((int32_t)ps3.analog.stick.lx+64)*200/191);
        }
        else{
                target_adc = 415 - (((int32_t)ps3.analog.stick.lx+128)*65/64);
        }

        if(ps3.analog.stick.lx == 64){
                target_adc = 482;
        }

        // ESP_LOGI(TAG3, "Target adc Value: %lu", target_adc);

        if(adc_val2 < (target_adc - 20)){

                ledc_set_duty(ledc_channel_steer_right.speed_mode, ledc_channel_steer_right.channel, 60);
                ledc_update_duty(ledc_channel_steer_right.speed_mode, ledc_channel_steer_right.channel);  
        
                ledc_set_duty(ledc_channel_steer_left.speed_mode, ledc_channel_steer_left.channel, 0);
                ledc_update_duty(ledc_channel_steer_left.speed_mode, ledc_channel_steer_left.channel);  
        }
        else if(adc_val2 > (target_adc + 20)){

                ledc_set_duty(ledc_channel_steer_right.speed_mode, ledc_channel_steer_right.channel, 0);
                ledc_update_duty(ledc_channel_steer_right.speed_mode, ledc_channel_steer_right.channel);  
        
                ledc_set_duty(ledc_channel_steer_left.speed_mode, ledc_channel_steer_left.channel, 60);
                ledc_update_duty(ledc_channel_steer_left.speed_mode, ledc_channel_steer_left.channel);  
        }
        else{
                ledc_set_duty(ledc_channel_steer_right.speed_mode, ledc_channel_steer_right.channel, 0);
                ledc_update_duty(ledc_channel_steer_right.speed_mode, ledc_channel_steer_right.channel);  
        
                ledc_set_duty(ledc_channel_steer_left.speed_mode, ledc_channel_steer_left.channel, 0);
                ledc_update_duty(ledc_channel_steer_left.speed_mode, ledc_channel_steer_left.channel);  
        }

        if(ps3.analog.button.r2){

                ledc_set_duty(ledc_channel_forward.speed_mode, ledc_channel_forward.channel, 2 * (uint16_t)ps3.analog.button.r2);
                ledc_update_duty(ledc_channel_forward.speed_mode, ledc_channel_forward.channel);

                ledc_set_duty(ledc_channel_backward.speed_mode, ledc_channel_backward.channel, 0);
                ledc_update_duty(ledc_channel_backward.speed_mode, ledc_channel_backward.channel);
        }
        else if(ps3.analog.button.l2){

                ledc_set_duty(ledc_channel_forward.speed_mode, ledc_channel_forward.channel, 0);
                ledc_update_duty(ledc_channel_forward.speed_mode, ledc_channel_forward.channel);

                ledc_set_duty(ledc_channel_backward.speed_mode, ledc_channel_backward.channel,  2 * (uint16_t)ps3.analog.button.l2);
                ledc_update_duty(ledc_channel_backward.speed_mode, ledc_channel_backward.channel);
        }
        else{
                ledc_set_duty(ledc_channel_forward.speed_mode, ledc_channel_forward.channel, 0);
                ledc_update_duty(ledc_channel_forward.speed_mode, ledc_channel_forward.channel);

                ledc_set_duty(ledc_channel_backward.speed_mode, ledc_channel_backward.channel, 0);
                ledc_update_duty(ledc_channel_backward.speed_mode, ledc_channel_backward.channel);
        }


        // ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, adc_val2);
        // ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
}

// void app_main(void) {
    
//     init_hw();

//     while(1) {
//         uint32_t adc_val =0;
//         for (int i = 0; i < SAMPLE_CNT; ++i) {
//             adc_val += adc1_get_raw(adc_channel);
//         }
//         adc_val /= SAMPLE_CNT;
//         ESP_LOGI(TAG, "Current ADC Value: %lu", adc_val);
//         ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, adc_val);
//         ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
//         vTaskDelay(100 / portTICK_PERIOD_MS);
//     }
// }