/*
ID-Level Encoding
*/

#include "id_lvl.h"

// float y[617] = {-0.0438,  0.7912,  0.8622, -0.0146, -0.4780, -0.6660, -0.9750, -0.7704,
//          -0.9164, -0.9416, -0.7828, -0.8456, -0.5282, -0.4906, -0.2318, -0.0814,
//           0.3068,  0.6534,  0.9416,  0.9040,  0.8664,  0.8080,  0.9708,  1.0000,
//           1.0000,  0.8246,  0.7828,  0.6702,  0.5782,  0.6076,  0.6660,  0.4614,
//          -0.0574,  0.5676,  0.6318,  0.0574, -0.4662, -0.5068, -0.6722, -0.8918,
//          -0.9426, -0.8986, -0.6418, -0.7500, -0.5506, -0.5642, -0.4426, -0.2702,
//          -0.0778,  0.3378,  0.5676,  0.7364,  0.6082,  0.4730,  0.5136,  0.8244,
//           0.8784,  1.0000,  0.9324,  0.6824,  0.5608,  0.3952,  0.5406,  0.4764,
//          -0.0738,  0.5512,  0.5706,  0.0320, -0.5320, -0.6218, -0.6730, -0.8590,
//          -0.8782, -0.9294, -0.7244, -0.6026, -0.5576, -0.5192, -0.4488, -0.3622,
//          -0.1346,  0.1538,  0.5738,  0.7596,  0.6826,  0.3462,  0.4680,  0.5834,
//           0.9392,  1.0000,  0.9358,  0.8878,  0.5384,  0.4262,  0.4358,  0.3910,
//           0.0134,  0.6262,  0.5758, -0.0572, -0.5354, -0.7812, -0.8922, -0.9226,
//          -0.9664, -0.9696, -0.9494, -0.7946, -0.7004, -0.5858, -0.4410, -0.4242,
//          -0.1886,  0.1380,  0.6026,  0.7442,  0.5622,  0.1920,  0.4478,  0.5454,
//           0.9394,  1.0000,  0.9360,  0.8856,  0.5858,  0.4176,  0.4344,  0.4478,
//           0.1034,  0.5866,  0.4606, -0.1208, -0.5552, -0.8178, -0.9720, -0.9510,
//          -0.8528, -0.9300, -0.9510, -0.8914, -0.7654, -0.6392, -0.5062, -0.4256,
//          -0.1384,  0.1558,  0.5936,  0.7092,  0.4010,  0.1628,  0.3346,  0.5026,
//           0.9194,  1.0000,  0.9860,  0.8914,  0.4852,  0.4046,  0.4816,  0.5622,
//          -0.0138,  0.3702,  0.2734, -0.2146, -0.5502, -0.7336, -0.9204, -0.8408,
//          -0.8996, -0.8650, -0.9204, -0.9170, -0.7162, -0.5606, -0.4810, -0.5156,
//          -0.2492,  0.2214,  0.7336,  0.8028,  0.3252,  0.2006,  0.3288,  0.5260,
//           0.8962,  1.0000,  1.0000,  0.9550,  0.3772,  0.3772,  0.4394,  0.4776,
//          -0.1832,  0.3408,  0.2700, -0.3794, -0.5274, -0.8842, -0.8102, -0.7846,
//          -0.8650, -0.9550, -0.8456, -0.7138, -0.7170, -0.6078, -0.4952, -0.3504,
//          -0.2154,  0.3762,  0.6528,  0.5852,  0.2122,  0.0610,  0.2766,  0.5048,
//           0.9228,  1.0000,  0.8360,  0.8456,  0.4116,  0.3570,  0.4920,  0.4662,
//          -0.0858,  0.6000,  0.6000, -0.0286, -0.2572, -0.7142, -0.9428, -0.9428,
//          -0.7714, -0.8286, -0.7142, -0.5428, -0.5428, -0.2572, -0.0286,  0.3714,
//           0.4858,  0.7714,  0.6572,  0.7142,  0.9428,  0.7142,  1.0000,  0.8858,
//           0.7142,  0.5428,  0.5428,  0.5428,  0.6572,  0.7714,  0.4286, -0.0858,
//           0.0000,  0.5652,  0.6086,  0.1304, -0.2608, -0.3914, -0.6522, -0.5652,
//          -0.7392, -0.7392, -0.7826, -0.6086, -0.4348, -0.3914, -0.1740, -0.0434,
//           0.2608,  0.6522,  0.6956,  0.6522,  0.6522,  0.7392,  1.0000,  1.0000,
//           0.7826,  0.6086,  0.5652,  0.5218,  0.4348,  0.5652,  0.6086,  0.3478,
//           0.1428,  0.4958,  0.4286, -0.0084, -0.2942, -0.5630, -0.9160, -0.4286,
//          -0.4118, -0.4958, -0.5294, -0.5294, -0.2774, -0.3278, -0.2268, -0.2942,
//          -0.0588,  0.2942,  0.6470,  0.6806,  0.3278,  0.2436,  0.3950,  0.5966,
//           0.8992,  1.0000,  0.9496,  0.8320,  0.4286,  0.2100,  0.5630,  0.5126,
//          -0.9858, -0.8654, -0.5536, -0.5350, -0.5162, -0.5620, -0.6190, -0.6786,
//          -0.7658, -0.7866, -0.1242,  0.8856,  0.7446,  0.2774,  0.0866,  0.0886,
//           0.1068,  0.1054, -0.0646, -0.3576, -0.5272, -0.5712, -0.5970, -0.5958,
//          -0.6746, -0.6792, -0.7522, -0.6694, -0.8662, -0.9224, -0.9320, -0.9366,
//          -0.9632, -0.9640, -0.8662, -0.6100, -0.5420, -0.5430, -0.5906, -0.6686,
//          -0.7210, -0.7960, -0.7658,  0.0288,  0.8846,  0.6436,  0.4098,  0.2574,
//           0.2616,  0.2040,  0.1650,  0.0582, -0.1006, -0.3020, -0.2372, -0.2170,
//          -0.0356, -0.1606, -0.3256, -0.6262, -0.6002, -0.8306, -0.8778, -0.8630,
//          -0.8904, -0.9172, -0.7954, -0.6188, -0.8254, -0.8088, -0.8320, -0.8688,
//          -0.8988, -0.9088, -0.8154, -0.8388, -0.4820, -0.7946, -0.8196, -0.7246,
//          -0.6726, -0.7250, -0.7800, -0.8576, -0.7912, -0.6046, -0.5734, -0.5356,
//          -0.4600, -0.2768, -0.1934, -0.2068, -0.6534, -0.7200, -0.5700, -0.2868,
//          -0.4368, -0.5968, -0.6600, -0.1428,  0.6286,  0.7428, -0.6858, -0.9142,
//          -0.8572, -0.8858, -0.8572, -0.4572,  1.0000,  1.0000,  0.3142, -0.6858,
//          -0.9428, -0.9714, -1.0000, -1.0000, -0.8858, -0.8286, -0.6572, -0.9714,
//          -0.5142, -0.1428, -0.3428, -0.4858, -0.7142,  0.4858, -0.5142, -0.1714,
//          -0.0572, -0.4286, -0.4000, -0.6572, -0.9752, -0.9906, -1.0000, -1.0000,
//          -1.0000, -1.0000, -1.0000, -1.0000, -1.0000, -1.0000,  0.6254,  0.6684,
//           0.6798,  0.7126,  0.7270,  0.7746,  0.8156,  0.8802,  0.9588,  0.9502,
//           0.1066, -0.0352,  0.1404,  0.6902,  0.8720,  1.0000,  0.7354, -0.1334,
//           0.4872,  0.6752,  0.6410,  0.6068,  0.6240,  0.3162,  0.8804,  1.0000,
//           1.0000,  0.8120,  0.8974,  0.8974,  0.8974,  0.7436,  0.9316,  0.9488,
//           0.9146,  0.7436,  0.7436,  0.9146,  0.8974,  0.9146,  0.8974,  0.8290,
//           0.8290,  0.9488,  0.8974,  0.9146,  0.8290,  0.6068,  0.2992,  0.1282,
//           0.5600,  0.7866,  0.4134,  0.3066,  0.2534,  0.2266,  0.3866,  0.9866,
//           0.9866,  0.8400,  0.9866,  0.9066,  0.8134,  0.7866,  1.0000,  0.9200,
//           0.6666,  0.5066,  0.8400,  0.8934,  0.7866,  0.7734,  0.8000,  0.8266,
//           0.7066,  0.6134,  0.7466,  0.6266,  0.4934,  0.5334,  0.3866,  0.0266,
//           0.2318,  0.5732,  0.1464, -0.2926, -0.2074, -0.2804, -0.0854,  0.1708,
//           0.6464,  0.6830,  1.0000,  0.9268,  0.3170,  0.4268,  0.4146,  0.5244,
//           0.0610, -0.0854,  0.2682,  0.3414,  0.2074,  0.3780,  0.1342,  0.3292,
//           0.2804,  0.3414,  0.1830,  0.1464,  0.1342, -0.0122, -0.0122, -0.2804,
//           0.4074, -1.0000, -1.0000,  1.0000, -0.6000,  1.0000, -0.8000, -0.7334,
//           1.0000,  0.0798,  0.2270, -0.0430, -0.1534, -0.1412, -0.2638, -0.1412,
//           0.1042,  0.6932,  1.0000,  0.6442,  0.7178,  0.6932,  0.5706,  0.6320,
//           0.7546,  0.4110,  0.2270,  0.2392, -0.0062, -0.0062,  0.1166, -0.0674,
//           0.0798,  0.2148,  0.2270,  0.2638, -0.1166, -0.0062,  0.0184, -0.1780,
//          -0.2760};


