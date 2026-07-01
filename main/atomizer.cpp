#include "atomizer.h"
#include "app_gpio.h"

#define ATOMIZER_GPIO GPIO_NUM_18

void atomizer_init()
{
    gpio_init_output(ATOMIZER_GPIO);
}

void atomizer_on()
{
    gpio_set_output(ATOMIZER_GPIO, 1);
}

void atomizer_off()
{
    gpio_set_output(ATOMIZER_GPIO, 0);
}
