// Copyright (C) 2023 Zubax Robotics

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

void platform_init(void);

void platform_led(const bool on);

void platform_kick_watchdog(void);

/// The call is non-blocking unless the buffer is full. Transmission is interrupt-driven.
void platform_serial_write(const size_t size, const void* const data);
/// The call is non-blocking. Returns -1 if the buffer is empty, otherwise the byte value in the range [0, 255].
int16_t platform_serial_read(void);

void     platform_adc_setup(void);
uint16_t platform_adc_read(const uint8_t channel);

void platform_pwm_setup(void);
void platform_pwm_set(const uint8_t channel, const uint8_t duty_pct);
