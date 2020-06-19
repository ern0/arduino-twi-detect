#include <Arduino.h>
#include <Wire.h>


void printHex(int value);
void command(int addr, int reg, int value);
void query(int addr, int reg, int len);
void discover(int first, int last);
void swioTest();
void muxTest();


void setup() {

	Wire.begin();
	Serial.begin(38400);

} // setup()


void loop() {

	Serial.println("");

	discover(0x00, 0xff);
	//swioTest();
	//muxTest();

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


void discover(int first, int last) {

	Serial.println("------- I2C/TWI address scanner -------");

	int col = 0;
	for (int address = first; address <= last; address++) {

		if (( (col % 8) == 0 ) && ( col != 0 )) Serial.println();
		col++;

		Serial.print(" ");
		printHex(address);

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

	delay(1000);

} // discover()


void swioTest() {

	// Turn RED on/off
	command(0x42, 0x11, 1);
	delay(300);
	command(0x42, 0x11, 0);
	delay(300);

	// Turn GREEN on/off
	command(0x42, 0x12, 1);
	delay(300);
	command(0x42, 0x12, 0);
	delay(300);

	// Turn BLUE on/off
	command(0x42, 0x13, 1);
	delay(300);
	command(0x42, 0x13, 0);
	delay(300);

	// Set RGB to %111 (white), then turn off
	command(0x42, 0x10, 0x07);
	delay(1000);
	command(0x42, 0x10, 0x00);
	delay(1000);

	// Set storage register $50 to 1, 2, 3, 4
	command(0x42, 0x50, 1);
	delay(300);
	command(0x42, 0x50, 2);
	delay(300);
	command(0x42, 0x50, 3);
	delay(300);
	command(0x42, 0x50, 4);
	delay(300);

} // swioTest()


void muxTest() {
		// Fetch values from my attached devices
	if (false) {

		Serial.println("");

		// Fetch value: INA219 device, Bus Voltage register, 2-byte length
		query(0x42, 0x1e, 4);

		// Fetch value: ADT7410 device, Temperature register, 2-byte lenght
		query(0x48,0,2);
	}

	delay(100);

} // muxTest()
