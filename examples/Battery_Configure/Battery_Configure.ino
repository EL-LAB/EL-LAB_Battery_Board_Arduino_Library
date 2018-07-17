/*
    Battery_Configure.ino

    This example shows how to configure manually the ADC.

    This is a code for testing purposes and proper communication between
    the host and the device.

    Created: July 17th, 2018
    Author: El Lab de Electro: EL LAB
    Modified: -
    Author: -

    URL: https://github.com/EL-LAB/EL-LAB_Battery_Board_Arduino_Library
*/

#include "battery.h"

Battery myBattery;

void setup()
{
  Serial.begin(9600);
  
  // Checking connection.
  if (myBattery.begin()) {
    Serial.println("Battery detected.");
  }
  else {
    Serial.println("Baterry not detected!");
    return;
  }
  
  Serial.println("\nInitializing battery with default settings:  ONESHOT_MODE - BIT_16 - GAIN_1X.");
  
  // Initializes ADC.
  if (myBattery.init()) { 
    Serial.println("\tBattery initialized.");
  }
  else {
    Serial.println("\tBattery could not be initialized!");
    return;
  }

  // From this point, the ADC is configured with different set of settings just
  // to confirm the proper communication with the device.
  Serial.println("\nReading configuration register - Expected output: 00001000.");
  Serial.print("\tConfiguration register from IC: ");
  Serial.println(myBattery.getConfigIC(), BIN);
  Serial.print("\tConfiguration register from variable: ");
  Serial.print(myBattery.getConfigReg(), BIN);
  Serial.println("\n");

  Serial.println("Configuring the battery settings manually to: CONTINUOUS_MODE - BIT_14 - GAIN_4X.");

  Serial.println(myBattery.configureMode(CONTINUOUS_MODE) ? "\tCONTINUOUS_MODE configured." : "/tMode could not be configured!");
  Serial.println(myBattery.configureResolution(BIT_14) ? "\tBIT_14 configured." : "/tResolution could not be configured!");
  Serial.println(myBattery.configureGain(GAIN_4X) ? "\tGAIN_4X configured." : "/tGain could not be configured!");

  Serial.println("\nReading configuration register - Expected output: 00010110.");
  Serial.print("\tConfiguration register from IC: ");
  Serial.println(myBattery.getConfigIC(), BIN);
  Serial.print("\tConfiguration register from variable: ");
  Serial.print(myBattery.getConfigReg(), BIN);
  Serial.println("\n");

  Serial.println("Configuring the battery settings manually to: ONESHOT_MODE - BIT_18 - GAIN_8X.");

  Serial.println(myBattery.configureMode(ONESHOT_MODE) ? "\tONESHOT_MODE configured." : "/tMode could not be configured!");
  Serial.println(myBattery.configureResolution(BIT_18) ? "\tBIT_18 configured." : "/tResolution could not be configured!");
  Serial.println(myBattery.configureGain(GAIN_8X) ? "\tGAIN_8X configured." : "/tGain could not be configured!");

  Serial.println("\nReading configuration register - Expected output: 00001111.");
  Serial.print("\tConfiguration register from IC: ");
  Serial.println(myBattery.getConfigIC(), BIN);
  Serial.print("\tConfiguration register from variable: ");
  Serial.print(myBattery.getConfigReg(), BIN);
  Serial.println("\n");

  Serial.println("Configuring the battery settings manually to: ONESHOT_MODE - BIT_12 - GAIN_2X.");

  Serial.println(myBattery.configureMode(ONESHOT_MODE) ? "\tONESHOT_MODE configured." : "/tMode could not be configured!");
  Serial.println(myBattery.configureResolution(BIT_12) ? "\tBIT_12 configured." : "/tResolution could not be configured!");
  Serial.println(myBattery.configureGain(GAIN_2X) ? "\tGAIN_2X configured." : "/tGain could not be configured!");

  Serial.println("\nReading configuration register - Expected output: 00000001.");
  Serial.print("\tConfiguration register from IC: ");
  Serial.println(myBattery.getConfigIC(), BIN);
  Serial.print("\tConfiguration register from variable: ");
  Serial.print(myBattery.getConfigReg(), BIN);
  Serial.println("\n");
  
  Serial.println("Configuring the battery settings manually to (default): ONESHOT_MODE - BIT_16 - GAIN_1X.");

  Serial.println(myBattery.configureMode(ONESHOT_MODE) ? "\tONESHOT_MODE configured." : "/tMode could not be configured!");
  Serial.println(myBattery.configureResolution(BIT_16) ? "\tBIT_16 configured." : "/tResolution could not be configured!");
  Serial.println(myBattery.configureGain(GAIN_1X) ? "\tGAIN_1X configured." : "/tGain could not be configured!");

  Serial.println("\nReading configuration register - Expected output: 00001000.");
  Serial.print("\tConfiguration register from IC: ");
  Serial.println(myBattery.getConfigIC(), BIN);
  Serial.print("\tConfiguration register from variable: ");
  Serial.print(myBattery.getConfigReg(), BIN);
}

void loop()
{

}
