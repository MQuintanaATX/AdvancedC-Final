/* *****************************
 * Name: Michael Quintana
 * Date: 3/24/3019
 * Assignment: Final Project
 * File - functions.cpp
 * Purpose - Contains the interface for misc. functions
******************************/

#include "functions.h"

int inputInteger(int min, int max, string msg){
    //Input will hold the user input, and fractional will be used later
    //to hold any value to the right of input's decimal.
    double input, fractional;
    while (true) {
        cout << msg;
        cin >> input;
        //modf will take the input, and assign anything to the right of the decimal to fractional!
        fractional = modf(input, &fractional);
        //Catches for any non-numerical input
        if (cin.fail()){
            cout << "You have entered an invalid value" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
            //Checks to see if there is any values in the decimal digits of input
        else if (fractional != 0){
            cout << "You have entered a non-integer  value" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
            //Checks for bounds
        else if (input < min or input > max){
            cout << "You have entered an invalid value" << endl;
        }
            //returns input
        else
            return input;
    }
}