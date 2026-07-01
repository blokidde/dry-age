#include "relais.h"
#include "app_gpio.h"

#define RELAIS_GPIO GPIO_NUM_19
    
void relais_init()
{
    gpio_init_output(RELAIS_GPIO);
}

void relais_on()
{
    gpio_set_output(RELAIS_GPIO, 1);
}

void relais_off()
{
    gpio_set_output(RELAIS_GPIO, 0);
}