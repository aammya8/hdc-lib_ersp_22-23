#ifndef id_lvl_h
#define id_lvl_h

//#include "Arduino.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <random>

using namespace std;

#define DIMENSION 100   // Size of hypervector
#define NUM_LEVELS 10
#define RANDOMNESS 0


// https://docs.arduino.cc/learn/contributions/arduino-creating-library-guide

class ID_Level_Encoder {

  public:

    ID_Level_Encoder(int n);
    void random_hv();
    void level_hv(); // generate level hypervectors
    void bind(float value[]);
    void multiset();
    void hard_quantize();
    void ID_Level_Forward(float x[]);
    float sample_hv[617];

  private:
    float id[617][DIMENSION];
    float level[617][DIMENSION];
    float threshold_v[617];
    int num_vectors;
    float hv[617][DIMENSION];

};




#endif