/*
 * SerialIface.cpp
 *
 *  Created on: 1 груд. 2015
 *      Author: sd
 */

#include "avr/io.h"
#include "avr/interrupt.h"
#include "SerialIface.h"

SerialIface port;

ISR(USART_RX_vect)
{
	port.rx_byte_int();
}
ISR(USART_TX_vect)
{
	port.tx_byte_int();
}

SerialIface::SerialIface() : UART(UDR0, 115200, 128, 8)
{
	// TODO Auto-generated constructor stub

}

SerialIface::~SerialIface()
{
	// TODO Auto-generated destructor stub
}

