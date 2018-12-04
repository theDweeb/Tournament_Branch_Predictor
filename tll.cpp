#include "tll.h"

// Initialization

// Variables
unsigned long int nLSB_Address = 0;
unsigned long int pht_index = 0;
int threshold = 0;
string prediction = "";

// Data Structures
unordered_map<int,int> lht, pht;
unordered_map<int, int>::iterator pht_itr, lht_itr;

// Functions
string tll(string address, string direction, int nLSB, int nBitCounter) {
    
    // Find threshold between taken and not taken
    // 1 to threshold = not taken
    // threshold to 2^nBits = taken
    threshold = getCounterThreshold(nBitCounter);

    
    nLSB_Address = stol(address) % nLSB; // Takes n-LSB from address

    // Setup LHT
    lht_itr = lht.find(nLSB_Address);
    if(lht_itr == lht.end()) lht[nLSB_Address] = 0;
    lht[nLSB_Address] %= nLSB;

    // Setup PHT
    pht_index = lht[nLSB_Address];
    pht_itr = pht.find(pht_index);
    if(pht_itr == pht.end()) pht[pht_index] = 1;

    // TLL predicting [NOT TAKEN] based on the saturation counter
    if(pht[pht_index] <= threshold) {
        // set prediction for voter
        prediction = "N";

        // Actual direction was [TAKEN] -> Incorrect!
        if(direction == "T") {
            taken(lht, nLSB_Address, pht, pht_index, threshold);
        }
        // Actual direction was [NOT TAKEN] -> Correct!
        if(direction == "N") {
            notTaken(lht, nLSB_Address, pht, pht_index);
        }
    }

    // TLL predicting [TAKEN] based on the saturation counter
    else if(pht[pht_index] > threshold) {
        // set prediction for voter
        prediction = "T";

        // Actual direction was [TAKEN] -> Correct!
        if(direction == "T") {
            taken(lht, nLSB_Address, pht, pht_index, threshold);
        }
        // Actual direction was [NOT TAKEN] -> inCorrect!
        if(direction == "N") {
            notTaken(lht, nLSB_Address, pht, pht_index);
        }
    }
    
    return prediction;




}

// Functions
void taken(unordered_map<int, int> &lht, unsigned long int lht_index, unordered_map<int,int> &pht, unsigned long int pht_index, int max) {
    // "Shift" in a 1
    lht[lht_index] = (2*lht[lht_index]) + 1;

    // Update pht
    int value = pht[pht_index];
    value++;
    threshold *= 2; // get max counter value
    if(value > threshold) value = threshold;
    pht[pht_index] = value;

}

void notTaken(unordered_map<int, int> &lht, unsigned long int lht_index, unordered_map<int,int> &pht, unsigned long int pht_index) {
    // "Shift" in a 0
    lht[lht_index] = (2*lht[lht_index]);

    // Update pht
    int value = pht[pht_index];
    value--;
    if(value < 1) value = 1;
    pht[pht_index] = value;

}

int getCounterThreshold(int nBits) {
    int temp = pow(2, nBits);
    temp /= 2;
    return temp;
}