/*
 * SerialIface.h
 *
 *  Created on: 1 груд. 2015
 *      Author: sd
 */

#ifndef SERIAL_SERIALIFACE_H_
#define SERIAL_SERIALIFACE_H_

#include "UART/UART.h"

class SerialIface : public UART
{
public:
	SerialIface();
	~SerialIface();
};

extern SerialIface port;

#endif /* SERIAL_SERIALIFACE_H_ */
