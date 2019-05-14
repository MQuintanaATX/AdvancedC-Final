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
    nNetwork = new nNet;
    ioPairs = 0;
    loadCfgParams();
    buildInputLayer();
    buildHiddenLayer();
    buildOutputLayer();
    buildIOData();
    loadIOFile();
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
    float value;
    value = static_cast <float>(rand()) / static_cast <float> (RAND_MAX);
    if (rand() % 2 == 0) {
        value *= -1;
    }
    //|Casts random into float   | Divides that value, also by float
    return value;
};

/*
 * Builds the network layers
 */

//Inner layer
void NNetwork::buildInputLayer() {
    //Initializes the arrays
    float value;
    nNetwork->inputLayer.x = new float [inUnits + 1];
    nNetwork->inputLayer.w = new float* [inUnits + 1];
    //Creates the second dimension of the weights array
    for (int i = 0; i < inUnits + 1; i++) {
        nNetwork->inputLayer.w[i] = new  float [hidUnits];
    }
    int innerLoop, outerLoop;
    for (outerLoop = 0 ; outerLoop < inUnits + 1; outerLoop++) {
        if (outerLoop == inUnits) { //Loads the bias node with the max value
            nNetwork->inputLayer.x[outerLoop] = 1;
        } else {
            //Using .314 as a sentinel for activations
            nNetwork->inputLayer.x[outerLoop] = .314;
        }
        for (innerLoop = 0; innerLoop < hidUnits + 1; innerLoop++) {
            nNetwork->inputLayer.w[outerLoop][innerLoop] = randomWeight();
        }
    }
}

//Hidden layer
void NNetwork::buildHiddenLayer(){
    float value;
    //Initializes the arrays
    nNetwork->hiddenLayer.x = new float [hidUnits + 1];
    nNetwork->hiddenLayer.w = new float* [hidUnits + 1];
    nNetwork->hiddenLayer.e = new float [hidUnits + 1];
    //Creates the second dimension of the weights array
    for (int i = 0; i < hidUnits + 1; i++) {
        nNetwork->hiddenLayer.w[i] = new  float [outUnits];
    }
    int innerLoop, outerLoop;
    for (outerLoop = 0 ; outerLoop < hidUnits + 1; outerLoop++) {
        if (outerLoop == hidUnits) { //Loads the bias node with the max value
            nNetwork->hiddenLayer.x[outerLoop] = 1;
        } else {
            //Using .796 as a sentinel for activations
            nNetwork->hiddenLayer.x[outerLoop] = .796;
        }
        for (innerLoop = 0; innerLoop < outUnits; innerLoop++) {
            nNetwork->hiddenLayer.w[outerLoop][innerLoop] = randomWeight();
        }
    }
}

//Output layer
void NNetwork::buildOutputLayer() {
    //Initializes the arrays
    nNetwork->outputLayer.x = new float [outUnits];
    nNetwork->outputLayer.e = new float [outUnits];
    for (int loop = 0 ; loop < hidUnits + 1; loop++) {
        nNetwork->outputLayer.x[loop] = .555;
    }
}


void NNetwork::buildIOData() {
    /* Variable Initialization*/
    fstream inputFile;
    string fileName;
    string lineContainer;
    //Counts how many data entries are there in a line.
    int inputCounter = 0, outputCounter = 0;
    //Counts how many ints are in the first line
    int firstLine;
    //Gets user input for the file
    //  Note: Aware this is bad practice in the real world, but
    //  Neural network use, coding it within the class.
    cout << "\nWhich file would you like to use for training?";
    cout << "\n\t1) and.dat \n\t2) or.dat\n\t3) xor.dat\n" << "Enter your choice: ";
    //Note: No error checking; would in a more robust application, per the above note
    cin >> choice;
    switch (choice) {
        case 1:
            fileName = "and.dat";
            break;
        case 2:
            fileName = "or.dat";
            break;
        case 3:
            fileName = "xor.dat";
            break;
    }
    inputFile.open(fileName);
    getline(inputFile, lineContainer);
    ioPairs++;
    firstLine = lineContainer.size();
    //Counts the number of Input lines
    while(!inputFile.eof()){
        getline(inputFile, lineContainer);
        if (lineContainer.size() == firstLine){
            ioPairs++;
        }
    }
    inputFile.close();
    /*Array Initialization*/
    inputData = new float* [ioPairs];
    for (int i = 0; i < ioPairs; i++) {
        inputData[i] = new  float [inUnits];
    }
    outputData = new float *[ioPairs];
    for (int i = 0; i < ioPairs; i++) {
        outputData[i] = new  float [outUnits];
    }
    cout << endl;
}

