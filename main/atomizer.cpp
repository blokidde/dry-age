        gpio_set_level(ATOMIZER_GPIO, 0);
        printf("Atomizer ON\n");

        vTaskDelay(pdMS_TO_TICKS(10000));

        gpio_set_level(ATOMIZER_GPIO, 1);
        printf("Atomizer OFF\n");