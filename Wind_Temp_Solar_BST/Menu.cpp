#include "Menu.h"

Menu::Menu()
{
    ifstream myfile (filename.c_str()); //input file stream

    if (!myfile)
    {
        cout << "No data file found!!" << endl;
    }else{
    read();
    choice();
    }
}

Menu::Menu(string fn)
{
    filename = fn;
    ifstream myfile (filename.c_str());


    if (!myfile)
    {
        cout << "No data file found!!" << endl;
    }else{
    read();
    choice();
    }
}


void Menu::read()
{

	list<string> sFile; // creating this list to keep the name of the files in the input text file
	string sFilename = "data/met_index.txt"; // data file location
	string sDay, sMonth, sYear, sHH, sMM, sTempData, sSpeed, sSR, sT; //Variables
	string readFileName, sDateTime, keyYear;
	Weather *objWeather;

	bool isFirstRow = false;

		ifstream file;
		file.open(sFilename.c_str());

		while (!file.eof())
		{
			getline(file, readFileName);
			sFile.push_back(readFileName); // pushing file names from the input sheet to a list.

		}

		file.close();
        // start data loading
       cout << "Loading data......"<< endl;
       cout << " " << endl;

		//Looping through the list to get the individual file name and then push to vector
		for (list<string>::iterator it = sFile.begin(); it != sFile.end(); ++it)
		{
			if (*it != "")
			{
				sFilename = "data/" + *it;
				cout << ' ' <<"Loading file "<< sFilename <<endl;
				Vector <Weather*> objWVector;

				isFirstRow = false;
				keyYear = "";


				ifstream file;
				file.open(sFilename.c_str());
				file.ignore(64, '\n');

				while (file.good())
				{
					getline(file, sDay, '/');
					getline(file, sMonth, '/');
					getline(file, sYear, ' ');
					getline(file, sHH, ':');
					getline(file, sMM, ',');

					sDateTime = sDay + "/" + sMonth + "/" + sYear + " " + sHH + ":" + sMM;


					//Skip unused data
					getline(file, sTempData, ',');
					getline(file, sTempData, ',');
					getline(file, sTempData, ',');
					getline(file, sTempData, ',');
					getline(file, sTempData, ',');
					getline(file, sTempData, ',');
					getline(file, sTempData, ',');
					getline(file, sTempData, ',');
					getline(file, sTempData, ',');


					//read speed and SolarRadiation value
					getline(file, sSpeed, ',');
					getline(file, sSR, ',');

					//Skip unused data
					getline(file, sTempData, ',');
					getline(file, sTempData, ',');
					getline(file, sTempData, ',');
					getline(file, sTempData, ',');
					getline(file, sTempData, ',');
					getline(file, sT);

					if (!isFirstRow)
					{
						keyYear = sYear;
						isFirstRow = true;
					}
					//All N/A values will be replaced with zero. Ternary operator is used to assign value.
					sSpeed = sSpeed == "N/A" ? "0" : sSpeed;
					sSR = sSR == "N/A" ? "0" : sSR;
					sT = sT == "N/A" ? "0" : sT;


					//Inserting the DateTime combination to a BST to check for the duplicates, and if is Empty
					bool isReturn= true;
					objBTree.insert(sDateTime);
					objBTree.isEmpty();

					//inserting row to a vector
					if (isReturn)

					{
						Date objDate(atoi(sDay.c_str()), atoi(sMonth.c_str()), atoi(sYear.c_str()));
						Time objTime(atoi(sMM.c_str()), atoi(sHH.c_str()));
						objWeather = new Weather(objDate, objTime, stof(sSpeed.c_str()), stof(sSR.c_str()), stof(sT.c_str()));
						objWVector.push_back(objWeather);
						isReturn=true;
					}

				}
				 //creating a map with the key as Year and Vector as value.
				myMap.insert(pair<string, Vector<Weather*>>(keyYear, objWVector));

				file.close();
			}
		}

}