void hamming_distance_similarity(int & hamming_distance, float hv1[DIMENSION], float hv2[DIMENSION]){
  hamming_distance = 0;

  for (int i = 0; i < DIMENSION; i++) {
    if (hv1[i] != hv2[i]) {
      hamming_distance++;
    }
  }
}




ID_Level_Encoder::ID_Level_Encoder(int n) {
  num_vectors = n;
  random_hv();
  level_hv();
}


/* 
  * Return array of random binary hypervectors (1 and -1)
  * Each row in array corresponds to different random hypervector
  * e.g. row 0 corresponds to hv0, row 1 to hv1, etc. 
*/
void ID_Level_Encoder::random_hv() {

    // 2-D array to store all num_vectors random binary hypervectors
    // Generate random hypervectors
    for (int hv = 0; hv < num_vectors; hv++) {
      for (int element = 0; element < DIMENSION; element++) {
        id[hv][element] = double (rand()%2);
        //printf("%f ", random_hv_set[hv][element]);
      }
      //printf("\n");
    }
}




void ID_Level_Encoder::level_hv() {
  int levels_per_span = 1;
  //(1 - RANDOMNESS) * (num_vectors - 1) + RANDOMNESS * 1; 
  //levels_per_span = max(levels_per_span, 1);
  int span = 0;
  //(num_vectors - 1) / levels_per_span;

  /* Random number generator (Uniform Real Distribution from 0 to 1) */
  /*
  const double range_from = 0.0;
  const double range_to = 1.0;
  std::default_random_engine generator;
  std::uniform_real_distribution<double>  distr(range_from, range_to);*/
  /* 
   * Generate 2 random hv for min hv (L1) and max hv (Lm) in span
   * After bits flipped in for-loop below in agreement with https://arxiv.org/pdf/2205.07920.pdf, 
   * L1 and Lm will share exactly d/2 bits, making them precisely orthogonal
   */
    
  int row = ceil(span+1);
  double span_start_hv[DIMENSION];
  double span_end_hv[DIMENSION];
  //double span_hv[row][DIMENSION]; // 2 x DIMENSION
    
  /*
  for (int i = 0; i < DIMENSION; i++) {
    double n1 = distr(generator);
    span_hv[0][i] = n1;
    double n2 = distr(generator);
    span_hv[1][i] = n2;
  }*/
  for (int i = 0; i < DIMENSION; i++){
      //span_hv[0][i] = double(rand()%2);
      //span_hv[1][i] = double(rand()%2)
      span_start_hv[i] = double(rand()%2);
      span_end_hv[i] = double(rand()%2);
  }


  /* Generate random threshold */
  //double threshold_v[DIMENSION]; // ceil(span) x DIMENSION = 1 x DIMENSION
  /*
  for (int i = 0; i < DIMENSION; i++) {
    double n = distr(generator);
    threshold_v[i] = n;
  }*/
  for (int i = 0; i < num_vectors; i++) {
    threshold_v[i] = double(double(i)/(num_vectors-1));
  }
    


  for (int i = 0; i < num_vectors; i++) {
    int span_idx = (int) floor(double(i) / levels_per_span);
    //cout << "span_idx = " << i << " ";

    // NOTE: special case not included for now

    int level_within_span = i % levels_per_span;

    double t = 1 - (double(level_within_span) / double(levels_per_span)); // threshold value from start_hv perspective
    for (int j = 0; j < DIMENSION; j++){
        //double span_start_hv[j] = span_hv[0][j];
        //double span_end_hv[j] = span_hv[1][j];
        /*
        if (threshold_v[span_idx] < t)
            level[i][j] = span_start_hv[j];
        else
            level[i][j] = span_end_hv[j];*/
        //level[i][j] = (threshold_v[i] < t) ? span_start_hv[j] : span_end_hv[j];
        level[i][j] = (threshold_v[span_idx] < t) ? span_start_hv[j] : span_end_hv[j];
        //Error Core dumped here
    }
      
  }


}



