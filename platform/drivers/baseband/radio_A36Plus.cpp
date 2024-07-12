/***************************************************************************
 *   Copyright (C) 2021 - 2023 by Federico Amedeo Izzo IU2NUO,             *
 *                                Niccolò Izzo IU2KIN                      *
 *                                Frederik Saraci IU2NRO                   *
 *                                Silvano Seva IU2KWO                      *
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

#include <gd32f3x0.h>
#include <hwconfig.h>
#include <interfaces/nvmem.h>
#include <interfaces/radio.h>
#include <peripherals/gpio.h>
#include <utils.h>

#include <algorithm>

#include "HR_C6000.h"
#include "radioUtils.h"
static const rtxStatus_t*
    config;  // Pointer to data structure with radio configuration

// static gdxCalibration_t calData;        // Calibration data
// static Band currRxBand     = BND_NONE;  // Current band for RX
// static Band currTxBand     = BND_NONE;  // Current band for TX
// static uint16_t apcVoltage = 0;  // APC voltage for TX output power control

// static enum opstatus radioStatus;  // Current operating status

// static HR_C6000& C6000  = HR_C6000::instance();  // HR_C5000 driver
// static AT1846S& at1846s = AT1846S::instance();   // AT1846S driver

void radio_init(const rtxStatus_t* rtxState)
{
    config      = rtxState;
    // radioStatus = OFF;

    /*
     * Configure RTX GPIOs
     */
    rcu_periph_clock_enable(RCU_GPIOB);

    gpio_setMode(BK4819_CLK, OUTPUT);
    gpio_setMode(BK4819_DAT, OUTPUT);
    gpio_setMode(BK4819_CS, OUTPUT);

    /*
     * Enable and configure DAC for PA drive control
     */
    // SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK;
    // DAC0->DAT[0].DATL = 0;
    // DAC0->DAT[0].DATH = 0;
    // DAC0->C0   |= DAC_C0_DACRFS_MASK    // Reference voltage is Vref2
    //            |  DAC_C0_DACEN_MASK;    // Enable DAC

    // /*
    //  * Load calibration data
    //  */
    // nvm_readCalibData(&calData);

    // /*
    //  * Enable and configure both AT1846S and HR_C6000, keep AF output
    //  disabled
    //  * at power on.
    //  */
    // at1846s.init();
    // C6000.init();
    // radio_disableAfOutput();
}
void radio_terminate()
{

}

void radio_tuneVcxo(const int16_t vhfOffset, const int16_t uhfOffset)
{
    (void) vhfOffset;
    (void) uhfOffset;
}

void radio_setOpmode(const enum opmode mode)
{
    (void) mode;
}

bool radio_checkRxDigitalSquelch()
{
    return false;
}

void radio_enableAfOutput()
{

}

void radio_disableAfOutput()
{

}

void radio_enableRx()
{

}

void radio_enableTx()
{

}

void radio_disableRtx()
{

}

void radio_updateConfiguration()
{

}

rssi_t radio_getRssi()
{
    return -121.0f;  // S1 level: -121dBm
}

enum opstatus radio_getStatus()
{
    return OFF;
}
