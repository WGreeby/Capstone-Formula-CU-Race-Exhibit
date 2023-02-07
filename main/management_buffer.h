#include <stdint.h>
#include "ps3.h"

#include "sdkconfig.h"

typedef struct {
    uint32_t time_since_race_started;
    uint32_t total_boost_points;
    uint32_t car_battery_status;
    uint32_t controller_battery_status;
} sendy_buffer;