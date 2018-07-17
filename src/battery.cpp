/***********************************************************************
* FILENAME: battery.cpp
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

#include "battery.h"

void Battery::_updateResolution(uint8_t resolution) {
    switch (resolution) {
        case BIT_12:
            _conversion_factor_1 = 1.0;
            _conversion_factor_2 = 1000.0;
            break;

        case BIT_14:
            _conversion_factor_1 = 250.0;
            _conversion_factor_2 = 1000000.0;
            break;

        case BIT_16:
            _conversion_factor_1 = 62.5;
            _conversion_factor_2 = 1000000.0;
            break;

        case BIT_18:
            _conversion_factor_1 = 15.625;
            _conversion_factor_2 = 1000000.0;
            break;

        default:
            _conversion_factor_1 = 1.0;
            _conversion_factor_2 = 1000.0;
            break;
    }
}

void Battery::_updateGain(uint8_t gain) {
    switch (gain) {
        case GAIN_1X:
            _gain = 1;
            break;

        case GAIN_2X:
            _gain = 2;
            break;

        case GAIN_4X:
            _gain = 4;
            break;

        case GAIN_8X:
            _gain = 8;
            break;

        default:
            _gain = 1;
            break;
    }
}

Battery::Battery(void) {
}

bool Battery::begin(void) {
    Wire.begin();
    Wire.beginTransmission(ADC_ADDRESS);
    return (Wire.endTransmission() == 0);
}

bool Battery::init(uint8_t mode, uint8_t resolution, uint8_t gain) {
    _configReg = (mode | resolution | gain);

    _updateResolution(resolution);
    _updateGain(gain);

    _voltage_divider_relation = 0.19;
    _resistor_current = 0.01;

    Wire.beginTransmission(ADC_ADDRESS);
    Wire.write(_configReg);
    return (Wire.endTransmission() == 0);
}

bool Battery::init(void) {
    return init(ONESHOT_MODE, BIT_16, GAIN_1X);
}

bool Battery::configureMode(uint8_t mode) {
    _configReg = ((_configReg & ~MODE_MASK) | mode); // Overwrites with the new mode.

    Wire.beginTransmission(ADC_ADDRESS);
    Wire.write(_configReg);
    return (Wire.endTransmission() == 0);
}

bool Battery::configureResolution(uint8_t resolution) {
    _configReg = ((_configReg & ~BIT_MASK) | resolution); // Overwrites with the new resolution bits.

    _updateResolution(resolution);

    Wire.beginTransmission(ADC_ADDRESS);
    Wire.write(_configReg);
    return (Wire.endTransmission() == 0);
}

bool Battery::configureGain(uint8_t gain) {
    _configReg = ((_configReg & ~GAIN_MASK) | gain); // Overwrites with the new gain.

    _updateGain(gain);

    Wire.beginTransmission(ADC_ADDRESS);
    Wire.write(_configReg);
    return (Wire.endTransmission() == 0);
}

uint8_t Battery::getConfigIC(void) {
    uint8_t configData = 0x00;

    do {
        // If 18BIT mode is configured, then the conversion data is 3 bytes and then 1 byte with the configuration data.
        if ((_configReg & BIT_MASK) == BIT_18) {
            if (Wire.requestFrom((int) ADC_ADDRESS, (int) 4) == 4) {
                configData = Wire.read();   // Conversion data.
                configData = Wire.read();   // Conversion data.
                configData = Wire.read();   // Conversion data.
                configData = Wire.read();   // Configuration data is output after the data bytes. We don't care about the conversion data.
            }
            else {
                return 0xFF;
            }
        }
        // If 12|14|16BIT mode is configured, then the conversion data is 2 bytes and then 1 byte with the configuration data.
        else {
            if (Wire.requestFrom((int) ADC_ADDRESS, (int) 3) == 3) {
                configData = Wire.read();   // Conversion data.
                configData = Wire.read();   // Conversion data.
                configData = Wire.read();   // Configuration data is output after the data bytes. We don't care about the conversion data.
            }
            else {
                return 0xFF;
            }
        }
    } while ((configData & RDY_MASK) != 0x00); // Keep reading the buffer until the output register has been updated.

    // Updates internal variables with current configuration data.
    _configReg = configData;
    _updateResolution(configData & BIT_MASK);
    _updateGain(configData & GAIN_MASK);

    return configData;
}

uint8_t Battery::getConfigReg(void) {
    return _configReg;
}

bool Battery::startConversion(uint8_t channel){
    _configReg = ((_configReg & ~CHANNEL_MASK) | channel); // Overwrites with the new channel to read from.

    // Starts a new conversion by sending the new configuration data.
    Wire.beginTransmission(ADC_ADDRESS);
    Wire.write(_configReg | RDY_MASK); // RDY_MASK initiates the conversion process. Not needed if continuous conversion mode is configured.
    return (Wire.endTransmission() == 0);
}

uint32_t Battery::read(void) {
    uint32_t data = 0x00000000;
    uint8_t configData = 0x00;

    do {
        // If 18BIT mode is configured, then the conversion data is 3 bytes and then 1 byte with the configuration data.
        if ((_configReg & BIT_MASK) == BIT_18) {
            if (Wire.requestFrom((int) ADC_ADDRESS, (int) 4) == 4) {
                data = Wire.read();                 // Conversion data. First byte.
                data = data << 8;
                data = data | Wire.read();          // Conversion data. Second byte.
                data = data << 8;
                data = data | Wire.read();          // Conversion data. Third byte.
                configData = Wire.read();           // Configuration data is output after the data bytes.
            }
            else {
                return 0xFFFFFFFF;
            }
        }
        // If 12|14|16BIT mode is configured, then the conversion data is 2 bytes and then 1 byte with the configuration data.
        else {
            if (Wire.requestFrom((int) ADC_ADDRESS, (int) 3) == 3) {
                data = Wire.read();          // Conversion data. First byte.
                data = data << 8;
                data = data | Wire.read();   // Conversion data. Second byte.
                configData = Wire.read();    // Configuration data is output after the data bytes.
            }
            else {
                return 0xFFFFFFFF;
            }
        }
    } while ((configData & RDY_MASK) != 0x00); // Keep reading the buffer until the output register has been updated.

    return data;
}

float Battery::readVoltage(void) {
    if (!startConversion(CHANNEL_1)) {  // Voltage input comes from channel 1.
        return 0xFFFFFFFF;
    }

    // Value read * voltage divider relation * (conversion_factor_1/conversion_factor_2) / gain
    return ((uint32_t) read() * ((_conversion_factor_1) / (_gain * _conversion_factor_2 * _voltage_divider_relation)));
}

float Battery::readCurrent(void) {
    if (!startConversion(CHANNEL_2)) {  // Current input (voltage) comes from channel 2.
        return 0xFFFFFFFF;
    }

    // Value read * (conversion_factor_1/conversion_factor_2) / (gain * voltage divider relation)
    // Divided by resistor value
    return (((int32_t) read() * ((_conversion_factor_1) / (_gain * _conversion_factor_2))) / _resistor_current);
}
