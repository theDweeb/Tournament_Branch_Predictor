#include "gshare.h"

// Initialization

// Variables
unsigned long int nLSB_Address_gs = 0;
unsigned long int ght_gs = 0;
unsigned long int pht_index_gs = 0;
int threshold_gs = 0;
string prediction_gs = "";

// Data Structures
unordered_map<int, int> pht_gs;
unordered_map<int, int>::iterator pht_itr_gs;

// Functions
string gshare(string address, string direction, int nLSB, int nBitCounter) {

    // Find threshold between taken and not taken (half of 2^nBits)
    // 1 to threshold = not taken
    // threshold to 2^nBits = taken
    threshold_gs = getCounterThreshold_gs(nBitCounter);

    ght_gs %= nLSB; // Keep the GHT at the specified bit size
    nLSB_Address_gs = stol(address) % nLSB; // Takes the n-LSB of address
    pht_index_gs = nLSB_Address_gs ^ ght_gs; // XOR's the n-bit address with the n-bit ght

    pht_itr_gs = pht_gs.find(pht_index_gs); // Checks to see if index has been accessed before
    if(pht_itr_gs == pht_gs.end()) pht_gs[pht_index_gs] = 1; // if not, set it to 1 (Strongly Not Taken)

    // GShare predicting [NOT TAKEN] based on the saturation counter
    if(pht_gs[pht_index_gs] <= threshold_gs) {
        // set prediction for voter
        prediction_gs = "N";

        // Actual direction was [TAKEN] -> Incorrect!
        if(direction == "T") {
            taken(ght_gs, pht_gs, pht_index_gs, threshold_gs);
        }
        // Actual direction was [NOT TAKEN] -> Correct!
        if(direction == "N") {
            notTaken(ght_gs, pht_gs, pht_index_gs);
        }
    }

    // GShare predicting [TAKEN] based on the saturation counter
    else if(pht_gs[pht_index_gs] > threshold_gs) {
        // set prediction for voter
        prediction_gs = "T";

        // Actual direction was [TAKEN] -> Correct!
        if(direction == "T") {
            taken(ght_gs, pht_gs, pht_index_gs, threshold_gs);
        }
        // Actual direction was [NOT TAKEN] -> inCorrect!
        if(direction == "N") {
            notTaken(ght_gs, pht_gs, pht_index_gs);
        }
    }
    
    return prediction_gs;
}

// Functions
void taken(unsigned long int &ght, unordered_map<int,int> &pht, unsigned long int index, int max) {
    // "Shift" in a 1
    ght = (2*ght) + 1;

    // Update pht
    int value = pht[index];
    value++;
    max *= 2; // get max counter value
    if(value > max) value = max;
    pht[index] = value;

}

void notTaken(unsigned long int &ght, unordered_map<int,int> &pht, unsigned long int index) {
    // "Shift" in a 0
    ght *= 2;

    // Update pht
    int value = pht[index];
    value--;
    if(value < 1) value = 1;
    pht[index] = value;

}

int getCounterThreshold_gs(int nBits) {
    int temp = pow(2, nBits);
    temp /= 2;
    return temp;
}