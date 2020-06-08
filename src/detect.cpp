#include <Arduino.h>
#include <Wire.h>

void setup() {

	Wire.begin();
	Serial.begin(38400);


} // setup()


void loop() {

	Serial.println("---- I2C/TWI address scanner ----");

	for (int address = 1; address < 128; address++) {

		Serial.print("[$");
		if (address < 0x10) Serial.print("0");
		Serial.print(address,HEX);
		Serial.print(":");

		Wire.beginTransmission(address);
		int error = Wire.endTransmission(true);

		Serial.print(" ");
		Serial.print(error);
		if (error == 0) Serial.print(" - ### gotcha! ###");
		Serial.print("]  ");
		if ((address-1) %4 == 0) Serial.println();
		delay(20);

	} // for address

	Serial.println();

	delay(5555);

} // loop()
