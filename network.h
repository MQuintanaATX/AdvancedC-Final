/* This is a sample header file for a neural network. A few things
 * to note about this file...
 * *** It is only a simple proof-of-concept header file. It does not conform
 *     to all the specifications in your project assignment. It is ONLY meant
 *     a guide to help you think about how you will structure your network.
 *     Your final network will have more functionality than this one.
 * *** There are many ways to structure a neural network. You are free to
 *     structure yours any way you like so long as it follows good programming
 *     practice and is efficient and well structured.
 * *** I "cheat" and have all my parameters in #define. These should be in
 *     a configuration file except for iopairs which you have to find
 *     dynamically by testing your input file
 */

#ifndef NNETWORK_H
#define NNETWORK_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iomanip>

using namespace std;

/*
 * These are some of the things you will put in a configuration file.
 * DO NOT do it like this, put these values, and anything else you need
 * in a cfg file. The purpose of the cfg file is so that if you change
 * the structure of your network, you should not need to recompile.
 * Also, you should not have the number of io pairs specified anywhere,
 * you need to deduce that number from the data file itself.
 */
/* Commenting out due to config file containing these
#define ON 1.0
#define OFF 0.0
#define OFFSOFT 0.1
#define ONSOFT 0.9

#define I_UNITS 2
#define H_UNITS 2
#define O_UNITS 1
#define IOPAIRS 4

#define MAX_EPOCH 1000
#define LR .35
#define EE 2.718281828
*/
/* input layer consisting of activations x (neurons) and weights w
   to the hidden layer. these are created as pointers that will be allocated
 * as 1 and 2 dimensional arrays. */
struct inLayer {
    float *x; /*activation for each neuron in the input layer*/
    float **w; /*weights from input layer to hidden layer*/
};

/* hidden layer consisting of activations x (neurons) and weights w
   to the output layer and errors in the hidden neurons. these are created
 * as pointers that will be allocated as 1 and 2 dimensional arrays. */
struct hidLayer {
    float *x; /*activation for each neuron in the hidden layer*/
    float **w; /*weights from input layer to output layer*/
    float *e; /*errors in hidden layer*/
};

/* output layer consisting of activations x (neurons) and 
   errors in the output neurons. these are created as pointers that
 * will be allocated as 1 and 2 dimensional arrays. */
struct outLayer {
    float *x; /*activation for each neuron in the output layer*/
    float *e; /*errors in output layer*/
};

// the structure defining the whole neural network structure
struct nNet {
    inLayer inputLayer;
    hidLayer hiddenLayer;
    outLayer outputLayer;
};

class NNetwork {
public:
    NNetwork();
    ~NNetwork();

    /*
     * These are just debug routines that help me see what's in the
     * network and to make sure it's working right. They do not add
     * to the functionality of the network.
     */
    void displayInputLayerWeights();
    void displayHiddenLayerWeights();
    void displayInputActivations();
    void displayHiddenActivations();
    void displayOutputActivations();
    void displayTrainingInput();
    void displayTrainingOutput();

    //this calls all the private training methods
    void train();

    //this loads the validation set and tests the trained network
    void test();

    //this saves the weights when training is done
    void saveweights();

    /* this loads weights from a saved weights file so you can re-load
     a trained network and use it, instead of retraining.*/
    void loadweights();

    /*
     * Debug Functions
     * Used to ensure proper configuration. Student's functions
     */
    void printConfig();
    void displayHiddenErrors();
    void displayOutputErrors();

private:
    /* this file is for debug purposes. I save my MSE from compute errors so
       I can look at it and see how training is working. This will dramatically
       slow down your network so you should be able to turn this on and off
       as needed or find a smart way to make it aster.*/
    ofstream msefile;

    //basic data for the network. these are initialized in the loadCfgParams()
    int inUnits, hidUnits, outUnits, ioPairs, maxEpoch;
    float off, on;
    float offSoft, onSoft;
    float learnRate;
    float ee;

    /* holds the data set for training. these are initialized in buildIOData()
       and loaded in loadIOFile() */
    float **inputData, **outputData;

    // MQ Variable Declaration */
    //Flag to help parse which file is being used
    int choice;

    // a pointer to a neural network. this will be dynamically allocated
    nNet *nNetwork;


    // set-up methods to create and initialize the network and data
    float randomWeight();
    void loadCfgParams();
    void buildInputLayer();
    void buildHiddenLayer();
    void buildOutputLayer();
    void buildIOData();
    bool loadIOFile();

    /* training methods used in train(). assignActivatons and propigateActivations
       are also used in the test() method. depending on your implementation,
       compute errors may also be used in the test method, but do not use
       adjustWeights in the test method. */
    void assignActivations(int);
    void propigateActivations();
    void computeErrors(int);
    void adjustWeights();

};

#endif /* NNETWORK_H */


