/*
 * ServoPWM.cpp
 *
 *  Created on: 28 лист. 2015
 *      Author: sd
 */

#include "ServoPWM.h"
#include "avr/io.h"

void setup()
{
	// Timer/Counter 1 initialization
	// Clock source: System Clock
	// Clock value: 250,000 kHz
	// Mode: Fast PWM top=ICR1
	// OC1A output: Non-Inverted PWM
	// OC1B output: Non-Inverted PWM
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer Period: 50 ms
	// Output Pulse(s):
	// OC1A Period: 50 ms Width: 1,5001 ms
	// OC1B Period: 50 ms Width: 1,5001 ms
	// Timer1 Overflow Interrupt: Off
	// Input Capture Interrupt: Off
	// Compare A Match Interrupt: Off
	// Compare B Match Interrupt: Off
	TCCR1A = (1 << COM1A1) | (0 << COM1A0) | (1 << COM1B1) | (0 << COM1B0)
			| (1 << WGM11) | (0 << WGM10);
	TCCR1B = (0 << ICNC1) | (0 << ICES1) | (1 << WGM13) | (1 << WGM12)
			| (0 << CS12) | (1 << CS11) | (1 << CS10);
	TCNT1H = 0x00;
	TCNT1L = 0x00;
	ICR1H = 0x30;
	ICR1L = 0xD3;
	OCR1AH = 0x01;
	OCR1AL = 0x77;
	OCR1BH = 0x01;
	OCR1BL = 0x77;

	DDRB = (1 << DDB2) | (1 << DDB1);
}

void setOutputA(int position)
{
//	if (position > 250)
//		position = 250;
//	if (position < 0)
//		position = 0;

	OCR1A = position;// + 125;
}

void setOutputB(int position)
{
	if (position > 250)
		position = 250;
	if (position < 0)
		position = 0;

	OCR1B = position + 125;
}
