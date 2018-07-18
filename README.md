# EL LAB: Battery Board Arduino Library
This library allows using the ADC MCP3422 for reading data from its 2 channels (one channel for getting the battery voltage and one channel for getting the current draw from the battery). This library has been specifically developed for the platform **EL LAB: Battery Board**.

There is additional information about the library and its uses in the following sections:
- [Arduino Examples](https://github.com/EL-LAB/EL-LAB_Battery_Board_Arduino_Library#arduino-examples)
- [Library Functions](https://github.com/EL-LAB/EL-LAB_Battery_Board_Arduino_Library#library-functions)

## Arduino Examples
#### [Battery_Configure](/examples/Battery_Configure/Battery_Configure.ino)
This example shows how to configure manually the ADC. It's recommended to use the ADC with the default settings, but it's also possible to configure it with custom settings. This sketch shows different settings combinations and checks if the ADC was properly configured by reading the configuration register.
#### [Battery_Compare](/examples/Battery_Compare/Battery_Compare.ino)
This example compares the data provided by the ADC for different resolutions and gains. This sketch helps to see the effect of changing the resolution and gain settings.

It is recommended to use `GAIN_1X` as higher gains may cause overflow. This effect is shown in this sketch.
#### [Battery_Read](/examples/Battery_Read/Battery_Read.ino)
This example shows how to get the voltage and current draw from the battery.

## Library Functions
This library includes the following functions to initialize, configure and get data from the ADC MCP3422:
#### begin()
It starts the I2C communication on the board and checks if the ADC MCP3422 is available. It doesn't require any argument and it returns `TRUE` if the ADC is found or `FALSE` otherwise.
```C++
bool begin(void);
```
#### init()
It configures the ADC MCP3422 for the first use. This function receives 3 arguments: mode, resolution and gain. These arguments will define how the ADC will work. If no arguments are provided, then the ADC MCP3422 will be configured with the default (and recommended) settings: one shot mode, 16 bit resolution and x1 gain. Different options are:
- **Mode**: `ONESHOT_MODE` or `CONTINUOUS_MODE`.
- **Resolution**: `BIT_12`, `BIT_14`, `BIT_16` or `BIT_18`.
- **Gain**: `GAIN_1X`, `GAIN_2X`, `GAIN_4X` or `GAIN_8X`.

The funtion returns `TRUE` if the configuration is succesfull or `FALSE` otherwise.
```C++
bool init(void);
bool init(uint8_t mode, uint8_t resolution, uint8_t gain);
```
#### configureMode()
It configures the ADC MCP3422 with a new mode. This could be `ONESHOT_MODE` or `CONTINUOUS_MODE`. The recommended mode is `ONESHOT_MODE` as the power consumption of the ADC will be highly decreased. The funtion returns `TRUE` if the configuration is succesfull or `FALSE` otherwise.
```C++
bool configureMode(uint8_t mode);
```
#### configureResolution()
It configures the ADC MCP3422 with a new resolution. This could be `BIT_12`, `BIT_14`, `BIT_16` or `BIT_18`. The recommended resolution is `BIT_16`. Using a higher resolution requires additional resources (memory) from the MCU, however there is no much difference in the final result. The funtion returns `TRUE` if the configuration is succesfull or `FALSE` otherwise.
```C++
bool configureResolution(uint8_t resolution);
```
#### configureGain()
It configures the ADC MCP3422 with a new gain. This could be `GAIN_1X`, `GAIN_2X`, `GAIN_4X` or `GAIN_8X`. The way the platform **EL LAB: Battery Board** is designed makes unecessary the use of a different gain besides `GAIN_1X`, therefore the recommended gain is `GAIN_1X`. Using higher gains may cause overflow in the ADC conversion and wrong data readings. The funtion returns `TRUE` if the configuration is succesfull or `FALSE` otherwise.
```C++
bool configureGain(uint8_t gain);
```
#### getConfigIC()
It reads the configuration register of the ADC MCP3422. The function doesn't receive any argument and it returns the configuration register value (8 bits). This function is used to confirm the ADC has been configured as desired.
```C++
uint8_t getConfigIC(void);
```
#### getConfigReg()
It returns the value of the configuration register of the ADC MCP3422 that is stored in an internal library variable. This function is used for testing purposes only.
```C++
uint8_t getConfigReg(void);
```
#### startConversion()
It starts the ADC conversion process. This function must be used after the ADC has been configured properly with a mode, a resolution and a gain. The function receives the desired channel to read the data from. The channel options are:
- `CHANNEL_1` for voltage readings.
- `CHANNEL_2` for current readings.

The function returns `TRUE` if the process started succesfully or `FALSE` otherwise.
```C++
bool startConversion(uint8_t channel);
```
#### read()
It returns the result of the data conversion as a raw value. The conversion output corresponds to the channel defined when the `startConversion()` function was called.
```C++
uint32_t read();
```
#### readVoltage()
It returns the battery voltage in volts (V). This function automatically starts the conversion process for the `CHANNEL_1`, and calculate the voltage value based on the raw data from the ADC; and the resolution and gain settings that were configured previously.
```C++
float readVoltage(void);
```
#### readCurrent()
It returns the battery current draw in amperes (A). This function automatically starts the conversion process for the `CHANNEL_2`, and calculate the current value based on the raw data from the ADC; and the resolution and gain settings that were configured previously.
```C++
float readCurrent(void);
```
