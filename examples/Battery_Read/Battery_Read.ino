/*
    Battery_Read.ino

    This example shows how to get the voltage and current from the battery.

    This code uses the default settings which are the recommended ones:
        - 16 bit resolution
        - Gain 1x

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
  
  // Initializes ADC.
  if (myBattery.init()) { 
    Serial.println("Battery initialized.");
  }
  else {
    Serial.println("Battery could not be initialized!");
    return;
  }
}

void loop()
{
  // Reads battery voltage.
  Serial.print("\nVoltage: ");
  Serial.print(myBattery.readVoltage(), 3);
  Serial.println("V");
  
  // Reads battery current.
  Serial.print("Current: ");
  Serial.print((myBattery.readCurrent() / 1000.0), 3);
  Serial.println("mA");

  delay(5000); // Reading battery every 5 seconds.
}
