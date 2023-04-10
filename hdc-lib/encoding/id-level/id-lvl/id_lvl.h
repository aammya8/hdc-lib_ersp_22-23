#ifndef id_lvl_h
#define id_lvl_h

//#include "Arduino.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>

using namespace std;

#define DIMENSION 10000   // Size of hypervector
#define NUM_LEVELS 100
#define RANDOMNESS 0


// https://docs.arduino.cc/learn/contributions/arduino-creating-library-guide

class ID_Level_Encoder {

  public:

    ID_Level_Encoder(int n);
    void random_hv();
    void level_hv(); // generate level hypervectors
    void bind(double* value);
    void multiset();
    void hard_quantize();
    void ID_Level_Forward(double* x);
    double sample_hv[617];

  private:
    double id[617][DIMENSION];
    double level[617][DIMENSION];
    int num_vectors;
    double hv[617][DIMENSION];

};




#endif