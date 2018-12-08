#include "GSelect.h"

// Initialization

// Variables
unsigned long int nLSB_Address_s = 0;
unsigned long int ght_s = 0;
unsigned long int pht_index_s = 0;
int threshold_s = 0;
string prediction_s = "";

// Data Structures
unordered_map<int, int> pht_s;
unordered_map<int, int>::iterator pht_itr_s;

// Functions
string gselect(string address, string direction, int nLSB, int nBitCounter) {

    // Find threshold between taken and not taken (half of 2^nBits)
    // 1 to threshold = not taken
    // threshold to 2^nBits = taken
    threshold_s = getCounterThreshold_s(nBitCounter);

    ght_s %= nLSB;
    ght_s /= 2; // Keep the GHT at the specified bit size
    nLSB_Address_s = stol(address) % nLSB; // Takes the n-LSB of address
    nLSB_Address_s /= 2;
    pht_index_s = nLSB_Address_s + ght_s; // XOR's the n-bit address with the n-bit ght

    pht_itr_s = pht_s.find(pht_index_s); // Checks to see if index has been accessed before
    if(pht_itr_s == pht_s.end()) pht_s[pht_index_s] = 1; // if not, set it to 1 (Strongly Not Taken)

    // GShare predicting [NOT TAKEN] based on the saturation counter
    if(pht_s[pht_index_s] <= threshold_s) {
        // set prediction for voter
        prediction_s = "N";

        // Actual direction was [TAKEN] -> Incorrect!
        if(direction == "T") {
            taken_s(ght_s, pht_s, pht_index_s, threshold_s);
        }
        // Actual direction was [NOT TAKEN] -> Correct!
        if(direction == "N") {
            notTaken_s(ght_s, pht_s, pht_index_s);
        }
    }

    // GShare predicting [TAKEN] based on the saturation counter
    else if(pht_s[pht_index_s] > threshold_s) {
        // set prediction for voter
        prediction_s = "T";

        // Actual direction was [TAKEN] -> Correct!
        if(direction == "T") {
            taken_s(ght_s, pht_s, pht_index_s, threshold_s);
        }
        // Actual direction was [NOT TAKEN] -> inCorrect!
        if(direction == "N") {
            notTaken_s(ght_s, pht_s, pht_index_s);
        }
    }
    
    return prediction_s;
}

// Functions
void taken_s(unsigned long int &ght, unordered_map<int,int> &pht, unsigned long int index, int max) {
    // "Shift" in a 1
    ght = (2*ght) + 1;

    // Update pht
    int value = pht[index];
    value++;
    max *= 2; // get max counter value
    if(value > max) value = max;
    pht[index] = value;

}

void notTaken_s(unsigned long int &ght, unordered_map<int,int> &pht, unsigned long int index) {
    // "Shift" in a 0
    ght *= 2;

    // Update pht
    int value = pht[index];
    value--;
    if(value < 1) value = 1;
    pht[index] = value;

}

int getCounterThreshold_s(int nBits) {
    int temp = pow(2, nBits);
    temp /= 2;
    return temp;
}