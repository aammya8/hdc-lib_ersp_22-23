/*
ID-Level Encoding
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define DIMENSION 10000   // Size of hypervector
#define NUM_LEVELS 100


class ID_Level_Encoder {

  public:
    float id[];
    float value[];
    int num_vectors;

    /* 
     * Return array of random binary hypervectors (1 and -1)
     * Each row in array corresponds to different random hypervector
     * e.g. row 0 corresponds to hv0, row 1 to hv1, etc. 
    */
    float[][] random_hv() {

      // 2-D array to store all num_vectors random binary hypervectors
      float random_hv_set[num_vectors][DIMENSION];

      // Generate random hypervectors
      // https://www.includehelp.com/c-programs/generate-random-numbers-within-a-range.aspx
      int lower = 0;
      int upper = 1;
      srand(time(0));
      for (int hv = 0; hv < num_vectors; hv++) {
        for (int element = 0; element < DIMENSION; element++) {
          random_hv_set[hv][element] = (float) (rand() % (upper - lower + 1)) + lower;
          printf("%f ", random_hv_set[hv][element]);
        }
        printf("\n");
      }

      return random_hv_set;
    }


    /*
     * 
     */
    float[] level_hv() {

    }


    /* Constructor */
    ID_Level_Encoder(int n) {
      num_vectors = n;
      id = random_hv();
      value = level_hv();
    }


  private:

}




float[] bind(float [] weight, float [] value) {
  float hv[];
  for (int i = 0; i < weight.size(); i++){
    if (weight[i]*value[i] > 0)
      hv[i] = 1;
    else
      hv[i] = -1;
  }
  return hv;
}

float[] multiset(float [] sample) {
  float hv[];
  for (int i = 0; i < sample[0].size(); i++){
    float total;
    for (int j = 0; j < sample[0].size(); i++)
      total += sample[i][j];
    hv[i] = total;
  }
  return hv;
}

float[] hard_quantize(float [] sample){
  float hv[];
  for (int i = 0; i < sample.size(); i++){
    if (sample[i] > 0)
      hv[i] = 1;
    else
      hv[i] = -1;
  }
  return hv;
}


// void id_level_encoder(int num_classes, int size) {}


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
