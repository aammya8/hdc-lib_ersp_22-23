/*
ID-Level Encoding
*/

#include "id_lvl.h"

float a[10] = {-0.5752,  0.0264,  0.4010,  0.3694, -0.2164, -0.3166, -0.3694, -0.4828,
        -0.5198, -0.3878};
float b[10] = {-0.6498,  0.0556,  0.2536,  0.2632, -0.2632, -0.3672, -0.4542, -0.4710,
        -0.4324, -0.3478};
//class: 0
float c[10] = {-0.5038, -0.2724, -0.0958,  0.4004,  0.7352,  0.8326,  0.4978,  0.1902,
        0.1050,  0.1812};

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
    //char** newId = new char*[num_vectors];
    int element;
    int hv;
    /*for (hv = 0; hv < num_vectors; hv++) {
      //id[hv] = new char[DIMENSION];
      for (element = 0; element < DIMENSION; element++)
        id[hv][element] = int(rand()%2);
        Serial.print(id[hv][element]);
    }*/
    for (int hv = 0; hv < num_vectors; hv++) {
      for (int element = 0; element < DIMENSION/num_vertcors; element++){
        int byte = 0;
        for (int index = 0; index < num_vertcors; index++){
          int ran = rand()%2;
          if (ran == 1)
            byte = (byte << 1) + 1;
          else
            byte = (byte << 1);
        }
        id[hv][element] = byte;
      }
      //the remining bit
      if(DIMENSION%8 != 0){
        int last = DIMENSION%8;
        int byte = 0;
        for (int index = 0; index < last; index++){
          int ran = rand()%2;
          if (ran == 1)
            byte = (byte << 1) + 1;
          else
            byte = (byte << 1);
        }
        byte = byte << last;
        id[hv][DIMENSION/8] = byte;
      }
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
  char span_start_hv[DIMENSION];
  char span_end_hv[DIMENSION];
  //char** newLevel = new char*[num_vectors];
  //double span_hv[row][DIMENSION]; // 2 x DIMENSION

  for (int i = 0; i < DIMENSION; i++){
      span_start_hv[i] = char(rand()%2);
      span_end_hv[i] = char(rand()%2);
  }


  /* Generate random threshold */
  //double threshold_v[DIMENSION]; // ceil(span) x DIMENSION = 1 x DIMENSION

  float threshold_v[num_vectors];
  for (int i = 0; i < num_vectors; i++) {
    threshold_v[i] = float (i) / (num_vectors-1.0);
  }

    

  for (int i = 0; i < num_vectors; i++) {
    int span_idx = (int) float(float(i) / levels_per_span);
    //cout << "span_idx = " << i << " ";

    // NOTE: special case not included for now

    int level_within_span = i % levels_per_span;

    float t = 1 - (float(level_within_span) / float(levels_per_span)); // threshold value from start_hv perspective
    for (int j = 0; j < DIMENSION/8; j++){
        int byte = 0;
        for (int index = 0; index < num_vertcors; index++){
          int ran = (threshold_v[span_idx] < t) ? span_start_hv[j] : span_end_hv[j];
          if (ran == 1)
            byte = (byte << 1) + 1;
          else
            byte = (byte << 1);
        }
        level[i][j] = byte;
    }
    //the remining bit
    if (DIMENSION%8 != 0){
      int last = DIMENSION%8;
      int byte = 0;
      for (int index = 0; index < last; index++){
        int ran = (threshold_v[span_idx] < t) ? span_start_hv[DIMENSION/8] : span_end_hv[DIMENSION/8];
        if (ran == 1)
          byte = (byte << 1) + 1;
        else
          byte = (byte << 1);
      }
      byte = byte << last;
      level[i][DIMENSION/8] = byte;
    }
      
  }

}


