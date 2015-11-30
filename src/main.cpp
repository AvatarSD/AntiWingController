/*
 * main.cpp
 *
 *  Created on: 11 лист. 2015
 *      Author: sd
 */

#include "avr/io.h"
#include "avr/interrupt.h"

#include "UART/UART.h"
#include "ADC/Analog.h"
#include "PWM/ServoPWM.h"
#include "speedsensor/speedsensor.h"

#include "util/delay.h"

UART port(UDR0, 115200, 128, 8);
ISR(USART_RX_vect)
{
	port.rx_byte_int();
}
ISR(USART_TX_vect)
{
	port.tx_byte_int();
}

int main()
{
	setup();
	setupSpeedSensor();

	sei();

	while (1)
	{
//		for (int i = 0; i < 250; i++)
//		{
//			setOutputA(i);
//			_delay_ms(10);
//		}
//		for (int i = 250; i > 0; i--)
//		{
//			setOutputA(i);
//			_delay_ms(10);
//		}
		//setOutputA(analog[0]);
		//setOutputA((long int)getSpeedA());
		port("Analog0: ");
		port(analog[0]);
		port("\t");
		port("Analog1: ");
		port(analog[1]);
		port("\t");
		port("Analog2: ");
		port(analog[2]);
		port("\t");
		port("Analog3: ");
		port(analog[3]);
		port("\t");
		port("Analog4: ");
		port(analog[4]);
		port("\t");
		port("Speed A: ");
		port((long int) (getSpeedA() * 60));
		port("\r\n");
	}

	return 0;
}
