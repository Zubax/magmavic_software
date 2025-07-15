// Copyright (C) 2023 Zubax Robotics

#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#include "platform.h"

#define BUFFER_SIZE 256  // Buffer size for reading serial data
#define LIGHT_LEVEL_TRIGGER_THRESHOLD 400

// Frequency PWM = Clock / (Prescaler * 255)
//               = 16,000,000 / (256 * 255) = 245 Hz ~= 250 Hz
// Period = 1/250 = 4 ms
// OFF:   requires between 0.8-1.2 ms -> 25% duty cycle = 1.0 ms
// ON:    requires between 1.6-1.9 ms -> 45% duty cycle = 1.8 ms
// FORCE: requires between 2.1-2.5 ms -> 55% duty cycle = 2.2 ms
#define MAGNET_OFF_DUTY_CYCLE_PCT 25
#define MAGNET_ON_DUTY_CYCLE_PCT 45

int main(void)
{
    platform_init();
    platform_adc_setup();
    platform_pwm_setup();
    while (true)
    {
        uint16_t readout = 0;
        readout          = platform_adc_read(0);
        // TODO: Buffer readout results, so spurious readings don't accidentally trigger the magnet.

        // Report on the current state
        char buffer[BUFFER_SIZE];
        snprintf(buffer, BUFFER_SIZE, "Current readout from A0: %u\r\n", readout);
        platform_serial_write(strlen(buffer), buffer);

        if (readout > LIGHT_LEVEL_TRIGGER_THRESHOLD)
        {
            // Turn magnet on
            platform_pwm_set(0, MAGNET_ON_DUTY_CYCLE_PCT);
        }
        else
        {
            // Turn magnet off
            platform_pwm_set(0, MAGNET_OFF_DUTY_CYCLE_PCT);
        }

        _delay_ms(1000);
    }

    return 0;
}
