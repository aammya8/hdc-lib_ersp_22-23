/*
 * C++ version code
 */
// imports
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <random>
#include <vector>
// statistic c library: https://github.com/christianbender/statistic
// #include <statistic.h>

using namespace std;
// number of hypervector dimensions
const unsigned int DIMENSIONS = 4;

// number of features in dataset
const unsigned NUM_FEATURES = 5;

/*
 * Torch functions:
 * hard_quantize
 * Sinusoid
 * linear 
 * normalize
 */

// //Applies binary quantization to all elements of the input tensor.
void hard_quantize (float x[5]){
  for(int i = 0; i < sizeof(x); i++) {
    if (x[i] <= 0) {
        x[i] = -1;
    } else {
      x[i] = 1;
    }
  }
}


/*
 * multiply by the weight and add the bias
 */


void normalize(float input[DIMENSIONS][5])
{
  // work on each row in the 2d vector
  for(int i = 0; i < DIMENSIONS; ++i){
    float magnitude = 0;
    for(int j=0; j < 5; ++j){
      magnitude +=input[i][j]*input[i][j];
    }
    magnitude = sqrt(magnitude);
    for (int j=0; j < 5; ++j) {
      input[i][j] = input[i][j]/magnitude;
    }
  }
}

/*
 * performs normalization of inputs by rows (dimension = 1)
 */


void Projection(int in_features, int out_features, float tensor[5], float result[DIMENSIONS]){
  // instantiating matrix with rows and columns
  float weight[out_features][5];
  
  // filling matrix with rnd normal distribution
  srand(time(NULL)); // Set a random seed value
  default_random_engine generator(rand()); // Use the seed value for the random engine
  normal_distribution<float> distribution(0,1);

  for (int row = 0; row < out_features; ++row){
    for(int col = 0; col < in_features; ++col){
      weight[row][col] = distribution(generator);
      //Serial.println(weight[row][col]);
    }
  }

  // normalize weight
  normalize(weight);

  // MATRIX MULTIPLICATION SECTION
  for (int r = 0; r < out_features; ++r){
    for (int c = 0; c < in_features; ++c){
       result[r] += weight[r][c]*tensor[c];
    }
    //Serial.println(result[r]);
  }
}

// /*
//  * Projection: does matrix multiplication with the input tensor/data (vector<float>)
//  * and a randomly generated matrix to produce a random hypervector
//  * @param in_features = dimension of the input vector
//  * @param out_features (1000) = output dimension of the hypervector
//  * @return = random generated hypervector
//  */


void setup() {
  Serial.begin(9600);
  float x[5] = {-0.6624, -0.3334, 0.3666, 0.4292, -0.2084};
  float result[DIMENSIONS] = {0};
  
  Projection(5, DIMENSIONS, x, result);
  hard_quantize(result);
  //Serial.println(result[0]);
  for (int i = 0; i < 5; ++i) {
    Serial.print(i);
    Serial.print(" ");
    Serial.println(result[i]);
  }
  
}

void loop() {
  // do nothing
}