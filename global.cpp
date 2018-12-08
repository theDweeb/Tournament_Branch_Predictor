#include "global.h"

// Initialization

// Variables
unsigned long int ght_g = 0;
unsigned long int pht_index_g = 0;
int threshold_g = 0;
string prediction_g = "";

// Data Structures
unordered_map<int, int> pht_g;
unordered_map<int, int>::iterator pht_itr_g;

// Functions
string global(string address, string direction, int nLSB, int nBitCounter) {

    // Find threshold between taken and not taken (half of 2^nBits)
    // 1 to threshold = not taken
    // threshold to 2^nBits = taken
    threshold_g = getCounterThreshold_g(nBitCounter);

    ght_g %= nLSB; // Keep the GHT at the specified bit size
    pht_index_g = ght_g; // XOR's the n-bit address with the n-bit ght

    pht_itr_g = pht_g.find(pht_index_g); // Checks to see if index has been accessed before
    if(pht_itr_g == pht_g.end()) pht_g[pht_index_g] = 1; // if not, set it to 1 (Strongly Not Taken)

    // ghare predicting [NOT TAKEN] based on the saturation counter
    if(pht_g[pht_index_g] <= threshold_g) {
        // set prediction for voter
        prediction_g = "N";

        // Actual direction was [TAKEN] -> Incorrect!
        if(direction == "T") {
            taken_g(ght_g, pht_g, pht_index_g, threshold_g);
        }
        // Actual direction was [NOT TAKEN] -> Correct!
        if(direction == "N") {
            notTaken_g(ght_g, pht_g, pht_index_g);
        }
    }

    // ghare predicting [TAKEN] based on the saturation counter
    else if(pht_g[pht_index_g] > threshold_g) {
        // set prediction for voter
        prediction_g = "T";

        // Actual direction was [TAKEN] -> Correct!
        if(direction == "T") {
            taken_g(ght_g, pht_g, pht_index_g, threshold_g);
        }
        // Actual direction was [NOT TAKEN] -> inCorrect!
        if(direction == "N") {
            notTaken_g(ght_g, pht_g, pht_index_g);
        }
    }
    
    return prediction_g;
}

// Functions
void taken_g(unsigned long int &ght, unordered_map<int,int> &pht, unsigned long int index, int max) {
    // "Shift" in a 1
    ght = (2*ght) + 1;

    // Update pht
    int value = pht[index];
    value++;
    max *= 2; // get max counter value
    if(value > max) value = max;
    pht[index] = value;

}

void notTaken_g(unsigned long int &ght, unordered_map<int,int> &pht, unsigned long int index) {
    // "Shift" in a 0
    ght *= 2;

    // Update pht
    int value = pht[index];
    value--;
    if(value < 1) value = 1;
    pht[index] = value;

}

int getCounterThreshold_g(int nBits) {
    int temp = pow(2, nBits);
    temp /= 2;
    return temp;
}