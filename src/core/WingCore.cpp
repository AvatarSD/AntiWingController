/*
 * WingCore.cpp
 *
 *  Created on: 30 лист. 2015
 *      Author: sd
 */

#include "WingCore.h"
#include <avr/eeprom.h>

#include "../serial/SerialIface.h"
#include "util/delay.h"

double mainTableEEMEM[SPEED_POINT][RUD_ANGLE_POINT] EEMEM =
{
{ 0, 2, 5, 10, 12, 15, 16, 18, 20, 25 },
{ 10, 9, 10, 15, 46, 55, 60, 65, 68, 72 },
{ 20, 8, 12, 18, 43, 50, 60, 63, 65, 70 },
{ 30, 7, 15, 20, 39, 47, 58, 60, 63, 65 },
{ 40, 6, 15, 25, 34, 43, 54, 57, 59, 62 },
{ 50, 5, 17, 25, 31, 40, 52, 52, 53, 58 },
{ 60, 4, 15, 22, 28, 38, 47, 39, 47, 53 },
{ 70, 3, 12, 19, 25, 33, 40, 42, 45, 47 },
{ 80, 2, 12, 17, 22, 28, 33, 34, 37, 42 },
{ 90, 1, 9, 15, 20, 23, 28, 31, 34, 37 } };

double mainTableBuff[SPEED_POINT][RUD_ANGLE_POINT];

void loadBuffTable()
{
	eeprom_read_block(mainTableBuff, mainTableEEMEM,
	SPEED_POINT * RUD_ANGLE_POINT * sizeof(double));
}

void saveBuffTable()
{
	eeprom_write_block(mainTableBuff, mainTableEEMEM,
	SPEED_POINT * RUD_ANGLE_POINT * sizeof(double));
}

double getWingAnglePoint(double speed, double rudAngel)
{
	float speedPos = 1, anglePos = 1;

	if (speed <= mainTableBuff[1][0])
		speedPos = 1;
	else if (speed >= mainTableBuff[SPEED_POINT - 1][0])
		speedPos = SPEED_POINT - 1;
	else
		for (unsigned char i = 1; i < SPEED_POINT - 1; i++)
			if ((mainTableBuff[i][0] < speed)
					&& (mainTableBuff[i + 1][0] >= speed))
				speedPos = ((speed - mainTableBuff[i][0])
						/ (mainTableBuff[i + 1][0] - mainTableBuff[i][0])) + i;

	if (rudAngel <= mainTableBuff[0][1])
		anglePos = 1;
	else if (rudAngel >= mainTableBuff[0][RUD_ANGLE_POINT - 1])
		anglePos = RUD_ANGLE_POINT - 1;
	else
		for (unsigned char i = 1; i < RUD_ANGLE_POINT - 1; i++)
			if ((mainTableBuff[0][i] < rudAngel)
					&& (mainTableBuff[0][i + 1] >= rudAngel))
				anglePos = ((rudAngel - mainTableBuff[0][i])
						/ (mainTableBuff[0][i + 1] - mainTableBuff[0][i])) + i;

	/************/
	//TODO
	/*
	 * 1. ////////ok - found 4 points
	 * 2. get 4 point data
	 * 3. found mediate data
	 */

	return mainTableBuff[(long int) speedPos][(long int) anglePos];
}

bool setSpeedRange(unsigned char pos, double speed)
{
	mainTableBuff[pos][0] = speed;
	sortSpeedRange();
	saveBuffTable();
	return true;
}

bool setRudRange(unsigned char pos, double rudAngle)
{
	mainTableBuff[0][pos] = rudAngle;
	sortRudRange();
	saveBuffTable();
	return true;
}

bool setPoint(unsigned char speedPos, unsigned char rudAnglePos, double wingAngle)
{
	mainTableBuff[speedPos + 1][rudAnglePos + 1] = wingAngle;
	saveBuffTable();
	return true;
}

void sortSpeedRange()
{
	//todo sort range speed
}

void sortRudRange()
{
	//todo sort range rud
}
