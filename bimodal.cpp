#include "bimodal.h"

unsigned long int pht_index_bm = 0;
int threshold_bm = 0;
string prediction_bm = "";

unordered_map<int, int> pht_bm;
unordered_map<int, int>::iterator pht_itr_bm;

string bimodal(string address, string direction, int nLSB, int nBitCounter) {

    threshold_bm = getCounterThreshold_bm(nBitCounter);

    pht_index_bm = stol(address) % nLSB; // Takes the n-LSB of address

    pht_itr_bm = pht_bm.find(pht_index_bm);
    if(pht_itr_bm == pht_bm.end()) pht_bm[pht_index_bm] = 1;

    if(pht_bm[pht_index_bm] <= threshold_bm) {
        // set prediction for voter
        prediction_bm = "N";

        // Actual direction was [TAKEN] -> Incorrect!
        if(direction == "T") {
            taken(pht_bm, pht_index_bm, threshold_bm);
        }
        // Actual direction was [NOT TAKEN] -> Correct!
        if(direction == "N") {
            notTaken(pht_bm, pht_index_bm);
        }
    }

    // GShare predicting [TAKEN] based on the saturation counter
    else if(pht_bm[pht_index_bm] > threshold_bm) {
        // set prediction for voter
        prediction_bm = "T";

        // Actual direction was [TAKEN] -> Correct!
        if(direction == "T") {
            taken(pht_bm, pht_index_bm, threshold_bm);
        }
        // Actual direction was [NOT TAKEN] -> inCorrect!
        if(direction == "N") {
            notTaken(pht_bm, pht_index_bm);
        }
    }

    return prediction_bm;
}


// Functions
void taken(unordered_map<int,int> &pht, unsigned long int index, int max) {
    
    // Update pht
    int value = pht[index];
    value++;
    max *= 2; // get max counter value
    if(value > max) value = max;
    pht[index] = value;

}

void notTaken(unordered_map<int,int> &pht, unsigned long int index) {

    // Update pht
    int value = pht[index];
    value--;
    if(value < 1) value = 1;
    pht[index] = value;

}

int getCounterThreshold_bm(int nBits) {
    int temp = pow(2, nBits);
    temp /= 2;
    return temp;
}