////////////////////////////////////////////////////////////////////////////////////////
/// Menu for user to select option and perform different task accordingly to selection
///////////////////////////////////////////////////////////////////////////////////////
void Menu::choice()
{
    // to print out the options if the source document is found
    cout << "----------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t                  Menu"                                                                   << endl;
    cout << "----------------------------------------------------------------------------------------------" << endl;
    cout << "1 - The average wind speed and average ambient air temperature for a specified month and year." << endl;
    cout << "2 - Average wind speed and average ambient air temperature for each month of a specified year." << endl;
    cout << "3 - Total solar radiation in kWh/m^2 for each month of a specified year."                       << endl;
    cout << "4 - Average wind speed(km/h),average ambient air temperature and total solar radiation in "     <<endl;
    cout << "    kWh/m^2 for each month of a specified year.(print to a file called WindTempSolar.csv)"      << endl;
    cout << "5 - Highest solar radiation for the given date . Enter date in the form of d/m/yyyy"            << endl;
    cout << "6 - Exit the Program."                                                                          << endl;
    cout << endl;

    int choice = enterOption();

    while (choice != 6)
    {
        switch (choice)
        {
            case 1:
                option1();
                break;
            case 2:
                option2();
                break;
            case 3:
                option3();
                break;
            case 4:
                option4();
                break;
            case 5:
                option5();
                break;
            case 6:
                option6();
                break;
            default:
                cout<< "Please re-enter your selection (1-6): "<<endl;
                break;
        } // end of switch
        choice = enterOption();
    } // end of while loop


}

/////////////////////////////////////////////////////////////
/// Method to validate user input selection for menu option
////////////////////////////////////////////////////////////
int Menu::enterOption()
{
    int tempIn;
    cout << "Enter your selection : " << endl;
    cin  >> tempIn;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore();
        cout<< endl;
        cout << "Please re-enter your selection (1-6): " << endl;
        cin  >> tempIn;
    }

    return tempIn;
}

////////////////////////////////////////
/// Method to validate user input month
////////////////////////////////////////
int Menu::enterMonth()
{
    int  Month;
    bool flag = false;

    while (flag == false)
    {
        cout << "Please enter a month : "<< endl;
        cin  >> Month;

        if(cin.fail())
        {
            cout << "Please re-enter your selection (1-5) : " << endl;
            cin.clear();
            cin.ignore(10000,'\n');
        } else if (Month < 1 || Month >12){
            cout << "Month range is from 1 to 12."<< endl;
            cin.clear();
            cin.ignore(10000,'\n');
        } else {
            flag = true;
        }// end of if
    } // end of while loop
    return Month;
}

////////////////////////////////////////
/// Method to validate user input year
////////////////////////////////////////
int Menu::enterYear()
{
    int  Year;
    bool flag = false;

    while (flag == false)
    {
        cout << "Please enter year: " << endl;
        cin  >> Year;

        if(cin.fail())
        {
            cout << "Please re-enter your selection : " << endl;
            cin.clear();
            cin.ignore(10000,'\n');
        } else if (Year < 1000){
            cout << "Please enter more than 1000 "<< endl;
            cin.clear();
            cin.ignore(10000,'\n');
        } else {
            flag = true;
        }// end of if
    } // end of while loop
    return Year;
}

////////////////////////////////////////////////////////////////////////////////////////////
/// --- Option 1 --- (Average wind speed and air temperature of a specified month and year)
/// Method to perform calculation, output result and validate user input for year and month
///////////////////////////////////////////////////////////////////////////////////////////
void Menu::option1()
{
    int isYear  = enterYear();
    int isMonth = enterMonth();
    int countSum = 0;
    float tempWindspeedSum = 0;
    float tempAirTempSum   = 0;
	list<string> sFile;
    Vector<Weather*> myObj;
    Date objDate;
    NodeBST <float> WeatherBST;

	//Outer loop to go through all input data and insert to map
	sFile.push_back(to_string(isYear - 1));
	sFile.push_back(to_string(isYear));
	sFile.push_back(to_string(isYear + 1));


    list<string>::iterator it;
	for (it = sFile.begin(); it != sFile.end(); ++it)
	{
		string inputYear = *it;
		map<string, Vector<Weather*>>::iterator iter = myMap.find(*it);


		if (iter != myMap.end())
		{
			Vector<Weather*> localWeather = myMap.find(inputYear)->second;

			for (int i = 0; i < localWeather.getPosition(); i++)
			{
				Weather *objData;
				objData = localWeather.at(i);
                //WeatherBST.insert(objData->GetSolarRadiation());
				//objData->GetSolarRadiation();
				myObj.push_back(objData);



			}
		}
	}

    for(int i =0; i < myObj.getPosition(); i++)
    {
        	Weather *objData;
            objData = myObj.at(i);

         if(myObj.at(i)->GetYear() == isYear)
         {
            if(myObj.at(i)->GetMonth() == isMonth)
                {
                   tempWindspeedSum += objData->GetWindspeed();
                   WeatherBST.insert(objData->GetWindspeed());
                   tempAirTempSum   += objData->GetAirTemp();
                   WeatherBST.insert(objData->GetAirTemp());

                    countSum++;
                }// end of inner if loop
        } //end of outer if loop
    }// end of for loop

    if (tempWindspeedSum ==0 && tempAirTempSum==0)
        cout << objDate.getFullMonth(isMonth) << " " << isYear << " : " << " " << "No Data" << endl;
    else {
        cout << "Average wind speed and ambient air temperature for " << "'" << objDate.getFullMonth(isMonth)<< " " << isYear<< "'" << ":" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << objDate.getFullMonth(isMonth)<< " " << isYear << " : " << fixed << showpoint << setprecision(1) << tempWindspeedSum/countSum <<" km/h "
             << "," << fixed << showpoint << setprecision(1) << tempAirTempSum/countSum << " degrees C" <<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }// end of if loop
}

