#ifndef id_lvl_h
#define id_lvl_h

#include "Arduino.h"

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

    ID_Level_Encoder(int);
    double[][] random_hv();
    double[][] level_hv(); // generate level hypervectors
    double[][] bind(double [] weight, double [] value);
    double[] multiset(double [] sample);
    double[] hard_quantize(double [] sample);
    double[] ID_Level_Forward(double[] id, double [] x);

  private:
    double id[];
    double value[];
    int num_vectors;
    double sample_hv[];

};




#endif