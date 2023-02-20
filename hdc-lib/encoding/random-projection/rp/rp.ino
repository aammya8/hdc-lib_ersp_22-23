// imports
#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;

/*
 * Torch functions:
 * hard_quantize
 * Sinusoid
 * linear 
 * normalize
 */

//Applies binary quantization to all elements of the input tensor.
void hard_quantize (& float[] x)
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
  for(int i = 0; i < sizeOf(x); i++) {
    if (x[i] < 0) {
        x[i] = 0;
    } else {
      x[i] = 1;
    }
  }
}

void linear ()
{
  
}

void normalize()
{
  
}

void Sinusoid (int size, int dimensions)
{
  weight = 
  bias = 

  // F.linear(input, self.weight)
  projected = 
  // torch.cos(projected + self.bias) * torch.sin(projected)
  output = 
  return output;
}

// number of hypervector dimensions
double DIMENSIONS = 1000;

// number of features in dataset
double NUM_FEATURES = 5;

// structs
struct SingleModel 
{
    float lr;
    float M[DIMENSIONS];
    float project[DIMENSIONS];
    
    // encode defined within the class SingleModel
    void encode(& float[] x) {
      
    }

    // model_update defined within the class SingleModel
    void model_update()

    // forward defined within the class SingleModel
    void forward()
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
