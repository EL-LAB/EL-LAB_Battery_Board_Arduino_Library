/***********************************************************************
* FILENAME: battery.h
*
* DESCRIPTION:
*       Arduino library for the ADC MCP3422. It works only for the
*       platform EL LAB: Battery Board. This library should be adapted 
*       to work with the ADC MCP3422 stand alone.
*
* URL:  https://github.com/EL-LAB/EL-LAB_Battery_Board_Arduino_Library
* 
* AUTHOR:  Diego Villalobos    START DATE :  July 17 2018
*
* CHANGES:
*
* VERSION      DATE         WHO         DETAIL
*  1.0.0   July 17 2018   Diego V.      Initial release
*
***********************************************************************/

#ifndef _BATTERY_H_
#define _BATTERY_H_

#ifdef ARDUINO
    #if ARDUINO < 100
        #include "WProgram.h"
    #else
        #include "Arduino.h"
    #endif
#endif // ARDUINO

#include <Wire.h>

#define ADC_ADDRESS     0X69

#define RDY_MASK        0x80

#define CHANNEL_1       0x00
#define CHANNEL_2       0x20
#define CHANNEL_MASK    0x60

#define ONESHOT_MODE    0x00
#define CONTINUOUS_MODE 0x10
#define MODE_MASK       0x10

#define BIT_12          0x00
#define BIT_14          0x04
#define BIT_16          0x08
#define BIT_18          0x0C
#define BIT_MASK        0x0C

#define GAIN_1X         0x00
#define GAIN_2X         0x01
#define GAIN_4X         0x02
#define GAIN_8X         0x03
#define GAIN_MASK       0x03

class Battery {
    public:
        Battery(void);

        bool begin(void);

        bool init(void);
        bool init(uint8_t mode, uint8_t resolution, uint8_t gain);

        bool configureMode(uint8_t mode);
        bool configureResolution(uint8_t resolution);
        bool configureGain(uint8_t gain);

        uint8_t getConfigIC(void);
        uint8_t getConfigReg(void);

        bool startConversion(uint8_t channel);

        uint32_t read();
        float readVoltage(void);
        float readCurrent(void);

    private:
        uint8_t _configReg;

        double _conversion_factor_1;
        double _conversion_factor_2;
        uint8_t _gain;

        double _voltage_divider_relation;
        double _resistor_current;

        void _updateGain(uint8_t gain);
        void _updateResolution(uint8_t resolution);
};

#endif // _BATTERY_H_