bool NNetwork::loadIOFile() {
    /* Variable Initialization*/
    fstream inputFile;
    string fileName;
    string lineContainer;
    //Coordinates the second dimension in the array
    int positionFlag = 0;
    //Sets the file name
    switch (choice) {
        case 1:
            fileName = "and.dat";
            break;
        case 2:
            fileName = "or.dat";
            break;
        case 3:
            fileName = "xor.dat";
            break;
    }
    inputFile.open(fileName);
    //Checks each char in the file lines; if numeric, adds it to the input array
    for (int i = 0; i < ioPairs; i++){
        getline(inputFile, lineContainer);
        for (int o = 0; o < lineContainer.size(); o++){
            if (isdigit(lineContainer[o])) {
                inputData[i][positionFlag] = lineContainer[o] - 48;
                positionFlag++;
            }
        }
        positionFlag = 0;
    }
    positionFlag = 0;
    for (int i = 0; i < ioPairs; i++) {
        getline(inputFile, lineContainer);
        for (int o = 0; o < lineContainer.size(); o++){
            if (isdigit(lineContainer[o])) {
                outputData[i][positionFlag] = lineContainer[o] - 48;
                positionFlag++;
            }
        }
        positionFlag = 0;
    }
    inputFile.close();
    return true;
}

/*
 * Training Functions
 */
void NNetwork::train() {
    for (int j = 0; j < maxEpoch; j++) {
        for (int i = 0; i < ioPairs; i++) {
            assignActivations(i);
            propigateActivations();
            computeErrors(i);
            adjustWeights();
        }
    }
}

void NNetwork::test(){
    cout << "Input Pairs" << endl  <<"\t";
    for (int i = 0; i < ioPairs; i++) {
        for (int j = 0; j < inUnits; j++) {
            cout << inputData[i][j] << "  ";
        }
        cout << endl << "\t";
    }
    cout << "\nOutput from Network" << endl;
    for (int i = 0; i < ioPairs; i++) {
        assignActivations(i);
        propigateActivations();
        for (int j = 0; j < outUnits; j++){
            cout << "\t" << nNetwork->outputLayer.x[j] << "  ";
        }
        cout << endl;
    }
}

void NNetwork::assignActivations(int i) {
    for (int counter = 0; counter < inUnits; counter++){
        nNetwork->inputLayer.x[counter] = inputData[i][counter];
    }
}

void NNetwork::propigateActivations() {
    /*Variable Declaration */
    float sum = 0;
    //Outer loop handles each of the non-bias hidden nodes
    for (int i = 0; i < hidUnits; i++) {
        //Determines the product of each of the input nodes
        //  the +1 accounts for the bias node
        for (int j = 0; j < inUnits +1; j++) {
            sum += nNetwork->inputLayer.x[j] * nNetwork->inputLayer.w[j][i];
        }
        nNetwork->hiddenLayer.x[i] = 1.0 / (1.0 + pow(ee, -sum));
        //Resets newActivation
        sum = 0;
    }

    //Second loop structure pushes it to the output node
    for (int i = 0; i < outUnits; i++){
        //Determines the product of each of the input nodes
        //  the +1 accounts for the bias node
        for (int j = 0; j < hidUnits + 1; j++) {
            sum = sum + nNetwork->hiddenLayer.x[j] * nNetwork->hiddenLayer.w[i][j];
        }
        nNetwork->outputLayer.x[i] = 1.0 / (1.0 + pow(ee, -sum));
        //Resets newActivation
        sum = 0;
    }
}