void ID_Level_Encoder::bind(float value[]) {
  const double range_from = 0.0;
  const double range_to = 1.0;
  int target[num_vectors];

  for (int i = 0; i < num_vectors; i++) {
    //generate index for each value 
    double pick = threshold_v[0];
    int index = 0;
    while (value[i] > threshold_v[index]){
      index++;
    }
      
    pick = min(threshold_v[index]-value[i], value[i]-threshold_v[index-1]);
    if (index != 0 & pick == threshold_v[index-1])
      index--;
    target[i] = index;
  }


  for (int i = 0; i < num_vectors; i++){
    int index = target[i];
    for (int j = 0; j < DIMENSION; j++){
      if ((id[index][j] * level[index][j]) > 0)
          hv[i][j] = 1;
      else
          hv[i][j] = 0;
    }
  }
}



void ID_Level_Encoder::multiset() {
  for (int i = 0; i < DIMENSION; i++){
    double total = 0;
    for (int j = 0; j < num_vectors; j++){
      total += hv[j][i];
    }
    sample_hv[i] = total;
  }
}



void ID_Level_Encoder::hard_quantize(){
  for (int i = 0; i < DIMENSION; i++){
    if (sample_hv[i] > 0)
      sample_hv[i] = 1;
    else
      sample_hv[i] = 0;
  }
}




