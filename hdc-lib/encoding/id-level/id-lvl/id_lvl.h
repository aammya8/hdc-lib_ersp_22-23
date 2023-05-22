#ifndef id_lvl_h
#define id_lvl_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

#define DIMENSION 10  // Size of hypervector
#define NUM_LEVELS 10
#define RANDOMNESS 0
#define num_vertcors 10


// https://docs.arduino.cc/learn/contributions/arduino-creating-library-guide

class ID_Level_Encoder {

  public:

    ID_Level_Encoder(int n);
    //~ID_Level_Encoder(int n);
    void random_hv();
    void level_hv(); // generate level hypervectors
    void bind(float* value);
    void multiset();
    void hard_quantize();
    void ID_Level_Forward(float* x);
    int sample_hv[DIMENSION];

  private:
    char id[num_vertcors][DIMENSION/8+1];
    char level[num_vertcors][DIMENSION/8+1];
    int num_vectors;
    char hv[num_vertcors][DIMENSION/8+1];

};




#endif