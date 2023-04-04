/*
 * Arduino version code
 */
#include <stdio.h>
#include <math.h>
#include <random>
#include <vector>

using namespace std;

// Applies binary quantization to all elements of the input tensor.
vector<float> hard_quantize(vector<float> x)
{
    vector<float> hqVector(x.size());
    for (int i = 0; i < x.size(); i++) {
        if (x[i] <= 0) {
            hqVector[i] = -1;
        } else {
            hqVector[i] = 1;
        }
    }
    return hqVector;
}

/*
 * performs normalization of inputs by rows (dimension = 1)
 */
void normalize(vector<vector<float>> &input)
{
    for (vector<float> &row: input){
        float magnitude = 0;
        for (float x: row){
            magnitude += x*x;
        }
        magnitude = sqrt(magnitude);

        for (float &x: row) {
            x = x / magnitude;
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

// CREATING THE RANDOM MATRIX
// Step 1: generate the random empty matrix with dimensions of out_features
// Step 2: fill matrix with random normal distribution values
// Step 3: normalize weight
vector<float> Projection(int in_features, int out_features, vector<float> tensor)
{
    vector<vector<float>> weight(out_features);
    for (int i = 0; i < out_features; ++i){
        weight[i].resize(in_features);
    }
    default_random_engine generator;
    normal_distribution<float> distribution(0,1);

    for (int row = 0; row < out_features; ++row){
        for (int col = 0; col < in_features; ++col){
            weight[row][col] = distribution(generator);
        }
    }

    normalize(weight);

    vector<float> result(out_features);

    for (int r = 0; r < out_features; ++r){
        for (int c = 0; c < in_features; ++c){
            result[r] += weight[r][c] * tensor[c];
        }
    }

    return result;
}

// number of hypervector dimensions
const float DIMENSIONS = 1000;

// number of features in dataset
const float NUM_FEATURES = 5;

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
        //   vector<float> update =...
        // }
};


void setup() {
  vector<float> x = {-0.6624, -0.3334, 0.3666, 0.4292, -0.2084};
  RP_Encoder np;
  vector<float> sample = np.encode(x, x.size());
  Serial.begin(9600);
  Serial.print("[");
  for (int i = 0; i < sample.size(); i++) {
    Serial.print(sample[i], DEC);
    if (i != sample.size() - 1) {
      Serial.print(", ");
    }
  }
  Serial.println("]");
  
}

void loop() {
  // put your main code here, to run repeatedly:

}