void NNetwork::computeErrors(int current) {
    float sum = 0;
    int i, j;
    //Calculate output layer errors
    for (j = 0; j < outUnits; j++) {
        nNetwork->outputLayer.e[j] = nNetwork->outputLayer.x[j] *
                (1.0 - nNetwork->outputLayer.x[j]) * (outputData[current][j] - nNetwork->outputLayer.x[j]);
    }
    //Compute Hidden Layer Errors
    //hidUnits is set to 2 in the config; +1 accounts for the bias
    for (j = 0; j < hidUnits + 1; j++) {
        //Not skipping bias node
        for (i = 0; i < outUnits; i++) {
            sum = sum + nNetwork->outputLayer.e[i] * nNetwork->hiddenLayer.w[j][i];
        }
        nNetwork->hiddenLayer.e[j] = (nNetwork->hiddenLayer.x[j] * (1 - nNetwork->hiddenLayer.x[j])) * sum;
    }
}

void NNetwork::adjustWeights() {
    int i, j;
    for(i = 0; i < hidUnits + 1; i++ ){
        for (j = 0; j < outUnits; j++){
            nNetwork->hiddenLayer.w[i][j] =
                    nNetwork->hiddenLayer.w[i][j] +
                    (learnRate * nNetwork->outputLayer.e[j] * nNetwork->hiddenLayer.x[i]);
        }
    }
    for (i = 0; i < inUnits + 1; i++) {
        for(j = 0; j < hidUnits; j++) {
            nNetwork->inputLayer.w[i][j] =
                    nNetwork->inputLayer.w[i][j] +
                    (learnRate * nNetwork->hiddenLayer.e[j] * nNetwork->inputLayer.x[i]);
        }
    }
}

/*
 * Administrative Functions
 */
void NNetwork::saveweights() {
    /*
     * This function assumes everything is configured/named correctly. In a production
     * environment, this would contain more robust error handling.
     */
    int innerLoop, outerLoop;
    ofstream weightFile;
    weightFile.open("weights.cfg");
    //Saves the inner layer's weights
    for (outerLoop = 0; outerLoop < inUnits + 1; outerLoop++) {
        for (innerLoop = 0; innerLoop < hidUnits + 1; innerLoop++) {
            weightFile << nNetwork->inputLayer.w[outerLoop][innerLoop] << endl;
        }
    }
    //Saves the outer layer's weights
    for (outerLoop = 0 ; outerLoop < hidUnits + 1; outerLoop++) {
        for (innerLoop = 0; innerLoop < outUnits; innerLoop++) {
            weightFile << nNetwork->hiddenLayer.w[outerLoop][innerLoop] << endl;
        }
    }
    weightFile.close();
}

void NNetwork::loadweights() {
    /*
     * This function assumes everything is configured/named correctly. In a production
     * environment, this would contain more robust error handling.
     */
    int innerLoop, outerLoop;
    //Holds a string to be converted to a float; used in the get lines
    string container;
    float weight;
    //File object for weights; in a production build, would have further
    //  validation for file existence
    fstream weightFile;
    weightFile.open("weights.cfg");
    //Loads the inner layer's weights
    for (outerLoop = 0; outerLoop < inUnits + 1; outerLoop++) {
        for (innerLoop = 0; innerLoop < hidUnits + 1; innerLoop++) {
             getline(weightFile, container);
            weight = stof(container);
            nNetwork->inputLayer.w[outerLoop][innerLoop] = weight;
        }
    }
    //Loads the outer layer's weights
    for (outerLoop = 0 ; outerLoop < hidUnits + 1; outerLoop++) {
        for (innerLoop = 0; innerLoop < outUnits; innerLoop++) {
            getline(weightFile, container);
            weight = stof(container);
            nNetwork->hiddenLayer.w[outerLoop][innerLoop] = weight;
        }
    }
    weightFile.close();
}
/*
 * Debug Functions
 */
