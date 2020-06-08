#include <Arduino.h>
#include <Wire.h>

void setup() {

	Wire.begin();
	Serial.begin(38400);


} // setup()


void loop() {

	Serial.println("---- I2C/TWI scanner ----");

	for (int address = 0; address < 128; address++) {

		Serial.print("$");
		if (address < 0x10) Serial.print("0");
		Serial.print(address,HEX);
		Serial.print(":");

		Wire.beginTransmission(address);
		int error = Wire.endTransmission(true);

		Serial.print(" ");
		Serial.println(error);
		delay(100);

		if (error != 0) continue;

		delay(100);

	} // for address

	delay(5555);

} // loop()
