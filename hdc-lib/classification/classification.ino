#include "classification.h"


int Classification::hamming_distance_similarity(float hv1[], float hv2[]) {

    int hv1_size = sizeof(hv1) / sizeof(int);
    int hv2_size = sizeof(hv2) / sizeof(int);

    int hamming_distance = 0;

    int num_comparisons = (hv1_size > hv2_size) ? hv2_size : hv1_size;
    for (int i = 0; i < num_comparisons; i++) {
        if (hv1[i] != hv2[i]) {
            hamming_distance++;
        }
    }
    return hamming_distance;
}