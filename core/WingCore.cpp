/*
 * WingCore.cpp
 *
 *  Created on: 30 лист. 2015
 *      Author: sd
 */

#include "WingCore.h"

double mainTableEEMEM[SPEED_POINT][RUD_ANGLE_POINT] EEMEM;
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
	/*
	 * 1. ok - found 4 points
	 * 2. get 4 point data
	 * 3. found mediate data
	 */

	float speedPos, anglePos;

	if (speed <= mainTableBuff[1][0])
	{
		speedPos = 1;
	}

	else if (speed >= mainTableBuff[SPEED_POINT - 1][0])
	{
		speedPos = SPEED_POINT - 1;
	}
	else
		for (char i = 1; i < SPEED_POINT - 1; i++)
			if ((mainTableBuff[i][0] < speed)
					&& (mainTableBuff[i + 1][0] >= speed))
				speedPos = (mainTableBuff[i + 1][0] - mainTableBuff[i][0])
						/ (speed - mainTableBuff[i][0]) + i;

	if (rudAngel <= mainTableBuff[0][1])
	{
		speedPos = 1;
	}

	else if (rudAngel >= mainTableBuff[0][RUD_ANGLE_POINT - 1])
	{
		speedPos = RUD_ANGLE_POINT - 1;
	}
	else
		for (char i = 1; i < RUD_ANGLE_POINT - 1; i++)
			if ((mainTableBuff[0][i] < rudAngel)
					&& (mainTableBuff[0][i + 1] >= rudAngel))
				speedPos = (mainTableBuff[0][i + 1] - mainTableBuff[0][i])
						/ (rudAngel - mainTableBuff[0][i]) + i;



/************/ //TODO


}

bool setSpeedRange(unsigned char pos, double speed)
{
	mainTableBuff[pos][0] = speed;
	saveBuffTable();
	return true;
}

bool setRudRange(unsigned char pos, double rudAngle)
{
	mainTableBuff[0][pos] = rudAngle;
	saveBuffTable();
	return true;
}

bool setPoint(unsigned char speedPos, unsigned char rudAnglePos, double speed)
{
	mainTableBuff[speedPos + 1][rudAnglePos + 1] = speed;
	saveBuffTable();
	return true;
}
