/*
 * main.cpp
 *
 *  Created on: 11 лист. 2015
 *      Author: sd
 */

#include "math.h"
#include "avr/interrupt.h"
/*Serial Iface*/
#include "serial/SerialIface.h"
/*Input*/
#include "rudder/rudder.h"
#include "speed/Speed.h"
/*Main Table*/
#include "core/WingCore.h"
/*Output*/
#include "output/OutputControl.h"


int main()
{
	setupPWMoutput();
	setupSpeedSensor();

	loadBuffTable();

	sei();

	while (1)
	{
		setWingAngle(getWingAnglePoint(getSpeed(), fabs(getAngel())));

//		setWingAngle(getSpeed()*2);
//				port(F("Speed: "));
//				port((long int)getSpeed());
//				port("\t");
//				port(F("Angel: "));
//				port((long int)getAngel());
//				port("\r\n");


//		for(int i = 0; i < 150; i++)
//			for(int k = 0; k < 20; k++)
//			{
////				port(F("Speed: "));
////				port(i);
////				port("\t");
////				port(F("Angel: "));
////				port(k);
////				port("\t");
////				port(F("WingAngel: "));
////				port((long int)
//				setWingAngle(getWingAnglePoint(i,k));//);
////				port("\r\n");
////
//			}
	}

	return 0;
}
