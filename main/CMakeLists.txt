idf_component_register(SRCS "control.cpp" "fan.cpp" "relais.cpp" "app_gpio.cpp" "atomizer.cpp" "sht40.cpp" "main.cpp"
                    PRIV_REQUIRES spi_flash esp_driver_gpio esp_driver_ledc esp_driver_i2c esp_timer
                    INCLUDE_DIRS ".")
target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++11)
