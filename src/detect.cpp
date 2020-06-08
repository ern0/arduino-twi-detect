#include <Arduino.h>
#include <Wire.h>

void setup() {

	Wire.begin();
	Serial.begin(38400);

	Serial.println("I2C/TWI scanner");

} // setup()


void loop() {

	for (int address = 0; address < 128; address++) {



	} // for address

} // loop()
