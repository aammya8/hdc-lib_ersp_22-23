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



void bind(float [] id, float [] value) {
  float hv[];
  for (int i = 0; i < id.size(); i++){
    if (id[i]*value[i] > 0)
      hv[i] = 1;
    else
      hv[i] = -1;
  }
  return hv;

}


void hard_quantize() {


}


void id_level_encoder(int num_classes, int size) {

}


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
