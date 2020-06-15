#include <Arduino.h>
#include <Wire.h>


void printHex(int value);
void detect();
void query(int addr, int reg, int len);


void setup() {

	Wire.begin();
	Serial.begin(38400);

} // setup()


void loop() {

	detect();
	Serial.println("--");

	// Fetch values from my attached devices
	if (true) {

		// Fetch value: INA219 device, Bus Voltage register, 2-byte length
		query(0x40,2,2);

		// Fetch value: ADT7410 device, Temperature register, 2-byte lenght
		query(0x48,0,2);

		Serial.println("");
	}

	delay(2000);

} // loop()


void printHex(int value) {

	Serial.print("$");
	if (value < 0x10) Serial.print("0");
	Serial.print(value,HEX);

} // printHex()


void detect() {

	Serial.println("---- I2C/TWI address scanner ----");

	int col = 0;
	for (int address = 0x38; address < 0x50; address++) {

		if (( (col % 4) == 0 ) && ( col != 0 )) Serial.println();
		col++;

		Serial.print(" ");
		printHex(address);

		Wire.beginTransmission(address);
		int error = Wire.endTransmission(true);

		if (error == 0) {
			Serial.print(" [X] ");
		} else {
			Serial.print(" [ ] ");
		}

		delay(10);

	} // for address

	Serial.println();

} // detect()


void query(int addr, int reg, int len) {

	Serial.print("Fetching, addr=");
	printHex(addr);
	Serial.print(" reg=");
	printHex(reg);
	Serial.print(" ..");

	Wire.beginTransmission(addr);
	Wire.write(reg);
	Wire.endTransmission();

	Serial.print(".. ");

	Wire.requestFrom(addr,len);

	while (Wire.available()) {
		int b = Wire.read();
		if (b == -1) break;
		printHex(b);
		Serial.print(" ");
	}

	Serial.println();

} // query()
