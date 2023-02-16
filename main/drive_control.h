#include <stdio.h>
#include <stdlib.h>
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_log.h"
#include "ps3.h"

#define SAMPLE_CNT 32
#define LEDC_GPIO 27

void drive(uint32_t adc_val);
void init_hw(void);