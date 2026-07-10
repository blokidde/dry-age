#include "control.h"

#include "esp_timer.h"

void control_init(bool* atomizer_state, bool* relais_state, int64_t* start_time){
    *atomizer_state = false;
    *relais_state = false;

    *start_time = esp_timer_get_time();
}

void control_update(){
    
}

void control_get_output(){
    
}