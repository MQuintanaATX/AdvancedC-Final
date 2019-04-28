/* *****************************
 * Name: Michael Quintana
 * Date: 3/24/3019
 * Assignment: Final Project
 * File - network.cpp
 * Purpose - Implementation for the Network class
******************************/

#include "network.h"
/*
 * Constructor
 */
NNetwork::NNetwork() {
    loadCfgParams();
    buildInputLayer();
}

NNetwork::~NNetwork() {
}

//Loads the data file
void NNetwork::loadCfgParams() {
    //Filestream object; used to load files from the config file
    fstream config;
    //Holds characters as the line is read, holds the read line
    string container = "", fileline;
    //Counter; used for a switch statement later
    int counter = 0;
    //Opens the file; hardcoded due to being a toy problem
    config.open("Network.cfg");
    //Loads the file into the variables
    while (!config.eof()){
        getline(config, fileline);
        //reads each line of the file
        for (int i = 0; i < fileline.size(); i++){
            //Checks for the delimiter character, |. If not, adds it to the container variable
            if (fileline[i] != '|') {
                container += fileline[i];
                continue;
            }
            //Checks for the delimiter character, |. If it is, sets the variable to it
            if (fileline[i] == '|'){
                //Sets the variable for each successive iteration of While
                switch (counter){
                    case 0:
                        on = stof(container);
                        break;
                    case 1:
                        off = stof(container);
                        break;
                    case 2:
                        inUnits = stoi(container);
                        break;
                    case 3:
                        hidUnits = stoi(container);
                        break;
                    case 4:
                        outUnits = stoi(container);
                        break;
                    case 5:
                        maxEpoch  = stoi(container);
                        break;
                    case 6:
                        learnRate = stof(container);
                        break;
                    case 7:
                        ee = stof(container);
                        break;

                }
                break;
            }
        }
        //Increments counter for next loop
        counter++;
        //clears container
        container = "";
    }
}
//Responsible for generating random weights for the first pass
float NNetwork::randomWeight () {
          //|Casts random into float   | Divides that value, also by float
    return static_cast <float>(rand()) / static_cast <float> (RAND_MAX);
};

/*
 * Builds the network layers
 */

//Inner layer
void NNetwork::buildInputLayer() {
    nNetwork->inputLayer.x = new float [inUnits+1];
    nNetwork->inputLayer.w = new float* [inUnits];
    for (int i = 0; i < inUnits; i++) {
        nNetwork->inputLayer.w[i] = new  float [hidUnits];
    }
    int innerLoop, outerLoop;
    for (outerLoop = 0 ; outerLoop < inUnits; outerLoop++) {
        for (innerLoop = 0; innerLoop < hidUnits - 1; innerLoop++) {
            nNetwork->inputLayer.w[outerLoop][innerLoop] = randomWeight();
        }
    }
}

void NNetwork::buildIOData() {
    cout << "stuff";
}

/*
 * Debug Functions
 */
//******************Professor Debug Statements
void NNetwork::displayInputLayerWeights(){
    int innerLoop = 0, outerLoop = 0;
    cout << "Inner Layer Weights\n" << endl;
    for (outerLoop; outerLoop < inUnits + 1; outerLoop++){
        for (innerLoop; innerLoop < hidUnits + 1; innerLoop++)
            cout << "\tNode " << outerLoop << "\tWeight #: " << innerLoop;
            cout << "\tWeight: " << nNetwork->inputLayer.w[outerLoop][innerLoop] << endl;
    }
};


// ***************** Student Debugs
void NNetwork::printConfig() {
    cout << "Configuration: " << endl;
    cout << "ON: " << on << endl;
    cout << "OFF: " << off << endl;
    cout << "inUnits: " << inUnits << endl;
    cout << "hidUnits: " << hidUnits << endl;
    cout << "outUnits: " << outUnits << endl;
    cout << "maxEpoch: " << maxEpoch << endl;
    cout << "learnRate: " << learnRate << endl;
    cout << "ee: " << ee << endl;

}