/*
ID-Level Encoding
*/

#include "id-lvl.h"
#include "isolet.h"


ID_Level_Encoder::ID_Level_Encoder(int n) {
      num_vectors = n;
      id = random_hv();
      value = level_hv();
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
      // https://www.includehelp.com/c-programs/generate-random-numbers-within-a-range.aspx
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
  int levels_per_span = (1 - RANDOMNESS) * (num_vectors - 1) + RANDOMNESS * 1; // RANDOMNESS defined as 0
  levels_per_span = max(levels_per_span, 1);
  int span = (num_vectors - 1) / levels_per_span;

  double[ceil(span+1)][DIMENSION] span_hv; // 2 x DIMENSION

  // TODO: generate 2 orthogal hv FOR SPAN_HV

  double[ceil(span)][DIMENSION] threshold_v; // 1 x DIMENSION

  // TODO random generate threshold
  // https://stackoverflow.com/questions/288739/generate-random-numbers-uniformly-over-an-entire-range
  // https://cplusplus.com/reference/random/uniform_real_distribution/
  const double range_from = 0.0;
  const double range_to = 1.0;
  std::random_device                  rand_dev;
  std::mt19937                        generator(rand_dev());
  std::uniform_int_distribution<double>  distr(range_from, range_to);



  double[num_vectors][DIMENSION] hv; // empty hypervectors

  for (int i = 0; i < num_vectors; i++) {
    int span_idx = (int) floor(i / levels_per_span);

    // NOTE: special case check ignored for now

    int level_within_span = i % levels_per_span

    double t = 1 - (level_within_span / levels_per_span);

    double[] span_start_hv = span_hv[span_idx];
    double[] span_end_hv = span_hv[span_idx + 1];
    hv[i] = (threshold_v[span_idx] < t) ? span_start_hv : span_end_hv;
  }


  return hv;
}



double[][] ID_Level_Encoder::bind(double [] weight, double [] value) {
  double hv[][];
  for (int i = 0; i < weight.size(); i++){
    for (int j = 0; i < weight[0].size(); i++){
      if (weight[i][j]*value[i][j] > 0)
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




double[] ID_Level_Encoder::ID_Level_Forward(double[] id, double [] x) {
  
}




void setup() {
  // put your setup code here, to run once:
  int num_vec = isolet.size();
  ID_Level_Encoder encoder = new ID_Level_Encoder(num_vec);
}

void loop() {
  // put your main code here, to run repeatedly:

}
