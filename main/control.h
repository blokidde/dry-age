#pragma once

#include <stdint.h>

void control_init(bool* atomizer_state, bool* relais_state, int64_t* start_time);
void control_update();
void control_get_output();

