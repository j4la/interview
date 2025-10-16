/*
 * ProjectLDR.c
 *
 * Created: 25/09/2025 4:35:40 PM
 * Author : Jala
 */ 

#include <avr/io.h>

uint8_t keyScan();
void configB(char ddrb, char portb);
void configC(char ddrc, char portc);
void configTimer0(uint16_t prescaler, uint8_t timerCountLow);
void configTimer1();
void configTimer2();
void tenMicSecDelay();

// Membrane key pad values to set each column high
const char col1 = 0xEF;
const char col2 = 0xDF;
const char col3 = 0xBF;
const char col4 = 0x7F;

// Key press vals
const char oneKey = 0xEE;
const char twoKey = 0xDE;
const char threeKey = 0xBE;
const char fourKey = 0xED;
const char fiveKey = 0xDD;
const char sixKey = 0xBD;
const char sevenKey = 0xEB;
const char eightKey = 0xDB;
const char nineKey = 0xBB;
const char zeroKey = 0xD7;
const char aKey = 0x7E;
const char bKey = 0x7D;
const char cKey = 0x7B;
const char dKey = 0x77;
const char starKey = 0xE7;
const char hashKey = 0xB7;
/*
Membrane keypad return value for each key:
 0xEE - 1 key
 0xDE - 2 key
 0xBE - 3 key
 0xED - 4 key
 0xDD - 5 key
 0xBD - 6 key
 0xEB - 7 key
 0xDB - 8 key
 0xBB - 9 key
 0xD7 - 0 key
 0x7E - A key
 0x7D - B key
 0x7B - C key
 0x77 - D key
 0xE7 - * key
 0xB7 - # key
 
 Keypad Column 1:
 1 - 0xEE
 4 - 0xED
 7 - 0xEB
 * - 0xE7
 Keypad Column 2:
 2 - 0xDE
 5 - 0xDD
 8 - 0xDB
 0 - 0xD7
 Keypad Column 3:
 3 - 0xBE
 6 - 0xBD
 9 - 0xBB
 # - 0xB7
 Keypad Column 4:
 A - 0x7E
 B - 0x7D
 C - 0x7B
 D - 0x77
*/

uint8_t key = 0xFF;	// int for membrane key press value
uint8_t current = 0;
volatile uint8_t temp = 0;
uint8_t i;

volatile uint16_t boardReading = 0;

/*
	- Select A for LDR bar graph mode
	- Select B for setting PORTB with keypad nums mode
	- Select C for 
	- Select D for 


Page 203 in ATmega32A data sheet:

ADC6:
ACME - 1
ADEN - 0
MUX2:0 - 110

ADMUX:
REFS1 REFS0 ADLAR MUX4 MUX3 MUX2 MUX1 MUX0

MUX4:0 - Pos diff input ADC6, Neg diff input ADC1: 
1 0110

0000 0(110)

ADCSRA - ADC control and status register A
Enable ADEN in ACSRA to enable ADC
A conversion is started by writing a 1 to ADSC
	This clears after the conversion is complete
	
A freq between 50kHz and 200kHz required to get maximum resolution
ADC contains a prescaler, set by the ADPS bits in ADCSRA
Prescaler starts counting when ADC turned on by setting ADEN in ADCSRA
Prescaler keeps running as long as ADEN is set
Normal conversion takes 13 ADC clock cycles

When conversion is complete, result in ADC data registers and ADIF is set

Reference selection values in ADMUX.


How do I make the conversion target the LDR reading (PA6)?

	ADCH - ADC data register high byte
	ADCL - ADC data register low byte
	
ADMUX - Analog comparator multiplexed input

*/

int main(void)
{
    
    while (1) 
    {
		current = keyScan();
		
		if (current == 0x0A)	// LDR mode
		{
			DDRB = 0xFF;
			PORTB = 0x00;
			configLDR();
			boardReading = readLDR();
			// delay
			tenMiliSecDelay();
			
			temp = boardReading / 4;
			PORTB = temp;
			// while loop to continue reading LDR
			// output LDR reading to PORTB as bar graph	
		}
    }
}

