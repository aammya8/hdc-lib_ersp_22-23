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

/*
 * Torch functions:
 * hard_quantize
 * Sinusoid
 * linear 
 * normalize
 */

//Applies binary quantization to all elements of the input tensor.
vector<float> hard_quantize (vector<float> x)
{
  // ex usage: torchhd.hard_quantize(sample_hv)
  //tensor([ 2.,  0., -2.,  0.,  2.,  0.])
  // >>> torchhd.hard_quantize(y)
  //tensor([ 1., -1., -1., -1.,  1., -1.])
  // torch.bincount(input, weights=None, minlength=0)

  //for item in array
  //if item <= 0
  //item = 0
  //else: item = 1
  vector<float> hqVector(x.size());
  for(int i = 0; i < x.size(); i++) {
    if (x[i] <= 0) {
        hqVector[i] = -1;
        //hqVector.push_back(0);
    } else {
      hqVector[i] = 1;
      //hqVector.push_back(1);
    }
  }
  return hqVector;
}

/*
 * multiply by the weight and add the bias
 */
//  void linear(float input, float weight, float output) {
//     // Iterate over the elements of the output vector
//     for (int i = 0; i < output.size(); i++) {
//         //Initialize the i-th element of the output vector to zero
//         output[i] = 0;
//         // Iterate over the columns of the weight matrix
//         for (int j = 0; j < DIMENSIONS; j++) {
//             //dot product of the input vector and the weight matrix
//             output[i] += input[j] * weight[i*COLS + j];
//         }
//     }
// }

/*
 * performs normalization of inputs by rows (dimension = 1)
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


/*
 * Projection: does matrix multiplication with the input tensor/data (vector<float>)
 * and a randomly generated matrix to produce a random hypervector
 * @param in_features = dimension of the input vector
 * @param out_features (1000) = output dimension of the hypervector
 * @return = random generated hypervector
 */

// DONE - TODO: CREATING THE RANDOM MATRIX
 // DONE - Step 1: generate the random empty matrix with dimensions of out_features
 // DONE - Step 2: fill matrix with random normal distribution values  with LIBRARY
 // weight = https://www.tutorialspoint.com/generate-random-numbers-following-a-normal-distribution-in-c-cplusplus
 // DONE - Step 3: normalize weight
 //

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
      this->project = Projection(size, DIMENSIONS, x);
      this->project = hard_quantize(this->project); 
      return this->project;
    }

     /*
     * model_update: creates a model for linear regression
     * used for reghd.py, but ours is random projection
     */
    // void model_update(vector<float> x, int y) {
    //   vector<float> update = this->M + this->lr*(y-(linear(x, this->M)))*x;
    //   update = update.mean(0);
    //   this->M = update;
    // }

    // forward defined within the class SingleModel
    // vector<float> forward(vector<float> x) {
    //   vector<float> enc = encode(x, x.size());
    //   // vector<float> res = linear(enc, this->M); NOT NECESSARY FOR RP
    //   return res;
    // }
};

int main() {
  // correct output: ([[-1.,  1., -1.,  ..., -1.,  1., -1.]])
    vector<float> x = {-0.6624, -0.3334,  0.3666,  0.4292, -0.2084};
         
  RP_Encoder np;
  vector<float> sample = np.encode(x, x.size());
  for(float elements: sample){
    cout << elements << endl;
  }
  cout << endl;
  return 0;
}
