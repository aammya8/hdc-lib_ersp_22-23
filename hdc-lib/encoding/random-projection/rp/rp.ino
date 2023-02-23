// imports
#include <stdio.h>
#include <iostream>
#include <math.h>
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
  float output[] = cos(projected + bias)*sin(projected);
  return output;
}

// number of hypervector dimensions
double DIMENSIONS = 1000;

// number of features in dataset
double NUM_FEATURES = 5;

// struct
struct SingleModel 
{
    float lr;
    float M[DIMENSIONS];
    float project[DIMENSIONS];
    
    // encode defined within the class SingleModel
    float[] encode(float x[], int size) {
      project = Sinusoid(size, DIMENSIONS);
      return hard_quantize(project); 
    }

    // model_update defined within the class SingleModel
    void model_update(float x[], int y) {
      lr = 0.00001;
      M = M + lr*(y-(linear(x, M)));
      M = M.mean(0);
    }

    // forward defined within the class SingleModel
    float[] forward(float x[]) {
      float enc[] = encode(x);
      float res[] = linear(enc, M);
      return res;
    }
};

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
