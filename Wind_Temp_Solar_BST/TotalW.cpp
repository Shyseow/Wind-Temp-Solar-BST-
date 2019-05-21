#include "TotalW.h" //include header file
#include <iostream>
#include <cstdlib>

TotalW::TotalW() //default constructor
{
    wSpeed = 0;
    sRaditation = 0;
    AirTemp = 0;
}

TotalW::TotalW(float wSpeedData, float sRaditationData, float AirTempData)//parameterized constructor
{
    wSpeed = wSpeedData;
    sRaditation = sRaditationData;
    AirTemp = AirTempData;
}

TotalW::~TotalW()//Destructor
{
}

//Getters
float TotalW::getTotalSpeed()
{
	return wSpeed;
}

float TotalW::getTotalRaditation()
{

	return sRaditation;
}

float TotalW::getTotalTemperature()
{
	return AirTemp;
}

//Function that overload the operator +
//Objects of this classes are added everytime based on the input entries.
void TotalW::operator+(TotalW &objSecond) {
	wSpeed = wSpeed + objSecond.wSpeed;
	AirTemp = AirTemp + objSecond.AirTemp;
	//Checking if the solar radiation is higher than 100
	if (objSecond.sRaditation >= 100)
	{
		sRaditation = sRaditation + objSecond.sRaditation;
	}
}


