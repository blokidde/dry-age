#include "atomizer.h"


// function not specifically necessary but does bring more readability in main
void atomizer_on(gpio_num_t gpio_num)
{
        gpio_set_level(gpio_num, 0);
}

void atomizer_off(gpio_num_t gpio_num)
{
        gpio_set_level(gpio_num, 1);
}

// gpio_set_level(ATOMIZER_GPIO, 0);
// printf("Atomizer ON\n");

// vTaskDelay(pdMS_TO_TICKS(10000));

// gpio_set_level(ATOMIZER_GPIO, 1);
// printf("Atomizer OFF\n");