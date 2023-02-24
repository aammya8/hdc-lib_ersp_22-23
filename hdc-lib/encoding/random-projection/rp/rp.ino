// imports
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <random>
#include <vector>
// statistic c library: https://github.com/christianbender/statistic
// #include <statistic.h>

using namespace std;

/*
 * Torch functions:
 * hard_quantize
 * Sinusoid
 * linear 
 * normalize
 */

//Applies binary quantization to all elements of the input tensor.
//TODO: add pointers
void hard_quantize (float x[])
{
  // but it's not a tensor?
  // ex usage: torchhd.hard_quantize(sample_hv)
  //tensor([ 2.,  0., -2.,  0.,  2.,  0.])
  // >>> torchhd.hard_quantize(y)
  //tensor([ 1., -1., -1., -1.,  1., -1.])
  // torch.bincount(input, weights=None, minlength=0)

  //for item in array
  //if item <= 0
  //item = 0
  //else: item = 1
  for(int i = 0; i < x.size(); i++) {
    if (x[i] < 0) {
        x[i] = 0;
    } else {
      x[i] = 1;
    }
  }
}

/*
multiply by the weight and add the bias
*/
 void linear(float *input, float *weight, float *output) {
    // Iterate over the elements of the output vector
    for (int i = 0; i < output.size(); i++) {
        //Initialize the i-th element of the output vector to zero
        output[i] = 0;
        // Iterate over the columns of the weight matrix
        for (int j = 0; j < DIMENSIONS; j++) {
            //dot product of the input vector and the weight matrix
            output[i] += input[j] * weight[i*COLS + j];
        }
    }
}

/*
 * performs normalization of inputs over a specified dimension
 */
void normalize()
{
  
}


// TODO: Sinusoid -> Projection
/*
 * Projection: does matrix multiplication with the input tensor/data (vector<float>)
 * and a randomly generated matrix to produce a random hypervector
 * @param in_features = dimension of the input vector
 * @param out_features (1000) = output dimension of the hypervector
 * @return = random generated hypervector
 */

// TODO: CREATING THE RANDOM MATRIX
 // Step 1: generate the random empty matrix with dimensions of out_features
 // Step 2: fill matrix with random normal distribution values  with LIBRARY
 // weight = https://www.tutorialspoint.com/generate-random-numbers-following-a-normal-distribution-in-c-cplusplus
 // Step 3: normalize weight? NOT THIS WEEK
 //

/*
 * Embedding using a nonlinear random projection
 */
void Sinusoid (int size, int dimensions)
{
  weight = 
  bias = 

  // F.linear(input, self.weight)
  projected = linear(weight);
  // torch.cos(projected + self.bias) * torch.sin(projected)
  vector<float> output = cos(projected + bias)*sin(projected);
  return output;
}

// number of hypervector dimensions
const double DIMENSIONS = 1000;

// number of features in dataset
const double NUM_FEATURES = 5;

class RP_Encoder {
  public:
    float lr;
    vector<float> M;
    vector<float> project;

    /* Constructor */
    RP_Encoder() : lr(0.00001), M(DIMENSIONS), project(DIMENSIONS) {}

    // encode defined within the class SingleModel
    vector<float> encode(vector<float> x, int size) {
      this->project = Sinusoid(size, DIMENSIONS);
      return hard_quantize(this->project); 
    }

    // model_update defined within the class SingleModel
    void model_update(vector<float> x, int y) {
      vector<float> update = this->M + this->lr*(y-(linear(x, this->M)))*x;
      update = update.mean(0);
      this->M = update;
    }

    // forward defined within the class SingleModel
    vector<float> forward(vector<float> x) {
      vector<float> enc = encode(x);
      vector<float> res = linear(enc, this->M);
      return res;
    }
}
// download part


// Get necessary statistics for data and target transform
double STD_DEVS
double MEANS 
double TARGET_STD
double TARGET_MEAN

// transform function


// target_transform function


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
