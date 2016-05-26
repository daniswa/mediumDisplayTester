





#include <avr/io.h>
#include <util/delay.h>

void sendDispHeader();
void sendDispDataA();

int dispHeader [6][8] = {{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
						 {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
						 {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
						 {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
						 {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
						 {0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7}};

const int allSet = 0x00;
const int allClr = 0xFF;
const int clkSet = 0xFD;
const int strobeSet = 0xBF;
const int dataSet = 0xF7;
const int dataClkSet = 0xF5;

const int dispA [16][8] = {{0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7},
						   {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
						   {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
						   {0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7},
						   {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
						   {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
					       {0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7},
						   {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
						   {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
					       {0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7},
					       {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
					       {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
					       {0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7},
						   {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
						   {0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7},
					       {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}};

int main(void){
	DDRD = 0xFF;

	while(1){
		PORTD = allClr;
		sendDispHeader();
		sendDispDataA();
		_delay_us(2);
		PORTD = strobeSet;
		_delay_us(2);
	}
}

void sendDispHeader(){
	int j = 0;
	int k = 0;

	for(j = 0;j < 6;j++){

		for(k = 0;k < 8;k++){
			PORTD = dispHeader[j][k];
			_delay_us(1);
			PORTD = dispHeader[j][k] & clkSet;
			_delay_us(1);
			PORTD = dispHeader[j][k];
			_delay_us(1);
		}
	}
}

void sendDispDataA(){
	int j = 0;
	int k = 0;

	for(j = 0;j < 16;j++){

		for(k = 0;k < 8;k++){
			PORTD = dispA[j][k];
			_delay_us(1);
			PORTD = dispA[j][k] & clkSet;
			_delay_us(1);
			PORTD = dispA[j][k];
			_delay_us(1);
		}
	}
}