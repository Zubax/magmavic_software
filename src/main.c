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

    // This is to detect when Arduino reboots
    uint8_t i = 0;
    for (i = 0; i < 10; i++)
    {
        platform_led(i%2 == 0 ? true : false); // Toggle
        _delay_ms(500);
        platform_kick_watchdog();
    }


    bool magnet_on = false;
    while (true)
    {
        // Report on the current state
        char buffer[BUFFER_SIZE];
        snprintf(buffer, BUFFER_SIZE, "Current state of magnet: %s\r\n", magnet_on ? "ON" : "OFF");
        platform_serial_write(strlen(buffer), buffer);

        // Process incoming data
        while (true)
        {
            const int16_t rx = platform_serial_read();
            if (rx < 0)
            {
                break;
            }
            const char c = (char) rx;
            if (c == 'a')
            {
                // Turn magnet on
                magnet_on = true;
            }
            if (c == 'b')
            {
                // Turn magnet off
                magnet_on = false;
            }
        }

        // Update state of magnet
        platform_pwm_set(0, magnet_on == true ? MAGNET_ON_DUTY_CYCLE_PCT : MAGNET_OFF_DUTY_CYCLE_PCT);

        platform_kick_watchdog();
        _delay_ms(200);
    }

    return 0;
}
