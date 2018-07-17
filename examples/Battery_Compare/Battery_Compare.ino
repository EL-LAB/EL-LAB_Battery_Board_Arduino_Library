/*
    Battery_Compare.ino

    This example compares the data provided by the ADC for 
    different resolutions and gains.

    The recommended settings are 16 bits resolution and gain 1x.

    Created: July 17th, 2018
    Author: El Lab de Electro: EL LAB
    Modified: -
    Author: -

    URL: https://github.com/EL-LAB/EL-LAB_Battery_Board_Arduino_Library
*/

#include "battery.h"

Battery myBattery;

// Prints the channel data for all possible gains.
void printResults() {
  // Gain 1x
  myBattery.configureGain(GAIN_1X);
  myBattery.startConversion(CHANNEL_1);
  Serial.print("\tVoltage raw data (GAIN_1X): ");
  Serial.println(myBattery.read(), BIN);
  Serial.print("\tVoltage (GAIN_1X): ");
  Serial.print(myBattery.readVoltage(), DEC);
  Serial.println("V");
  myBattery.startConversion(CHANNEL_2);
  Serial.print("\tCurrent raw data (GAIN_1X): ");
  Serial.println(myBattery.read(), BIN);
  Serial.print("\tCurrent (GAIN_1X): ");
  Serial.print(myBattery.readCurrent(), DEC);
  Serial.println("A");
  
  // Gain 2x
  myBattery.configureGain(GAIN_2X);
  myBattery.startConversion(CHANNEL_1);
  Serial.print("\tVoltage raw data (GAIN_2X): ");
  Serial.println(myBattery.read(), BIN);
  Serial.print("\tVoltage (GAIN_2X): ");
  Serial.print(myBattery.readVoltage(), DEC);
  Serial.println("V");
  myBattery.startConversion(CHANNEL_2);
  Serial.print("\tCurrent raw data (GAIN_2X): ");
  Serial.println(myBattery.read(), BIN);
  Serial.print("\tCurrent (GAIN_2X): ");
  Serial.print(myBattery.readCurrent(), DEC);
  Serial.println("A");
  
  // Gain 4x
  myBattery.configureGain(GAIN_4X);
  myBattery.startConversion(CHANNEL_1);
  Serial.print("\tVoltage raw data (GAIN_4X): ");
  Serial.println(myBattery.read(), BIN);
  Serial.print("\tVoltage (GAIN_4X): ");
  Serial.print(myBattery.readVoltage(), DEC);
  Serial.println("V");
  myBattery.startConversion(CHANNEL_2);
  Serial.print("\tCurrent raw data (GAIN_2X): ");
  Serial.println(myBattery.read(), BIN);
  Serial.print("\tCurrent (GAIN_2X): ");
  Serial.print(myBattery.readCurrent(), DEC);
  Serial.println("A");
  
  // Gain 8x
  myBattery.configureGain(GAIN_8X);
  myBattery.startConversion(CHANNEL_1);
  Serial.print("\tVoltage raw data (GAIN_8X): ");
  Serial.println(myBattery.read(), BIN);
  Serial.print("\tVoltage (GAIN_8X): ");
  Serial.print(myBattery.readVoltage(), DEC);
  Serial.println("V");
  myBattery.startConversion(CHANNEL_2);
  Serial.print("\tCurrent raw data (GAIN_8X): ");
  Serial.println(myBattery.read(), BIN);
  Serial.print("\tCurrent (GAIN_8X): ");
  Serial.print(myBattery.readCurrent(), DEC);
  Serial.println("A");
}

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
  
  // Getting data from ADC for different resolutions.
  // NOTE: Recommended resolution is 16 bits.
  Serial.println("\nReading data in 12 bits resolution:");
  myBattery.configureResolution(BIT_12);
  printResults();
  
  Serial.println("\nReading data in 14 bits resolution:");
  myBattery.configureResolution(BIT_14);
  printResults();
  
  Serial.println("\nReading data in 16 bits resolution:");
  myBattery.configureResolution(BIT_16);
  printResults();
  
  Serial.println("\nReading data in 18 bits resolution:");
  myBattery.configureResolution(BIT_18);
  printResults();
}

void loop()
{

}
