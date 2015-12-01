/*
 * speedsensor.cpp
 *
 *  Created on: 28 лист. 2015
 *      Author: sd
 */

#include "speedsensor.h"
#include "avr/io.h"
#include "avr/interrupt.h"

#define MIN_SPEED 4
#define TIM_PERIOD 0.00001

volatile long long unsigned int counterA, counterB, snapA, snapB;
double speedA, speedB;

ISR(INT0_vect)
{
//	cli();
	snapA = counterA;
	counterA = 0;
//	sei();
}

ISR(INT1_vect)
{
	//cli();
	snapB = counterB;
	counterB = 0;
	//sei();
}

ISR(TIMER2_COMPA_vect)
{
	//cli();
	counterA++;
	counterB++;
	//sei();
}

void setupSpeedSensor()
{
	// External Interrupt(s) initialization
	// INT0: On
	// INT0 Mode: Rising Edge
	// INT1: On
	// INT1 Mode: Rising Edge
	EICRA = (1 << ISC11) | (1 << ISC10) | (1 << ISC01) | (1 << ISC00);
	EIMSK = (1 << INT1) | (1 << INT0);
	EIFR = (1 << INTF1) | (1 << INTF0);

	// Timer/Counter 2 initialization
	// Clock source: System Clock
	// Clock value: 16000,000 kHz
	// Mode: CTC top=OCR2A
	// OC2A output: Disconnected
	// OC2B output: Disconnected
	// Timer Period: 0,01 ms
	ASSR = (0 << EXCLK) | (0 << AS2);
	TCCR2A = (0 << COM2A1) | (0 << COM2A0) | (0 << COM2B1) | (0 << COM2B0)
			| (1 << WGM21) | (0 << WGM20);
	TCCR2B = (0 << WGM22) | (0 << CS22) | (0 << CS21) | (1 << CS20);
	TCNT2 = 0x00;
	OCR2A = 0x9F;
	OCR2B = 0x00;

	// Timer/Counter 2 Interrupt(s) initialization
	TIMSK2 = (0 << OCIE2B) | (1 << OCIE2A) | (0 << TOIE2);

	counterA = 1 / (TIM_PERIOD*MIN_SPEED);
	counterB = 1 / (TIM_PERIOD*MIN_SPEED);
}

double getSpeedA()
{
	if (counterA >= 1 / (TIM_PERIOD*MIN_SPEED))
		return 0;
	return ((double) 1 / ((double) TIM_PERIOD * snapA));
	//return snapA;
}

double getSpeedB()
{
	if (counterB >= 1 / (TIM_PERIOD*MIN_SPEED))
		return 0;
	return ((double) 1 / ((double) TIM_PERIOD * snapB));
}
