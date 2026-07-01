#include "app_gpio.h"

void gpio_init_output(gpio_num_t gpio_num)
{
    gpio_config_t io_conf ={
        .pin_bit_mask = (1ULL << gpio_num),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };

    gpio_config(&io_conf);
}

// not used for now
void gpio_init_input(gpio_num_t gpio_num)
{
    gpio_config_t io_conf ={
        .pin_bit_mask = (1ULL << gpio_num),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };

    gpio_config(&io_conf);
}

void gpio_set_output(gpio_num_t gpio_num, uint32_t level)
{
    gpio_set_level(gpio_num, level ? 1 : 0);
}