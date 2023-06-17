/*
 * This file contains the C++ version random projection code
 */

// imports
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <random>
#include <vector>

using namespace std;

// number of hypervector dimensions
const double DIMENSIONS = 1000;

// number of features in dataset
const double NUM_FEATURES = 5;

/**
 * Hamming_distance_similarity: finds the bit difference between two hypervectors
 * @param hv1 = the first hypervector
 * @param hv2 = the second hypervector
 * @returns an integer value of the number of differences between the two hypervectors
 */
Finds the bit difference between two hypervectors
int hamming_distance_similarity (vector<float> hv1, vector<float> hv2)
{
  int hamming_distance = 0;

  for (int i = 0; i < DIMENSIONS; i++) {
    if (hv1[i] != hv2[i]) {
      hamming_distance++;
    }
  }
  return hamming_distamce;
}


/**
 * Hard_quantize: applies binary quantization to all elements of the input tensor
 * @param x = the input tensor
 * @returns vector with binary values
 */
vector<float> hard_quantize (vector<float> x)
{
  vector<float> hqVector(x.size());
  for(int i = 0; i < x.size(); i++) {
    if (x[i] <= 0) {
        hqVector[i] = -1;
    } else {
      hqVector[i] = 1;
    }
  }
  return hqVector;
}

/**
 * Normalize: performs normalization of inputs by rows (dimension = 1)
 * @param input = 2 dimensional vector with data that requires normalization
 */
void normalize(vector<vector<float>> &input)
{
  // work on each row in the 2d vector
  for(vector<float> &row: input){
    // calculate magnitude of the row
    float magnitude = 0;
    for(float x: row){
      magnitude += x*x;
    }
    magnitude = sqrt(magnitude);

    // normalize the x
    for (float &x: row) {
      x = x/magnitude;
    }
  }
}


/**
 * Projection: does matrix multiplication with the input tensor/data (vector<float>)
 * and a randomly generated matrix to produce a random hypervector
 * @param in_features = dimension of the input vector
 * @param out_features (1000) = output dimension of the hypervector
 * @return = random generated hypervector
 */

vector<float> Projection(int in_features, int out_features, vector<float>tensor){
  // instantiating matrix with rows
  vector<vector<float>> weight(out_features);
  // instantiating each row with the number of columns
  for (int i = 0; i < out_features; ++i){
    weight[i].resize(in_features);
  }
  // filling matrix with rnd normal distribution
  srand(time(NULL)); // Set a random seed value
  default_random_engine generator(rand()); // Use the seed value for the random engine
  normal_distribution<float> distribution(0,1);

  for (int row = 0; row < out_features; ++row){
    for(int col = 0; col < in_features; ++col){
      weight[row][col] = distribution(generator);
    }
  }

  // normalize weight
  normalize(weight);

  // instantiating hypervector
  vector<float> result(out_features); 

  // MATRIX MULTIPLICATION SECTION
  for (int r = 0; r < out_features; ++r){
    for (int c = 0; c < in_features; ++c){
       result[r] += weight[r][c]*tensor[c];
    }
  }

  return result;
}

/**
 * RP_Encoder: a class for random projection with a constructor and a class function
 */
class RP_Encoder {
  public:
    float lr;
    vector<float> M;
    vector<float> project;

    /* Constructor */
    RP_Encoder() : lr(0.00001), M(DIMENSIONS), project(DIMENSIONS) {}

    // encode defined within the class SingleModel
    vector<float> encode(vector<float> x, int size) {
      this->project = Projection(size, DIMENSIONS, x);
      this->project = hard_quantize(this->project); 
      return this->project;
    }
};

int main() {
  // Data retrieved from the ISOLET data set
  // class: 25
  vector<float> SameC1 = {-0.5752,  0.0264,  0.4010,  0.3694, -0.2164, -0.3166, -0.3694, -0.4828,
         -0.5198, -0.3878};
  vector<float> SameC2 = {-0.6498,  0.0556,  0.2536,  0.2632, -0.2632, -0.3672, -0.4542, -0.4710,
         -0.4324, -0.3478};
  // class: 0
  vector<float> DiffC = {-0.5038, -0.2724, -0.0958,  0.4004,  0.7352,  0.8326,  0.4978,  0.1902,
          0.1050,  0.1812};


  RP_Encoder np;
  vector<float> sample1 = np.encode(SameC1, SameC1.size());
  vector<float> sample2 = np.encode(SameC2, SameC2.size());
  vector<float> sample3 = np.encode(DiffC, DiffC.size());
  int diffC1vC2 = hamming_distance_similarity(sample1, sample2);
  int diffC1vDiff = hamming_distance_similarity(sample1, sample3);
  int diffC2vDiff = hamming_distance_similarity(sample3, sample2);
  
  cout << "difference between data in same class: " << diffC1vC2 << endl;
  cout << "difference between data in different class (first and last vector): " << diffC1vDiff << endl;
  cout << "difference between data in different class (second and last vector): " << diffC2vDiff << endl;
  return 0;
}