//////////////////////////////////////////////////////////////////////////////////
/// --- Option 2 --- (Average wind speed and air temperature of a specified year)
/// Method to perform calculation, output result and validate user input for year
/////////////////////////////////////////////////////////////////////////////////
void Menu::option2()
{
    bool isDataFound = false;
	int iTotalMonthCount = 0, iYear = 0;
	Date objDate;
	string sYear;
	float fAvgWind = 0, fAvgTemp = 0;
	list<string> sFile;


	cout << "Please enter the year" << endl;
	cin >> sYear;

	cout << fixed << showpoint << setprecision(2);

	//Outer loop to go through all input data and insert to map
	iYear = atoi(sYear.c_str());
	sFile.push_back(to_string(iYear - 1));
	sFile.push_back(to_string(iYear));
	sFile.push_back(to_string(iYear + 1));

	Vector<Weather*> myObj;

	for (std::list<string>::iterator it = sFile.begin(); it != sFile.end(); ++it)
	{
		string inputYear = *it;
		map<string, Vector<Weather*>>::iterator iter = myMap.find(*it);

		if (iter != myMap.end())
		{
			Vector<Weather*> localWeather = myMap.find(inputYear)->second;

			for (int iIdx = 0; iIdx < localWeather.getPosition(); iIdx++)
			{
				Weather *objData;
				objData = localWeather.at(iIdx);
				myObj.push_back(objData);
			}
		}
	}

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Average wind speed & air temperature of the year "<< sYear <<" :" << endl;
    cout << "----------------------------------------------------------------" << endl;

			for (int iMonth = 1; iMonth <=12; iMonth++)
			{
				//Constructor of TotalWRT class is initialized with 0,0,0 and is added with the input value every time.
				TotalW objTotalDetail(0, 0, 0);
				iTotalMonthCount = 0;


				for (int iIdx = 0; iIdx < myObj.getPosition(); iIdx++)
				{
					Weather *objData;
					objData = myObj.at(iIdx);
					Date objInnerDate = objData->GetDate();

					//Checking user input is valid for year
					if (to_string(objInnerDate.GetYear()) == sYear)
					{
						if (to_string(objInnerDate.GetMonth()) == to_string(iMonth))
						{
							TotalW TotalWRTChild(objData->GetWindspeed(), objData->GetSolarRadiation(), objData->GetAirTemp());
							objTotalDetail + TotalWRTChild;
							iTotalMonthCount += 1;
						}
					}
				}

				//Check if the output of the calculation is more than zero
				//Date class getFullMonth function is used to display the user input for monthName
				if (objTotalDetail.getTotalSpeed() > 0)
				{
					fAvgWind = objTotalDetail.getTotalSpeed()/ (float)iTotalMonthCount;
					fAvgTemp = objTotalDetail.getTotalTemperature() / (float)iTotalMonthCount;

					cout << fixed << showpoint << setprecision(1) << setw(12)<< objDate.getFullMonth(iMonth) + "  :"
					<< fAvgWind << " km/h " <<","<< setw(5)<< fAvgTemp << " degree C" << endl;
				}

	else
	{
		cout << fixed << showpoint << setprecision(1)<<setw(12)<< objDate.getFullMonth(iMonth)+ " :" << setw(12) <<"No Data" << endl;
	}
	}
	    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/// --- Option 3 --- (Total solar radiation in kWh/m2 of a specified year)
/// Method to perform calculation and conversion, output result and validate user input for year
/////////////////////////////////////////////////////////////////////////////////////////////////
void Menu::option3()
{

	bool isDataFound = false;
	list<string> sFile;
	int iYear = 0;
	string sYear;
	Date objDate;

	cout << "Please enter the year" << endl;
	cin >> sYear;

	cout << fixed << showpoint << setprecision(2);

	//Outer loop to go through all input data and insert to map
	iYear = atoi(sYear.c_str());
	sFile.push_back(to_string(iYear - 1));
	sFile.push_back(to_string(iYear));
	sFile.push_back(to_string(iYear + 1));

	Vector<Weather*> myObj;

	for (std::list<string>::iterator it = sFile.begin(); it != sFile.end(); ++it)
	{
		string inputYear = *it;
		map<string, Vector<Weather*>>::iterator iter = myMap.find(*it);

		if (iter != myMap.end())
		{
			Vector<Weather*> localWeather = myMap.find(inputYear)->second;

			for (int iIdx = 0; iIdx < localWeather.getPosition(); iIdx++)
			{
				Weather *objData;
				objData = localWeather.at(iIdx);
				myObj.push_back(objData);
			}
		}
	}

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Total Solar Radiation of " << sYear <<endl;
    cout << "---------------------------------------------" << endl;

			for (int iMonth = 1; iMonth <=12; iMonth++)
			{
				//Constructor of TotalWRT class is initialized with 0,0,0 and is added with the input value every time.
				TotalW objTotalDetail(0, 0, 0);

				for (int iIdx = 0; iIdx < myObj.getPosition(); iIdx++)
				{
					Weather *objData;
					objData = myObj.at(iIdx);
					Date objInnerDate = objData->GetDate();

					//Checking user input is valid for year
					if (to_string(objInnerDate.GetYear()) == sYear)
					{
						if (to_string(objInnerDate.GetMonth()) == to_string(iMonth))
						{
							TotalW TotalWRTChild(objData->GetWindspeed(), objData->GetSolarRadiation(), objData->GetAirTemp());

							objTotalDetail + TotalWRTChild;
						}
					}
				}

                //Check if the output of the calculation is more than zero
				//Date class getFullMonth function is used to display the user input for monthName
				if (objTotalDetail.getTotalRaditation() > 0)
				{

					cout << fixed << showpoint << setprecision(1) << setw(12)<< objDate.getFullMonth(iMonth) + "  : "
					<< (objTotalDetail.getTotalRaditation()/6)/1000 << " kWh/m^2"<< endl;

				}

	else
	{
		cout << fixed << showpoint << setprecision(1)<<setw(12)<< objDate.getFullMonth(iMonth)+ " :" << setw(12) <<"No Data" << endl;
	}
	}
	    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
/// --- Option 4 --- (Average wind speed, air temperature and total radiation in kWh/m2)
/// Method to perform calculation, validate user input for year and output to file "WindTempSolar.csv"
//////////////////////////////////////////////////////////////////////////////////////////////////////
void Menu::option4(){

	bool isDataFound = true;
	int iTotalMonthCount = 0, iYear = 0;
	string sYear;
	Date objDate;
	float fAvgWind = 0, fAvgTemp = 0, fTotalSR = 0;
	list<string> sFile;

	cout << "Please enter the year" << endl;
	cin >> sYear;

	//Outer loop to go through all input data and insert to map
	iYear = atoi(sYear.c_str());
	sFile.push_back(to_string(iYear - 1));
	sFile.push_back(to_string(iYear));
	sFile.push_back(to_string(iYear + 1));

	Vector<Weather*> myObj;

	for (std::list<string>::iterator it = sFile.begin(); it != sFile.end(); ++it)
	{
		string inputYear = *it;
		map<string, Vector<Weather*>>::iterator iter = myMap.find(*it);

		if (iter != myMap.end())
		{
			Vector<Weather*> localWeather = myMap.find(inputYear)->second;

			for (int iIdx = 0; iIdx < localWeather.getPosition(); iIdx++)
			{
				Weather *objData;
				objData = localWeather.at(iIdx);
				myObj.push_back(objData);
			}
		}
	}

	//output file to WindTempSolar.csv
	ofstream outFile;
	outFile.open("WindTempSolar.csv");
	outFile << sYear << "\n";
    outFile << "Month, Average Wind Speed, Average Temperature, Total Solar Radiation \n";
	outFile << setprecision(1) << fixed;



			for (int iMonth = 0; iMonth < 13; iMonth++)
			{
				TotalW objTotalDetail(0, 0, 0);
				iTotalMonthCount = 0;

				for (int iIdx = 0; iIdx < myObj.getPosition(); iIdx++)
				{
					Weather *objData;
					objData = myObj.at(iIdx);
					Date objInnerDate = objData->GetDate();

					if (to_string(objInnerDate.GetYear()) == sYear)
					{
						if (to_string(objInnerDate.GetMonth()) == to_string(iMonth))
						{
							TotalW TotalWRTChild(objData->GetWindspeed(), objData->GetSolarRadiation(), objData->GetAirTemp());
							objTotalDetail + TotalWRTChild;
							iTotalMonthCount += 1;
						}
					}
				}

				if (objTotalDetail.getTotalSpeed() > 0)
				{
					isDataFound = false;
					fAvgWind = objTotalDetail.getTotalSpeed()/ (float)iTotalMonthCount;
					fAvgTemp = objTotalDetail.getTotalTemperature() / (float)iTotalMonthCount;
					//get the total Solar radiation with 1/6*1000 to convert in to KWh/m2
					outFile << objDate.getFullMonth(iMonth) + ", " << fAvgWind << ", " << fAvgTemp << ", " << (objTotalDetail.getTotalRaditation()/6)/1000 << "\n";
				}
			}

	outFile.close();

        //output success
        cout << "---------------------------------------------------------------" <<endl;
        cout << "File is created successfully, please refer to WindTempSolar.csv" << endl;
        cout << "---------------------------------------------------------------\n" <<endl;

	if (isDataFound)
	{
		cout << "No Data Found" << endl;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/// --- Option 5 --- (Highest solar radiation for the given date)
/// Method to perform calculation and conversion, output result and validate user input for date
/////////////////////////////////////////////////////////////////////////////////////////////////
void Menu::option5()
{
	list<string> sFile;
	list<string> sTime;
	string inputDate, sTimevalue;
	int iYear, iSetCount = 0;
	string sDay, sMonth, sYear;
	float isResult = 0;
	char delimit;
	string result;

	cout << "Please enter the date in the format of dd/m/yyyy" << endl;
	cin >> inputDate;

	delimit = '/';
	//parsing the day month and year of the user input using the delimiter,
	for (int i = 0; i < inputDate.size(); i++)
	{
		if (inputDate[i] == delimit)
		{
			if (iSetCount == 0)
			{
				sDay = result;
			}
			else if (iSetCount == 1)
			{
				sMonth = result;
			}

			result = "";
			iSetCount++;
		}
		else
		{
			result += inputDate[i];
		}
	}

	sYear = result;
	//To get the data from multiple files and insert to map
	//where the data is present in previous or next file for the given year.
	iYear = atoi(sYear.c_str());
	sFile.push_back(to_string(iYear - 1));
	sFile.push_back(to_string(iYear));
	sFile.push_back(to_string(iYear + 1));

	Vector<Weather*> myObj;

	for (std::list<string>::iterator it = sFile.begin(); it != sFile.end(); ++it)
	{
		string inputYear = *it;
		map<string, Vector<Weather*>>::iterator iter = myMap.find(*it);

		if (iter != myMap.end())
		{
			Vector<Weather*> localWeather = myMap.find(inputYear)->second;

			for (int iIdx = 0; iIdx < localWeather.getPosition(); iIdx++)
			{
				Weather *objData;
				objData = localWeather.at(iIdx);
				myObj.push_back(objData);
			}
		}
	}

	//looping through the vector to get the highest solar radiation for the date
			for (int iIdx = 0; iIdx < myObj.getPosition(); iIdx++)
			{
				Weather *objData;
				objData = myObj.at(iIdx);
				Date objInnerDate = objData->GetDate();
				Time objInnerTime = objData->GetTime();

				if (to_string(objInnerDate.GetYear()) == sYear)
				{
					if (to_string(objInnerDate.GetMonth()) == sMonth)
					{
						if (to_string(objInnerDate.GetDay()) == sDay)
						{
							if (isResult == 0)
							{
								isResult = objData->GetSolarRadiation();
							}
							else
							{
								if (isResult < objData->GetSolarRadiation())
								{
									isResult = objData->GetSolarRadiation();
									sTimevalue = to_string(objInnerTime.GetHour()) + ":" + to_string(objInnerTime.GetMinute());
									sTime.clear();
									sTime.push_back(sTimevalue);
								}
							}
						}
					}
				}
			}

    //printing the highest solar radiation for the date and the time of the occurance.
	if (isResult > 0)
	{
	    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "High solar radiation for the day :" << isResult <<" W/m2"<< endl;
		cout << setw (2) << setfill ('0') << "Time : " << endl;


		for (list<string>::iterator thisTime = sTime.begin(); thisTime != sTime.end(); ++thisTime)
		{
			if (*thisTime != "")
			{
				cout << *thisTime << endl;
			}
		}
	}
	else
	{
		cout << "No Data found"<<endl;
	}
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}
/////////////////////////
/// --- Option 6 ---
/// To exit the program
////////////////////////
void Menu::option6()
{
    objBTree.clearTree();
    exit(0);
}
