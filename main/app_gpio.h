#pragma once

#include "driver/gpio.h"

void gpio_init_output(gpio_num_t gpio_num);
void gpio_set_output(gpio_num_t gpio_num, uint32_t level);