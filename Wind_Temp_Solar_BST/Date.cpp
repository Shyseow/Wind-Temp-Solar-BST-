#include "Date.h" //include header file
#include <iostream>
#include <cstdlib>

using namespace std;

Date::Date() //default constructor
{
    day=1;
    month=5;
    year=2001;
}

Date::Date(int dd,int mm,int yy) //parameterized constructor
{
    day = dd;
    month = mm;
    year = yy;

}

//Setters
void Date::SetDay(int dd) //returnType class name::MethodName(vars)
{
    day=dd;
}

void Date::SetMonth(int mm)
{
    month=mm;
}

void Date::SetYear(int yy)
{
    year=yy;
}

void Date::SetDate(int dd, int mm, int yy)
{
    day   = dd;
    month = mm;
    year  = yy;
}


int Date::GetDay() const
{
    return day;
}

int Date::GetMonth() const
{
    return month;
}

int Date::GetYear() const
{
    return year;
}

string Date::getFullMonth(int iMonth)
{
	string sReturn = "";

	if (iMonth == 1)
	{
		sReturn = "January";
	}
	else if (iMonth == 2)
	{
		sReturn = "Feburary";
	}
	else if (iMonth == 3)
	{
		sReturn = "March";
	}
	else if (iMonth == 4)
	{
		sReturn = "April";
	}
	else if (iMonth == 5)
	{
		sReturn = "May";
	}
	else if (iMonth == 6)
	{
		sReturn = "June";
	}
	else if (iMonth == 7)
	{
		sReturn = "July";
	}
	else if (iMonth == 8)
	{
		sReturn = "August";
	}
	else if (iMonth == 9)
	{
		sReturn = "September";
	}
	else if (iMonth == 10)
	{
		sReturn = "October";
	}
	else if (iMonth == 11)
	{
		sReturn = "November";
	}
	else if (iMonth == 12)
	{
		sReturn = "December";
	}

	return sReturn;
}

ostream& operator<<(ostream& osObject, const Date& date)//overloading of output operator
{
   osObject<<date.GetDay()<<"/"<<date.GetMonth()<<"/"<<date.GetYear();

   return osObject;
}

istream& operator>>(istream& isObject,Date& date)//overloading of input operator
{
    int dd,mm,yy;
    isObject>>dd>>mm>>yy; //to take values from the stream

    date.SetDay(dd);
    date.SetMonth(mm);
    date.SetYear(yy);

    return isObject;
}
