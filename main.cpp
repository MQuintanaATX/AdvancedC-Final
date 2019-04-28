/* *****************************
 * Name: Michael Quintana
 * Date: 3/24/3019
 * Assignment: Final Project
 * File - main.cpp
 * Purpose - Main drive file
******************************/



#include "main.h"
#include "functions.h"
#include "network.h"

int main() {
    cout << "Final Project: Neural Network" << endl;
    //Seeding the Rand function
    srand (time(NULL));
    NNetwork skynet;
    skynet.printConfig();
    skynet.displayInputLayerWeights();
    skynet.displayInputActivations();
    skynet.displayHiddenLayerWeights();
}
