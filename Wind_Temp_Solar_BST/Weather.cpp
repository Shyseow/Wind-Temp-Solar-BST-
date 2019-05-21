#include "Weather.h"
#include "Time.h"
#include "Date.h"
#include <map>;

Weather::Weather()
{
    windSpeed      = 0;
    solarRadiation = 0;
    Atemp          = 0;
}

Weather::Weather(Date objDate, Time objTime, float windSpeed, float solarRadiation, float Atemp):
	objDate(objDate), objTime(objTime), windSpeed(windSpeed), solarRadiation(solarRadiation), Atemp(Atemp)
{

}

void Weather::SetWindspeed(float Ws)
{
    windSpeed = Ws;
}
void Weather::SetSolarRadiation(float SR)
{
    solarRadiation = SR;
}
void Weather::SetAirTemp(float T)
{
    Atemp = T;
}
void Weather::SetAll(int dd, int mth, int yy, int mm, int hh, float Ws, float SR, float T)
{
    objDate.SetDate(dd,mth,yy);
    objTime.SetTime(hh, mm);
    windSpeed      = Ws;
    solarRadiation = SR;
    Atemp        = T;
}

void Weather::SetTime(Time t)
{
    objTime = t;
}

void Weather::SetDate(Date d)
{
    objDate = d;
}


float Weather::GetWindspeed() const
{
    return windSpeed;
}
float Weather::GetSolarRadiation() const
{
    return solarRadiation;
}

float Weather::GetAirTemp() const
{
    return Atemp;
}


int Weather::GetMonth() const
{
    return objDate.GetMonth();
}

int Weather::GetYear() const
{
    return objDate.GetYear();
}

Date Weather::GetDate() const //Date&
{
    return objDate;
}

Time Weather::GetTime() const
{
    return objTime;
}

ostream &operator << (ostream& os,const Weather &m)
{
    os << m.GetWindspeed() << m.GetSolarRadiation() << m.GetAirTemp() << m.GetDate() << m.GetTime();
    return os;
}

istream &operator >> (istream& input, Weather &m)
{
    int dd,mth,yy,mm,hh;
    float Ws,SR,T;
    Date d;
    Time t;

    input >>dd>>mth>>yy>>hh>>mm>>Ws>>SR>>T>>d>>t;

    m.SetWindspeed(Ws);
    m.SetSolarRadiation(SR);
    m.SetAirTemp(T);
    m.SetDate(d);
    m.SetTime(t);

    return input;
}

