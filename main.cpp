#include <iostream>
#include <fstream>
#include "gshare.h"
#include "tll.h"

// Globals
int nLSB = 0;
int nBitCounter = 0;
double GShareMiss, tllMiss, totalMiss = 0;
double total = 0;
double GShareMissRate, tllMissRate, totalMissRate = 0;
double GShareAccuracy, tllAccuracy, totalAccuracy = 0;
int GShare_Outcome = 0;
int TLL_Outcome = 0;
int voteCount = 4;
string vote = "";

// Function Prototypes
void getnLSB(int &nLSB);
void getCounter(int &nCounter);
string pick_predictor(string gs, string tll, int voteCount);
void update_voter(int gs, int tll, int &voteCount);

int main() {
    string inAddress, inDirection = ""; // holds input from trace file
    string gsharePrediction, tllPrediction, voter = "";

    // Configure simulator parameters
    getnLSB(nLSB);
    getCounter(nBitCounter);

    
    // Parse trace file
    ifstream trace;
    trace.open("trace.trace");
    if(trace.is_open()) {
        cout << "\nTrace file opened successfully!\n\n";
        while(!trace.eof()) {
            trace >> inAddress >> inDirection;

            // increment number of branches predicted
            total++;

            // Find GShare's prediction for current address
            gsharePrediction = gshare(inAddress, inDirection, nLSB, nBitCounter);
            
            // Find Two-Level Local's prediction for current address
            tllPrediction = tll(inAddress, inDirection, nLSB, nBitCounter);

            // Find each predictor's accuracy
            if(gsharePrediction != inDirection) { 
                GShareMiss++;
                GShare_Outcome = 0;
            }
            else {
                GShare_Outcome = 1;
            }
            if(tllPrediction != inDirection) {
                tllMiss++;
                TLL_Outcome = 0;
            }
            else {
                TLL_Outcome = 1;
            }
            // Voter will choose which prediction to use
            vote = pick_predictor(gsharePrediction, tllPrediction, voteCount);
            if(vote != inDirection) totalMiss++;

            update_voter(GShare_Outcome, TLL_Outcome, voteCount);
        }
    }

    // calculate miss rates and accuracy
    GShareMissRate = (GShareMiss / total) * 100;
    tllMissRate = (tllMiss / total) * 100;
    totalMissRate = (totalMiss / total) * 100;

    cout << "GShare miss rate: " << GShareMissRate << " (Accuracy: " << (100-GShareMissRate) << ")\n";
    cout << "TLL miss rate: " << tllMissRate << " (Accuracy: " << (100-tllMissRate) << ")\n";
    cout << "Tournament miss rate: " << totalMissRate << " (Accuracy: " << (100-totalMissRate) << ")\n\n";

    return 0;
}

// Function Declarations
void getnLSB(int &nLSB) {
    int size = 0;
    cout << "Enter in pattern history table index size(ex. 1024): ";
    cin >> size;
    nLSB = size;
}

void getCounter(int &nCounter) {
    int size = 0;
    cout << "Enter in saturation counter size (int bits ex. 2): ";
    cin >> size;
    nCounter = size;
}

string pick_predictor(string gs, string tll, int voteCount) {
    string choice = "";

    if(voteCount <= 2) choice = gs;
    else if(voteCount > 2) choice = tll;

    return choice;
}

void update_voter(int gs, int tll, int &voteCount) {
        if(gs == 0 && tll == 1){
        voteCount++;
    }
    else if(gs == 1 && tll == 0){
        voteCount--;
    }

    if(voteCount > 4) voteCount = 4;
    if(voteCount < 1) voteCount = 1;
}