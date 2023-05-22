// imports
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <random>
#include <vector>
using namespace std;

// number of hypervector dimensions
const unsigned int DIMENSIONS = 300;

// number of features in dataset
const unsigned NUM_FEATURES = 10;

/*
 * hamming_distance_similarity: finds the bit difference between two hypervectors
 * @param hamming_distance - an integer variable to be filled with how many bits differ
 * @param hv1 - a hypervector to be compared
 * @param hv2 - a hypervector to be compared
 */
void hamming_distance_similarity(int & hamming_distance, float hv1[DIMENSIONS], float hv2[DIMENSIONS]){
  hamming_distance = 0;

  for (int i = 0; i < DIMENSIONS; i++) {
    if (hv1[i] != hv2[i]) {
      hamming_distance++;
    }
  }
}

/*
 * hard_quantize: applies binary quantization to all elements of the input tensor
 * @param x - a vector with positive and negative float values
 */
void hard_quantize (float x[DIMENSIONS]){
  for(int i = 0; i < DIMENSIONS; i++) {
    if (x[i] <= 0) {
        x[i] = -1;
    } else {
      x[i] = 1;
    }
  }
}

/*
 * normalize: performs normalization of inputs by rows (dimension = 1)
 * @param input - a 2D vector with random normal distribution values
 */
void normalize(float input[DIMENSIONS][10])
{
  // work on each row in the 2d vector
  for(int i = 0; i < DIMENSIONS; ++i){
    float magnitude = 0;
    for(int j=0; j < 10; ++j){
      magnitude +=input[i][j]*input[i][j];
    }
    magnitude = sqrt(magnitude);
    for (int j=0; j < 10; ++j) {
      input[i][j] = input[i][j]/magnitude;
    }
  }
}

/*
 * Projection: does matrix multiplication with the input tensor/data (vector<float>)
 * and a randomly generated matrix to produce a random hypervector
 * @param seed - a random seed value for the normal distribution generator
 * @param in_features - dimension of the input vector
 * @param out_features (1000) - output dimension of the hypervector
 */
void Projection(int seed, int in_features, int out_features, float tensor[10], float result[DIMENSIONS]){
  // instantiating matrix with rows and columns
  float weight[out_features][10];
  
  // filling matrix with rnd normal distribution
  default_random_engine generator(seed); // Use the seed value for the random engine
  normal_distribution<float> distribution(0,1);

  for (int row = 0; row < out_features; ++row){
    for(int col = 0; col < in_features; ++col){
      weight[row][col] = distribution(generator);
    }
  }

  // normalize weight
  normalize(weight);

  // MATRIX MULTIPLICATION SECTION
  for (int r = 0; r < out_features; ++r){
    for (int c = 0; c < in_features; ++c){
       result[r] += weight[r][c]*tensor[c];
    }
  }
}

void setup() {
  Serial.begin(9600);
  //class: 25
  float SameC1[10] = {-0.5752,  0.0264,  0.4010,  0.3694, -0.2164, -0.3166, -0.3694, -0.4828,
         -0.5198, -0.3878};
  float SameC2[10] = {-0.6498,  0.0556,  0.2536,  0.2632, -0.2632, -0.3672, -0.4542, -0.4710,
         -0.4324, -0.3478};
  //class: 0
  float DiffC[10] = {-0.5038, -0.2724, -0.0958,  0.4004,  0.7352,  0.8326,  0.4978,  0.1902,
          0.1050,  0.1812};
  
  //initializing empty vectors
  float resultC1[DIMENSIONS] = {0};
  float resultC2[DIMENSIONS] = {0};
  float resultDiffC[DIMENSIONS] = {0};

  //initializing empty hamming distances
  int hamming_distanceSame = 0;
  int hamming_distance1vDiff = 0;
  int hamming_distance2vDiff = 0;
  
  //Generating random seed value
  int seed = random(100000);

  //Generating random hyper vectors for each tensor
  Projection(seed, 10, DIMENSIONS, SameC1, resultC1);
  hard_quantize(resultC1);

  Projection(seed, 10, DIMENSIONS, SameC2, resultC2);
  hard_quantize(resultC2);

  Projection(seed, 10, DIMENSIONS, DiffC, resultDiffC);
  hard_quantize(resultDiffC);

  //Finding the difference between each pair of hyper vectors
  hamming_distance_similarity(hamming_distanceSame, resultC1, resultC2);
  hamming_distance_similarity(hamming_distance1vDiff, resultC1, resultDiffC);
  hamming_distance_similarity(hamming_distance2vDiff, resultC2, resultDiffC);

  //Printing the differences
  Serial.print("Same class diff: ");
  Serial.println(hamming_distanceSame);

  Serial.print("Diff class between first and different: ");
  Serial.println(hamming_distance1vDiff);

  Serial.print("Diff class between second and different: ");
  Serial.println(hamming_distance2vDiff);
}

void loop() {
  // do nothing
}