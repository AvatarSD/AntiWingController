/*
 * WingCore.h
 *
 *  Created on: 30 лист. 2015
 *      Author: sd
 */

#ifndef CORE_WINGCORE_H_
#define CORE_WINGCORE_H_

#include <avr/eeprom.h>

#define SPEED_POINT 10
#define RUD_ANGLE_POINT 10


double getWingAnglePoint(double speed, double rudAngel);
bool setSpeedRange(unsigned char pos, double speed);
bool setRudRange(unsigned char pos, double rudAngle);
bool setPoint(unsigned char speedPos, unsigned char rudAnglePos, double speed);



#endif /* CORE_WINGCORE_H_ */
