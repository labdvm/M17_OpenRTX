/***************************************************************************
 *   Copyright (C) 2023 by Federico Amedeo Izzo IU2NUO,                    *
 *                         Niccolò Izzo IU2KIN,                            *
 *                         Frederik Saraci IU2NRO,                         *
 *                         Silvano Seva IU2KWO                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>   *
 ***************************************************************************/

#include <at32f421.h>
#include <peripherals/gpio.h>
#include <interfaces/platform.h>
#include <platform/drivers/display/ST7735S.h>
#include <hwconfig.h>
#include <drivers/USART1.h>

static const hwInfo_t hwInfo =
{
    .vhf_maxFreq = 174,
    .vhf_minFreq = 136,
    .vhf_band    = 1,
    .uhf_maxFreq = 470,
    .uhf_minFreq = 400,
    .uhf_band    = 1,
    .hw_version  = 0,
    .name        = "RT-890"
};

void platform_init()
{
    // Configure GPIOs
    //InitGPIO();
    // Configure LCD RESX pin
    gpio_setMode(LCD_RST, OUTPUT);
    gpio_setPin(LCD_RST);
    // Configure rest of LCD pins
    gpio_setMode(LCD_DC,  OUTPUT);
    gpio_setMode(LCD_CS,  OUTPUT);
    gpio_setMode(LCD_CLK, OUTPUT);
    gpio_setMode(LCD_DAT, OUTPUT);

    gpio_setMode(GREEN_LED, OUTPUT);
    gpio_setMode(RED_LED,   OUTPUT);
    gpio_setMode(PTT_SW,    INPUT_PULL_UP);
}

void platform_terminate()
{
    // Shut down LED
    gpio_clearPin(GREEN_LED);
    gpio_clearPin(RED_LED);
}

uint16_t platform_getVbat()
{
    /*
     * Battery voltage is measured through an 1:5.7 voltage divider and
     * adc1_getMeasurement returns a value in mV. To have effective battery
     * voltage we have to multiply by the ratio: with a simple trick we can do
     * it also without using floats and with a maximum error of -1mV.
     */

    return 3000;
}

uint8_t platform_getMicLevel()
{
    return 0;
}

uint8_t platform_getVolumeLevel()
{
    return 0;
}

int8_t platform_getChSelector()
{
    return 0;
}

bool platform_getPttStatus()
{
    // PTT is active low
    return (gpio_readPin(PTT_SW) ? false : true);
}

bool platform_pwrButtonStatus()
{
    return true;
}

void platform_ledOn(led_t led)
{
    switch(led)
    {
        case GREEN:
            gpio_setPin(GREEN_LED);
            break;

        case RED:
            gpio_setPin(RED_LED);
            break;

        default:
            break;
    }
}

void platform_ledOff(led_t led)
{
    switch(led)
    {
        case GREEN:
            gpio_clearPin(GREEN_LED);
            break;

        case RED:
            gpio_clearPin(RED_LED);
            break;

        default:
            break;
    }
}

void platform_beepStart(uint16_t freq)
{
    (void) freq;
}

void platform_beepStop()
{

}

const hwInfo_t *platform_getHwInfo()
{
    return &hwInfo;
}
