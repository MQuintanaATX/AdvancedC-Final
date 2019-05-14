/* *****************************
 * Name: Michael Quintana
 * Date: 3/24/3019
 * Assignment: Final Project
 * File - main.cpp
 * Purpose - Main drive file
******************************/



#include "main.h"


int main() {
    cout << "Final Project: Neural Network" << endl;
    //Seeding the Rand function
    srand (time(NULL));
    NNetwork skynet;
    //Holds the choice for testing a new network, loading an existing network, or continuing the loop
    int menu = 0;
    while (menu != 5) {
        cout << "Choose an option: \n\t1) Load an Existing Network" <<
             "\n\t2) Dispay Weights & Activations \n\t3) Train and Save a New Network \n\t" <<
             "4) Test Network\n\t5) Quit\n";
        menu = inputInteger(1, 5, "Enter your choice: ");
        cout << endl;
        switch (menu) {
            case 1:
                cout << "Now loading weights..."<< endl;
                skynet.loadweights();
                cout << "Network Loaded" << endl << endl;
                break;
            case 2:
                skynet.displayInputActivations();
                skynet.displayInputLayerWeights();
                skynet.displayHiddenActivations();
                skynet.displayHiddenLayerWeights();
                skynet.displayOutputActivations();
                cout << endl;
                break;
            case 3:
                cout << "Now training new network..." << endl;
                skynet.train();
                cout << "Network trained; weights have been saved." << endl << endl;
                break;
            case 4:
                cout << "Testing loaded network..."<< endl;
                skynet.test();
                cout << "Testing completed." << endl << endl;
                break;
            case 5:
                cout << "Now exiting Neural Network" << endl;
                break;
        }
    }
}