void ID_Level_Encoder::ID_Level_Forward(float x[]) {
  bind(x);
  multiset();
  hard_quantize();
}



void setup() {
  Serial.begin(9600);

  //isolet class: 25
  float SameC1[10] = {-0.5752,  0.0264,  0.4010,  0.3694, -0.2164, -0.3166, -0.3694, -0.4828,
         -0.5198, -0.3878};
  float SameC2[10] = {-0.6498,  0.0556,  0.2536,  0.2632, -0.2632, -0.3672, -0.4542, -0.4710,
         -0.4324, -0.3478};
  //isolet class: 0
  float DiffC[10] = {-0.5038, -0.2724, -0.0958,  0.4004,  0.7352,  0.8326,  0.4978,  0.1902,
          0.1050,  0.1812};


  int num_vec1 = sizeof(SameC1)/sizeof(SameC1[0]); // size of data sample
  ID_Level_Encoder* enc1 = new ID_Level_Encoder(num_vec1);
  enc1->ID_Level_Forward(SameC1);
  float* resultC1 = enc1->sample_hv;

  int num_vec2 = sizeof(SameC2)/sizeof(SameC2[0]); // size of data sample
  ID_Level_Encoder* enc2 = new ID_Level_Encoder(num_vec2);
  enc1->ID_Level_Forward(SameC2);
  float* resultC2 = enc2->sample_hv;

  int num_vec3 = sizeof(DiffC)/sizeof(DiffC[0]); // size of data sample
  ID_Level_Encoder* enc_diff = new ID_Level_Encoder(num_vec3);
  enc1->ID_Level_Forward(SameC1);
  float* resultDiffC = enc_diff->sample_hv;



  //initializing empty hamming distances
  int hamming_distanceSame = 0;
  int hamming_distance1vDiff = 0;
  int hamming_distance2vDiff = 0;

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
  // put your main code here, to run repeatedly:

  // srand(time(0));
  // int num_vec = sizeof(y)/sizeof(y[0]); // size of isolet dataset
  // ID_Level_Encoder* encoder = new ID_Level_Encoder(num_vec);
  // encoder->ID_Level_Forward(y);
  // float* sample = encoder->sample_hv;

  // for (int i = 0; i < DIMENSION; i++) {
  //   Serial.print(String(sample[i]));
  //   if (i < (DIMENSION - 1)) {
  //     Serial.print(", ");
  //   }
  // }
}



