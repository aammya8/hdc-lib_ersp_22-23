/*
ID-Level Encoding
*/

#define DIMENSIONS 10000
#define NUM_LEVELS 100


struct ID_Level_Encoder {

  float id[];
  float value[];

  ID_Level_Encoder() {
    id = 
  }





}



void bind(float [] weight, float [] value) {
  float hv[];
  for (int i = 0; i < weight.size(); i++){
    if (weight[i]*value[i] > 0)
      hv[i] = 1;
    else
      hv[i] = -1;
  }
  return hv;
}

void multiset(float [] sample) {
  float hv[];
  float total;
  for (int i = 0; i < sample[0].size(); i++){
    for (int j = 0; j < sample[0].size(); i++)
      total += sample[i][j];
    hv[i] = total;
  }
  return hv;
}

void hard_quantize(float [] sample){
  float hv[];
  for (int i = 0; i < sample.size(); i++){
    if (sample[i] > 0)
      hv[i] = 1;
    else
      hv[i] = -1;
  }
  return hv;
}


void id_level_encoder(int num_classes, int size) {

}


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