//******************Professor Debug Statements
void NNetwork::displayInputLayerWeights() {
    int innerLoop, outerLoop;
    cout << endl << "Inner Layer Weights" << endl;
    for (outerLoop = 0; outerLoop < inUnits + 1; outerLoop++) {
        for (innerLoop = 0; innerLoop < hidUnits + 1; innerLoop++) {
            cout << "\t Node " << outerLoop << " Weight# " << innerLoop << " Weight ";
            cout  << nNetwork->inputLayer.w[outerLoop][innerLoop] << endl;
        }
    }
}

void NNetwork::displayHiddenLayerWeights() {
    int innerLoop, outerLoop;
    cout << endl << "Hidden Layer Weights" << endl;
    for (outerLoop = 0 ; outerLoop < hidUnits + 1; outerLoop++) {
        for (innerLoop = 0; innerLoop < outUnits; innerLoop++) {
            cout << "\t Node " << outerLoop << " Weight# " << innerLoop << " Weight ";
            cout  << nNetwork->hiddenLayer.w[outerLoop][innerLoop] << endl;
        }
    }
}


void NNetwork::displayInputActivations() {
    int outerLoop;
    cout << endl << "Inner Layer Activations" << endl;
    for (outerLoop = 0; outerLoop < inUnits + 1; outerLoop++) {
        cout << "\t Node " << outerLoop << " Activation ";
        cout  << nNetwork->inputLayer.x[outerLoop] << endl;
    }
}
void NNetwork::displayHiddenActivations(){
    int outerLoop;
    cout << endl << "Hidden Layer Activations" << endl;
    for (outerLoop = 0; outerLoop < hidUnits + 1; outerLoop++) {
        cout << "\t Node " << outerLoop << " Activation ";
        cout  << nNetwork->hiddenLayer.x[outerLoop] << endl;
    }
}

void NNetwork::displayOutputActivations(){
    int loop;
    cout << endl << "Output Layer Activations" << endl;
    for (loop = 0; loop < outUnits; loop++) {
        cout << "\t Node " << loop << " Activation ";
        cout  << nNetwork->outputLayer.x[loop] << endl;
    }
}


void NNetwork::displayTrainingInput(){
    int innerLoop = 0, outerLoop = 0;
    cout << endl << "Training Input Data" << endl;
    for (outerLoop = 0; outerLoop < ioPairs; outerLoop++) {
        cout << "\tPair " << outerLoop << "\t";
        for (innerLoop = 0; innerLoop < inUnits; innerLoop++) {
            cout << inputData[outerLoop][innerLoop] << " ";
        }
        cout << endl;
    }
}

void NNetwork::displayTrainingOutput() {
    int innerLoop = 0, outerLoop = 0;
    cout << endl << "Training Output Data" << endl;
    for (outerLoop = 0; outerLoop < ioPairs; outerLoop++) {
        cout << "\tPair " << outerLoop << "\t";
        for (innerLoop = 0; innerLoop < outUnits; innerLoop++) {
            cout << outputData[outerLoop][innerLoop] << " ";
        }
        cout << endl;
    }
}


/* **************** Student Debugs
void NNetwork::printConfig() {
    cout << "Configuration " << endl;
    cout << "\tON: " << on << endl;
    cout << "\tOFF: " << off << endl;
    cout << "\tinUnits: " << inUnits << endl;
    cout << "\thidUnits: " << hidUnits << endl;
    cout << "\toutUnits: " << outUnits << endl;
    cout << "\tmaxEpoch: " << maxEpoch << endl;
    cout << "\tlearnRate: " << learnRate << endl;
    cout << "\tee: " << ee << endl;

}

void NNetwork::displayHiddenErrors(){
    int outerLoop;
    cout << endl << "Hidden Layer Errors" << endl;
    for (outerLoop = 0; outerLoop < hidUnits + 1; outerLoop++) {
        cout << "\t Node " << outerLoop << " Error ";
        cout  << nNetwork->hiddenLayer.e[outerLoop] << endl;
    }
}

void NNetwork::displayOutputErrors(){
    int loop;
    cout << endl << "Output Layer Errors" << endl;
    for (loop = 0; loop < outUnits; loop++) {
        cout << "\t Node " << loop << " Error ";
        cout  << nNetwork->outputLayer.e[loop] << endl;
    }
}
*/