idf_component_register(SRCS "atomizer.cpp" "sht40.cpp" "gpio_output.cpp" "main.cpp"
                    PRIV_REQUIRES spi_flash esp_driver_gpio esp_driver_ledc esp_driver_i2c
                    INCLUDE_DIRS ".")
target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++11)
