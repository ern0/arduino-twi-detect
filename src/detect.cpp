#include <Arduino.h>
#include <Wire.h>


void printHex(int value);
void command(int addr, int reg, int value);
void query(int addr, int reg, int len);


void setup() {

	Wire.begin();
	Serial.begin(38400);

} // setup()


void loop() {

	Serial.println("------- I2C/TWI address scanner -------");

	const int first = 0x00;
	const int last = 0x7f;
	const int increment = 1;

	int col = 0;
	for (int address = first; address <= last; address += increment) {

		if (( (col % 8) == 0 ) && ( col != 0 )) Serial.println();
		col++;

		Serial.print(" ");
		printHex(address);

		if (address == 0) {
			Serial.print("-");
			continue;
		}

		Wire.beginTransmission(address);
		int error = Wire.endTransmission(true);

		if (error == 0) {
			Serial.print("*");
		} else {
			Serial.print(" ");
		}

		delay(10);

	} // for address

	Serial.println();

	delay(4000);

} // loop()


void printHex(int value) {

	Serial.print("$");
	if (value < 0x10) Serial.print("0");
	Serial.print(value,HEX);

} // printHex()


void command(int addr, int reg, int value) {

	Serial.print("Sending, addr=");
	printHex(addr);
	Serial.print(" reg=");
	printHex(reg);
	Serial.print(" value=");
	printHex(value);
	Serial.print(" ...");

	Wire.beginTransmission(addr);
	Wire.write(reg);
	Wire.write(value);
	Wire.endTransmission();

	Serial.println("");

} // command()


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
