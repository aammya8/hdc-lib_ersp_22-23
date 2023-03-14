/*
ID-Level Encoding
*/

#include "id-lvl.h"
#include "isolet.h"


ID_Level_Encoder::ID_Level_Encoder(int n) {
  num_vectors = n;
  id = random_hv();
  level = level_hv();
}


/* 
  * Return array of random binary hypervectors (1 and -1)
  * Each row in array corresponds to different random hypervector
  * e.g. row 0 corresponds to hv0, row 1 to hv1, etc. 
*/
double[][] ID_Level_Encoder::random_hv() {

    // 2-D array to store all num_vectors random binary hypervectors
    double random_hv_set[num_vectors][DIMENSION];

    // Generate random hypervectors
    int lower = 0;
    int upper = 1;
    srand(time(0));
    for (int hv = 0; hv < num_vectors; hv++) {
      for (int element = 0; element < DIMENSION; element++) {
        random_hv_set[hv][element] = (double) (rand() % (upper - lower + 1)) + lower;
        printf("%f ", random_hv_set[hv][element]);
      }
      printf("\n");
    }

    return random_hv_set;
}




double[][] ID_Level_Encoder::level_hv() {
  int levels_per_span = (1 - RANDOMNESS) * (num_vectors - 1) + RANDOMNESS * 1; 
  levels_per_span = max(levels_per_span, 1);
  int span = (num_vectors - 1) / levels_per_span;

  /* Random number generator (Uniform Real Distribution from 0 to 1) */
  const double range_from = 0.0;
  const double range_to = 1.0;
  std::default_random_engine generator;
  std::uniform_int_distribution<double>  distr(range_from, range_to);

  /* 
   * Generate 2 random hv for min hv (L1) and max hv (Lm) in span
   * After bits flipped in for-loop below in agreement with https://arxiv.org/pdf/2205.07920.pdf, 
   * L1 and Lm will share exactly d/2 bits, making them precisely orthogonal
   */
  double[ceil(span+1)][DIMENSION] span_hv; // 2 x DIMENSION
  for (int i = 0; i < DIMENSION; i++) {
    double n1 = distribution(generator);
    span_hv[0][i] = n1;
    double n2 = distribution(generator);
    span_hv[1][i] = n2;
  }


  /* Generate random threshold */
  double[DIMENSION] threshold_v; // ceil(span) x DIMENSION = 1 x DIMENSION
  for (int i = 0; i < DIMENSION; i++) {
    double n = distribution(generator);
    threshold_v[i] = n;
  }


  double[num_vectors][DIMENSION] hv; // empty hypervectors

  for (int i = 0; i < num_vectors; i++) {
    int span_idx = (int) floor(i / levels_per_span);

    // NOTE: special case not included for now

    int level_within_span = i % levels_per_span;

    double t = 1 - (level_within_span / levels_per_span); // threshold value from start_hv perspective

    double[] span_start_hv = span_hv[span_idx];
    double[] span_end_hv = span_hv[span_idx + 1];
    hv[i] = (threshold_v[span_idx] < t) ? span_start_hv : span_end_hv;
  }

  return hv;
}



double[][] ID_Level_Encoder::bind(double [] id, double [] value) {
  const double range_from = 0.0;
  const double range_to = 1.0;
  std::default_random_engine generator;
  std::uniform_int_distribution<double>  distr(range_from, range_to);
  int target[num_vectors];
  double hv[][];
  double[DIMENSION] threshold_v; // ceil(span) x DIMENSION = 1 x DIMENSION

  for (int i = 0; i < DIMENSION; i++) {
    double n = i/DIMENSION;
    threshold_v[i] = n;
  }

  for (int i = 0; i < num_vectors; i++) {
    //generate index for each value 
    double pick = threshold_v[0];
    int index = 0;
    while (value[i] > threshold_v[index]){
      index++;
    }
    pick = min(threshold_v[index]-value[i], value[i]-threshold_v[index])
    if (pick == threshold_v[index-1])
      index--;
    target[i] = index
  }

  for (int i = 0; i < num_vectors; i++){
    int index = targte[i];
    for (int j = 0; i < DIMENSION; i++){
      if (id[index][j]*level[index][j] > 0)
        hv[i][j] = 1;
      else
        hv[i][j] = 0;
    }
  }
  return hv;
}



double[] ID_Level_Encoder::multiset(double [] sample) {
  double hv[];
  for (int i = 0; i < sample[0].size(); i++){
    double total;
    for (int j = 0; j < sample[0].size(); i++)
      total += sample[i][j];
      hv[i] = total;
    }
    return hv;
}



double[] ID_Level_Encoder::hard_quantize(double [] sample){
  double hv[];
  for (int i = 0; i < sample.size(); i++){
    if (sample[i] > 0)
      hv[i] = 1;
    else
      hv[i] = 0;
  }
  return hv;
}




double[] ID_Level_Encoder::ID_Level_Forward(double [] x) {

  // TODO
  double smple_hv[][] = bind(id, x)
  double result = multiset(smple_hv)
  return hard_quantize(x);
}




void setup() {
  // put your setup code here, to run once:
  int num_vec = isolet.size();
  ID_Level_Encoder encoder = new ID_Level_Encoder(num_vec);
  double forWard[] = encoder.forward(x);
  for (int i = 0; i < num_vec; i++)
    cout << forWard[i];
}

void loop() {
  // put your main code here, to run repeatedly:

  // ?

}
