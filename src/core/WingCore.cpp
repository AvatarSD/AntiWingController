/*
 * WingCore.cpp
 *
 *  Created on: 30 лист. 2015
 *      Author: sd
 */

#include "WingCore.h"

double mainTableEEMEM[SPEED_POINT][RUD_ANGLE_POINT] EEMEM =
{
{ 0, 2, 5, 10, 12, 15, 16, -1, -1, -1 },
{ 10, 0, 10, 15, 46, 55, 60, 0, 0, 0 },
{ 20, 0, 12, 18, 43, 50, 60, 0, 0, 0 },
{ 30, 0, 15, 20, 39, 47, 58, 0, 0, 0 },
{ 40, 0, 15, 25, 34, 43, 54, 0, 0, 0 },
{ 50, 0, 17, 25, 31, 40, 52, 0, 0, 0 },
{ 60, 0, 15, 22, 28, 38, 47, 0, 0, 0 },
{ 70, 0, 12, 19, 25, 33, 40, 0, 0, 0 },
{ 80, 0, 12, 17, 22, 28, 33, 0, 0, 0 },
{ 90, 0, 9, 15, 20, 23, 28, 0, 0, 0 } };

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
	float speedPos = 0, anglePos = 0;

	if (speed <= mainTableBuff[1][0])
		speedPos = 1;
	else if (speed >= mainTableBuff[SPEED_POINT - 1][0])
		speedPos = SPEED_POINT - 1;
	else
		for (unsigned char i = 1; i < SPEED_POINT - 1; i++)
			if ((mainTableBuff[i][0] < speed)
					&& (mainTableBuff[i + 1][0] >= speed))
				speedPos = (mainTableBuff[i + 1][0] - mainTableBuff[i][0])
						/ (speed - mainTableBuff[i][0]) + i;

	if (rudAngel <= mainTableBuff[0][1])
		speedPos = 1;
	else if (rudAngel >= mainTableBuff[0][RUD_ANGLE_POINT - 1])
		speedPos = RUD_ANGLE_POINT - 1;
	else
		for (unsigned char i = 1; i < RUD_ANGLE_POINT - 1; i++)
			if ((mainTableBuff[0][i] < rudAngel)
					&& (mainTableBuff[0][i + 1] >= rudAngel))
				speedPos = (mainTableBuff[0][i + 1] - mainTableBuff[0][i])
						/ (rudAngel - mainTableBuff[0][i]) + i;

	/************/ //TODO
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

bool setPoint(unsigned char speedPos, unsigned char rudAnglePos, double speed)
{
	mainTableBuff[speedPos + 1][rudAnglePos + 1] = speed;
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
