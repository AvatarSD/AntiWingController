/*
 * WingCore.h
 *
 *  Created on: 30 лист. 2015
 *      Author: sd
 */

#ifndef CORE_WINGCORE_H_
#define CORE_WINGCORE_H_


#define SPEED_POINT 10
#define RUD_ANGLE_POINT 10


double getWingAnglePoint(double speed, double rudAngel);
bool setSpeedRange(unsigned char pos, double speed);
bool setRudRange(unsigned char pos, double rudAngle);
bool setPoint(unsigned char speedPos, unsigned char rudAnglePos, double wingAngle);


void loadBuffTable();
void saveBuffTable();
void sortSpeedRange();
void sortRudRange();

#endif /* CORE_WINGCORE_H_ */
