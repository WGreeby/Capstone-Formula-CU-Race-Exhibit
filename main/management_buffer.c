/*
We want to send stuff that gets updated every once in a while.
*/

#include "management_buffer.h"

static sendy_buffer send_boof = {
    0,
    0,         
    0,
    0,
};

void useBoostPoint(sendy_buffer boof){
    if(boof.total_boost_points != 0){
        boof.total_boost_points--;
        /*
        For some amount of time increase motor speed
        */
    } else {
        //Send rumble to player to indicate no more boost points
        uint8_t raw_intensity = 128;
        uint8_t raw_duration = 50;

        ps3_cmd_t cmd = {};

        cmd.rumble_right_intensity = raw_intensity;
        cmd.rumble_left_intensity = raw_intensity;

        cmd.rumble_right_duration = raw_duration;
        cmd.rumble_left_duration = raw_duration;

        ps3Cmd(cmd);
    }
    return;
}

void setTime(uint32_t new_time){
    send_boof.time_since_race_started = new_time;
    return;
}

uint32_t getTime(){
    return send_boof.time_since_race_started;
}
