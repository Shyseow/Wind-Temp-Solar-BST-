/* The TotalW class Header (TotalW.h) */
//---------------------------------------------------------------------------------
	/**
	 * @class  TotalW
     * @file   TotalW.h
     * @brief  Declaration for function and variables; and macro definition is made
     *         in this class. This class used to manage the calculations
     *
	 * @author Seow Hui Yin
	 * @version 1.0
	 * @date submission : 23/07/2018
     */
//---------------------------------------------------------------------------------
#ifndef TOTALW_H_INCLUDED
#define TOTALW_H_INCLUDED
//---------------------------------------------------------------------------------
#include <iostream>

//TotalW class declaration
class  TotalW
{
public:
    // Declare member function prototypes
    //--constructors
    /**
     * @brief  Default constructor with no parameters to initialize the variables
     *         To set the initial value of the data member variables
     *         with default value
     */
     TotalW();

    /**
     * @brief  Parameterized constructor with parameters to initialize the variables
     *         with given value in Date class
     *         To set the initial value of the member variables with given value
	 *
     * @param  integer - float of wind speed, solar radiation and air temperature
     *
     */
	 TotalW(float wSpeed, float sRaditation, float AirTemp);

	 /**
	 * @brief  Destructor of the Class TotalWRT.
	 */
	~ TotalW();

    /**
	 * @brief To get the total value of wind speed
	 *
	 * @return value of wind speed variable in float
	 *
	 */
	float getTotalSpeed();

    /**
	 * @brief To get the total value of solar radiation
	 *
	 * @return value of solar radiation variable in float
	 *
	 */
	float getTotalRaditation();

    /**
	 * @brief To get the total value of air temperature
	 *
	 * @return value of air temperature variable in float
	 *
	 */
	float getTotalTemperature();

	/**
	* @brief  Function that overload the operator +
	*         The + (plus) operator is redefined in this class to add two objects
	*
	* @return TotalW
	*/
	void operator+(TotalW &);


private:
    // private data members (variables)
	float wSpeed;
	float sRaditation;
	float AirTemp;

};


#endif // TOTALW_H_INCLUDED