// to read LDR read PORTA6
// returns 10 bit value
// to get 8 bit value suitable for PORTB, PA6 / 4

void configLDR()
{
	
	// Confirm that the ADC is currently disabled
	ADCSRA &= ~(1 << ADEN);
	
	// Once converter is off, setup ADMUX register
	ADMUX &= 0x70;	// Clear lower 5 bits
	// Set ADMUX single ended input to ADC6
	ADMUX |= (0 << MUX4) | (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (0 << MUX0);
	
	// Set prescaler (to 128 (94kHz)) & trigger source
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	
/*
	// Set ADCSRA bits ADEN (ADC enable), ADSC (ADC start conversion) (1100 0000)
	ADCSRA = ADEN << 1 | ADSC << 1;
	// ADCSRA = 0xC0;
	
	// Sets ADMUX single ended input to ADC6 (MUX4:0 = 00110)
	ADMUX = MUX2 << 1 | MUX1 << 1;
	//ADMUX = 0x06; // 0000 0110
*/
	
}

uint16_t readLDR()
{
	uint16_t ldrReading = 0;
	// Start conversion
	ADCSRA |= (1 << ADSC);
	
	// Wait until conversion is complete
	while ((ADCSRA & (1 << ADSC)) == (1 << ADSC));
	// ldrReading = ADCW; // not sure what this does as ADCW isnt mentioned in datasheet
	ldrReading = ADCL | (ADCH << 8);
	
	return ldrReading;
}


uint8_t keyScan()
{
/*
Keypad Column 1:
	1 - 0xEE
	4 - 0xED
	7 - 0xEB
	* - 0xE7
Keypad Column 2:
	2 - 0xDE
	5 - 0xDD
	8 - 0xDB
	0 - 0xD7
Keypad Column 3:
	3 - 0xBE
	6 - 0xBD
	9 - 0xBB
	# - 0xB7
Keypad Column 4:
	A - 0x7E
	B - 0x7D
	C - 0x7B
	D - 0x77
*/
	key = 0xFF;
	
	PORTC = col1;		// set column1 of keypad high
	// delay function
	tenMicSecDelay();
	key = PINC;			// get PINC switch input
	
	if (key != col1)
	{
		if (key == oneKey)			{return 0x01;}
		else if (key == fourKey)	{return 0x04;}
		else if (key == sevenKey)	{return 0x07;}
		else if (key == starKey)	{return 0x0E;}
		else						{return key;}
	}
	
	PORTC = col2;
	// delay
	tenMicSecDelay();
	key = PINC;
	if (key != col2)
	{
		if (key == twoKey)			{return 0x02;}
		else if (key == fiveKey)	{return 0xDD;}
		else if (key == eightKey)	{return 0x08;}
		else if (key == zeroKey)	{return 0x00;}
		else						{return key;}
	}
	
	PORTC = col3;
	// delay
	tenMicSecDelay();
	key = PINC;
	if (key != col3)
	{
		if (key == threeKey)		{return 0x03;}
		else if (key == sixKey)		{return 0x06;}
		else if (key == nineKey)	{return 0x09;}
		else if (key == hashKey)	{return 0x0F;}
		else						{return key};
	}
	
	PORTC = col4;
	// delay
	tenMicSecDelay();
	key = PINC;
	if (key != col4)
	{
		if (key == aKey)			{return 0x0A;}
		else if (key == bKey)		{return 0x0B;}
		else if (key == cKey)		{return 0x0C;}
		else if (key == dKey)		{return 0x0D;}
		else						{return key;}
	}
	
	return 0xFF;
}

void configB(char ddrb, char portb)
{
// DDRB bits logic 1, PORTB can be written to
// DDRB bits logic 0, PORTB value controls internal pull up resistors
// e.g. DDRB = 0xFF, write mode
	DDRB = ddrb;
	PORTB = portb;
}

/*
DDRC = 0xF0;	// lower byte read mode, upper byte write mode
PORTC = 0x0F;	// lower byte write mode, upper byte read mode

DDRB = 0xFF;	// write mode
PORTB = 0x00;	// read mode
*/

void configC(char ddrc, char portc)
{
// DDRC bits logic 1, PORTC can be written to
// DDRC bits logic 0, PORTC value controls internal pull up resistors
// e.g. DDRC = 0xF0, lower byte read mode, upper byte write mode
	DDRC = ddrc;
	PORTC = portc;
}

void configTimer0(uint16_t prescaler, uint8_t timerCountLow) // 8 bits wide, 0 -> 255
{
	if (prescaler == 0)	{
		TCCR0 = 0x00;						// prescaler off, control register set to 0 (clock source off)
	}
	else if (prescaler == 8) {
		TCCR0 = (1 << CS01);				// prescaler of 8
	}
	else if (prescaler == 64) {
		TCCR0 = (1 << CS01) | (1 << CS00);	// prescaler of 64
	}
	else if (prescaler == 256) {
		TCCR0 = (1 << CS02);				// prescaler of 256
	}
	else if (prescaler == 1024)	{
		TCCR0 = (1 << CS02) | (1 << CS00);	// prescaler at 1024
	}
	else {
		TCCR0 = 0x00;						// default, prescaler off
	}
	//TCNT0 = 0;	// Timer counter to 0
	TCNT0 = timerCountLow;
	
	//TIMSK &= ~((0 << OCIE0) | (0 << TOIE0)); // Ensure that interrupts are off
}

void configTimer1() // 16 bits wide, 0 -> 65535
{
	
}

void configTimer2()	// 8 bits wide, 0 -> 255
{
	TCCR2 = (1 << CS22) | (1 << CS20);
	TCNT2 = 0;
}

void debounce(){
/*
Debounce:
1. Determine start value of the switch (logic 1)
2. Wait a specified period of time (10us)
3. Check to see whether the switch is still logic 1
4. If it is, then a switch press has not been detected - maybe check again
5. If it is low, and remains low for a further 40us, then a valid key press may have been detected
*/
	// delay 10us
	tenMicSecDelay();
	current = keyScan();
	temp = 0xFF;
	
	while (current != temp)
	{
		//delay 40us
		for (i = 0; i < 4; i++) {tenMicSecDelay();}
		current = keyScan();
	}

}

void tenMicSecDelay()
{
/*
10us / 255 = 3.9e-8s (0.039 us)

8 / 12MHz = 6.67e-7s per cycle (0.667 us)
10 / 0.667 = 14.99 (8 prescaler)
therefore, timer should be set to 255-15+1 = 241 counts to reach 256 in 10us

1 / 12MHz = 8.33e-8s per cycle (0.0833 us)
10 / 0.0833 = 120.05 (no prescaler)
therefore, timer should be set to 255-120+1 = 136 counts to reach 256 in 10us
*/
	uint8_t timerCountLow = 136;
	configTimer0(0, timerCountLow);
	while (!(TIFR & (1 << TOV0)));	// wait until overflow flag is set (timer reached 256)
	TIFR |= (1 << TOV0);			// clear overflow flag
}

void tenMiliSecDelay()
{
/*
	10m / 255 = 3.9e-5s (0.039 ms)
256 / 12MHz = 2.13e-5s (0.0213 ms)

64 / 12MHz = 5.33e-6s (0.00533 ms)
10 / 0.00533 = 187.6 (64 prescaler)
therefore, timer should be set to 255-188+1 = 68 counts to reach 256 in 10ms
*/
	uint8_t timerCountLow = 68;
	configTimer0(64, timerCountLow);
	while(!(TIFR & (1 << TOV0)));
	TIFR |= (1 << TOV0);
}