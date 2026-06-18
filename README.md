# Dry-agingkast

Firmware voor een ESP32-gebaseerde climate controlled dry-agingkast, gebouwd door een ijskast om te bouwen. Het project is bedoeld om het klimaat in de kast te meten en actief te regelen voor dry aging.

De huidige code stuurt een atomizer aan via een GPIO-uitgang en bevat voorbereiding voor het uitlezen van een SHT40 temperatuur- en luchtvochtigheidssensor via I2C.

## Hardware

- Atomizer: GPIO 18, actief laag (`0` = aan, `1` = uit)
- SHT40: I2C-adres `0x44`
- I2C SDA: GPIO 5
- I2C SCL: GPIO 4

## Werking

De huidige `app_main` initialiseert GPIO 18 als uitgang en schakelt de atomizer elke 10 seconden aan en uit. De SHT40-meetcode staat al in `main/main.cpp`, maar is op dit moment uitgecommentarieerd. Uiteindelijk kan deze basis worden uitgebreid met klimaatregeling op basis van temperatuur en luchtvochtigheid.

## Projectstructuur

- `main/main.cpp`: hoofdprogramma en huidige regel-loop
- `main/gpio_output.*`: kleine helper voor GPIO-uitgangen
- `main/atomizer.*`: voorbereiding voor atomizer-logica
- `main/sht40.*`: voorbereiding voor SHT40-sensorlogica
- `sdkconfig`: ESP-IDF configuratie

## Bouwen en flashen

Gebruik ESP-IDF:

```sh
idf.py build
idf.py -p PORT flash monitor
```

Vervang `PORT` door de seriele poort van het ESP32-board.