// -----------------------------------------------------------------------

/*
 * C code:
 */
int main() {

  //isolet class: 25
  float SameC1[10] = {-0.5752,  0.0264,  0.4010,  0.3694, -0.2164, -0.3166, -0.3694, -0.4828,
         -0.5198, -0.3878};
  float SameC2[10] = {-0.6498,  0.0556,  0.2536,  0.2632, -0.2632, -0.3672, -0.4542, -0.4710,
         -0.4324, -0.3478};
  //isolet class: 0
  float DiffC[10] = {-0.5038, -0.2724, -0.0958,  0.4004,  0.7352,  0.8326,  0.4978,  0.1902,
          0.1050,  0.1812};


  int num_vec1 = sizeof(SameC1)/sizeof(SameC1[0]); // size of data sample
  ID_Level_Encoder* enc1 = new ID_Level_Encoder(num_vec1);
  enc1->ID_Level_Forward(SameC1);
  float* resultC1 = enc1->sample_hv;

  int num_vec2 = sizeof(SameC2)/sizeof(SameC2[0]); // size of data sample
  ID_Level_Encoder* enc2 = new ID_Level_Encoder(num_vec2);
  enc1->ID_Level_Forward(SameC2);
  float* resultC2 = enc2->sample_hv;

  int num_vec3 = sizeof(DiffC)/sizeof(DiffC[0]); // size of data sample
  ID_Level_Encoder* enc_diff = new ID_Level_Encoder(num_vec3);
  enc1->ID_Level_Forward(SameC1);
  float* resultDiffC = enc_diff->sample_hv;

  srand(time(0));
  int num_vec = sizeof(y)/sizeof(y[0]); // size of isolet dataset
  ID_Level_Encoder* encoder = new ID_Level_Encoder(num_vec);
  encoder->ID_Level_Forward(y);
  float* sample = encoder->sample_hv;
  for (int i = 0; i < DIMENSION; i++)
    cout << sample[i];
  cout << endl;
  
  return 0;
}