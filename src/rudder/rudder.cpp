/*
 * rudder.cpp
 *
 *  Created on: 1 груд. 2015
 *      Author: sd
 */

#include "rudder.h"
#include "ADC/Analog.h"
#include "math.h"

#define MEDIATE  512
#define K 4

//rudder::rudder()
//{
//	// TODO Auto-generated constructor stub
//
//}
//
//rudder::~rudder()
//{
//	// TODO Auto-generated destructor stub
//}

double getAngel()
{
	return (((double)analog[0] - MEDIATE) / K);
}
