#ifndef RP_H
#define RP_H
#include <list>
#include <string>
#include <vector>
using namespace std;

class RP {
    public:
        /*
        * rp constructor
        */
        rp(unsigned int num_classes, unsigned int size) : lr, M, project{}

        //methods outside of the SingleModel class
        //unsigned int transform(unsigned int x);

        //unsigned int target_transform(unsigned int x);

        vector<int> encode(const vector<int> x);

        void model_update(const vector<int> x, const vector<int> y);

        vector<int> forward(const vector<int> x);

        //number of hypervector dimensions
        const int dimensions = 10000;

        //number of features in dataset
        const int num_features = 5;
};
#endif