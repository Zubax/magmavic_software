# MavicMag firmware

`make` can be used for executing the most commonly required functionality.

- to build: `make all`
- to flash: `make dude`
- to test: `make execute_test`
- to format: `make format`
- assess size of the project: `make size`/`make sizex`

## Wiring diagram

- Light dependent sensor

```
5V (Nano) --- LDR --- A0 (Nano) --- 12kΩ Resistor --- GND (Nano)
```

- PWM output (for controlling magnet)

```
GND (Nano) --- GND (FluxGrip)
D10 (Nano) --- PWM (FluxGrip) 
```

- Power

```
9V (Battery) --- VIN (Nano)
GND (Battery) --- GND (Nano)
```

## Documentation

- Standard C libraries: https://en.cppreference.com/w/c/header.html
- AVR-GCC: https://www.nongnu.org/avr-libc/user-manual/modules.html
- Datasheets: see `docs/`
  - Atmega328P
  - PDV-P9008 Light Dependent Resistor
  - VEMD1060X01 Photodiode




