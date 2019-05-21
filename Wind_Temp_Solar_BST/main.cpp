#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <map>

#include "Date.h"
#include "Time.h"
#include "Weather.h"
#include "Vector.h"
#include "Menu.h"
#include "TotalW.h"
#include "BST.h"

using namespace std;

int main()
{

    string filename = "data/met_index.txt";
    Menu test(filename);

    return 0;
}