void ID_Level_Encoder::bind(float* value) {
  int target[num_vectors];
  float threshold_v[num_vectors];
  float data[num_vectors];
  for (int i = 0; i < num_vectors; i++) {
    threshold_v[i] = float (i) / (num_vectors-1.0);
    data[i] = float(value[i]+1.0)/2.0;
  }
  for (int i = 0; i < num_vectors; i++) {
    //generate index for each value 
    //newHv[i] = new float[DIMENSION];
    int index = 0;
    while (data[i] < threshold_v[index] && index < num_vertcors-1){
      index++;
    }
      
    index = (threshold_v[index]-data[i] < data[i]-threshold_v[index-1]) ? index:index-1;
    target[i] = index;
  }

  
  for (int i = 0; i < num_vectors; i++){
    int index = target[i];
    for (int j = 0; j < DIMENSION/8; j++){
      int idByte = int(id[index][j]);
      int levelByte = int(level[index][j]);
      if (idByte < 0)
        idByte = idByte * -1;
      if (levelByte < 0)
        idByte = levelByte * -1;        
      int byte = idByte^levelByte^256;
      hv[i][j] = byte;
    }
    if (DIMENSION%8 != 0){
      int idByte = int(id[index][DIMENSION/8]);
      int levelByte = int(level[index][DIMENSION/8]);
      if (idByte < 0)
        idByte = idByte * -1;
      if (levelByte < 0)
        idByte = levelByte * -1;
      int last = 8 - DIMENSION%8;
      int byte = idByte^levelByte^256;
      byte = byte << last;
      /*      
      for (int bit = 0; bit < last; bit++){
        int check = 2^(last - bit);
        if ((idByte >= check)^(levelByte >= check))
          byte = (byte << 1) + 1;
        else
          byte = (byte << 1);
        idByte = idByte - check;
        levelByte = levelByte - check;
      }
      */
      hv[i][DIMENSION/8] = byte;
    }
  }
}



void ID_Level_Encoder::multiset() {
  int check = 1<<7;
  for (int i = 0; i < DIMENSION; i++) 
        sample_hv[i] = 0;
  for (int i = 0; i < DIMENSION/8; i++){
    for (int j = 0; j < num_vectors; j++){
      int byte = int(hv[j][i]);
      if (byte < 0)
        byte = byte * -1;
      for (int bit = 0; bit < 8; bit++){
        if (byte >= check)
          sample_hv[i*8+bit] += 1;
        else
          sample_hv[i*8+bit] -= 1;
        byte = byte << 1;
      }
    }
  }
  if (DIMENSION%8 != 0){
    int last = DIMENSION%8;
    for (int j = 0; j < num_vectors; j++){
      int byte = int(hv[j][DIMENSION/8]);
      if (byte < 0)
        byte = byte * -1;
      for (int bit = 0; bit < last; bit++){
        if (byte >= check)
          sample_hv[DIMENSION-last+bit] += 1;
        else
          sample_hv[DIMENSION-last+bit] -= 1;
        byte = byte << 1;
      }
    }    
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




void ID_Level_Encoder::ID_Level_Forward(float* x) {

  // TODO
  bind(x);
  multiset();
  hard_quantize();
}

int hamming_distance_similarity(int hv1[], int hv2[]) {


    int hamming_distance = 0;

    for (int i = 0; i < DIMENSION; i++) {
        if (hv1[i] != hv2[i]) {
            hamming_distance++;
        }
    }
    return hamming_distance;

}


void setup() {

  long int t1 = millis();


  
  Serial.begin(9600);
  srand(10);

  //frist sample
  ID_Level_Encoder* encoder = new ID_Level_Encoder(num_vertcors);
  encoder->ID_Level_Forward(a);
  int* first = encoder->sample_hv;
  int hv1[DIMENSION];
  Serial.print("first");
  for (int i = 0; i < DIMENSION; i++){
    hv1[i] = first[i];
    Serial.print(first[i]);
  }

  long int t2 = millis();
  Serial.print("Time taken by the task: "); 
  Serial.print(t2-t1); 
  Serial.println(" milliseconds");


  //second sample with the same encoder as the first one
  encoder->ID_Level_Forward(b);
  int* second = encoder->sample_hv;
  int hv2[DIMENSION];
  Serial.print("second");
  for (int i = 0; i < DIMENSION; i++){
    hv2[i] = second[i];
    Serial.print(second[i]);
  }

  //third sample, new encoder
  ID_Level_Encoder* another = new ID_Level_Encoder(num_vertcors);
  another->ID_Level_Forward(c);
  int* third = another->sample_hv;
  int hv3[DIMENSION];
  Serial.print("third");
  for (int i = 0; i < DIMENSION; i++){
    hv3[i] = third[i];
    Serial.print(third[i]);
  }

  int dis1 = hamming_distance_similarity(hv1, hv2);
  Serial.print(" distance between two data in a same class: ");
  Serial.print(dis1);
  int dis2 = hamming_distance_similarity(hv1, hv3);
  Serial.print(" distance between two data in a different class: ");
  Serial.print(dis2);
  int dis3 = hamming_distance_similarity(hv2, hv3);
  Serial.print(" distance between two data in a different class: ");
  Serial.print(dis3);
  


}


void loop() {
}
