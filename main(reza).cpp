#include <iostream>
#include <fstream>
#include <sstream>
#include "main.h"
#include "gshare.h"
#include "tll.h"
#include "bimodal.h"
#include "GSelect.h"
#include "global.h"

// Globals
int nLSB = 0;
int nBitCounter = 0;
double bimodalMiss, globalMiss, GSelectMiss, GShareMiss, tllMiss, totalMiss = 0;
double total = 0;
double bimodalMissRate, globalMissRate, GSelectMissRate, GShareMissRate, tllMissRate, totalMissRate = 0;
double bimodalAccuracy, globalAccuracy, GSelectAccuracy, GShareAccuracy, tllAccuracy, totalAccuracy = 0;
int GShare_Outcome = 0;
int TLL_Outcome = 0;
int voteCount = 4;
string vote = "";


int main() {
    string c1, inDirection, c3, c4, c5, c6, c7, inAddress, c9, c10, c11, c12, c13, c14 = ""; // holds input from trace file
    string gsharePrediction, gselectPrediction, tllPrediction, bimodalPrediction, globalPrediction, voter = "";

    // Configure simulator parameters
    getnLSB(nLSB);
    getCounter(nBitCounter);
    unsigned long int newAddr;
    
    // Parse trace file
    ifstream trace;
    trace.open("fft.out");
    if(trace.is_open()) {
        cout << "\nTrace file opened successfully!\n\n";
        while(!trace.eof()) {
            trace >> c1 >> inDirection >> c3 >> c4 >> c5 >> c6 >> c7 >> inAddress >> c9;
                    if(c9 == "#BASE") trace.ignore(1000, '\n');
                    if(inDirection == "1") inDirection = "T";
                    else if(inDirection == "0") inDirection = "N";
                   
                    inAddress.erase(inAddress.begin(), inAddress.begin()+2);
                  
                    istringstream iss(inAddress);
                    iss >> hex >> newAddr;
                    
                    stringstream ss;
                    ss << newAddr;
                    inAddress = ss.str();
            
                    // increment number of branches predicted
                    total++;

                    // Find Bimodal prediction for current address
                    bimodalPrediction = bimodal(inAddress, inDirection, nLSB, nBitCounter);

                    // Find Global prediction for current address
                    globalPrediction = global(inAddress, inDirection, nLSB, nBitCounter);

                    // Find GSelect prediction for current address
                    gselectPrediction = gselect(inAddress, inDirection, nLSB, nBitCounter);
                    
                    // Find GShare's prediction for current address
                    gsharePrediction = gshare(inAddress, inDirection, nLSB, nBitCounter);
                    
                    // Find Two-Level Local's prediction for current address
                    tllPrediction = tll(inAddress, inDirection, nLSB, nBitCounter);

                    // Find each predictor's accuracy
                    //Bimodal
                    if(bimodalPrediction != inDirection) bimodalMiss++;
                    

                    if(globalPrediction != inDirection) globalMiss++;

                    if(gselectPrediction != inDirection) GSelectMiss++;


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
    bimodalMissRate = (bimodalMiss / total) * 100;
    globalMissRate = (globalMiss / total) * 100;
    GSelectMissRate = (GSelectMiss / total) * 100;
    GShareMissRate = (GShareMiss / total) * 100;
    tllMissRate = (tllMiss / total) * 100;
    totalMissRate = (totalMiss / total) * 100;

    cout << "Total Branch Predictions: " << total << endl;
    cout << "\nBimodal miss rate: " << bimodalMissRate << " (Accuracy: " << (100-bimodalMissRate) << ")\n";
    cout << "Global miss rate: " << globalMissRate << " (Accuracy: " << (100-globalMissRate) << ")\n";   
    cout << "GSelect miss rate: " << GSelectMissRate << " (Accuracy: " << (100-GSelectMissRate) << ")\n";   
    cout << "GShare miss rate: " << GShareMissRate << " (Accuracy: " << (100-GShareMissRate) << ")\n";
    cout << "TLL miss rate: " << tllMissRate << " (Accuracy: " << (100-tllMissRate) << ")\n";
    cout << "Tournament (GShare + TLL) miss rate: " << totalMissRate << " (Accuracy: " << (100-totalMissRate) << ")\n\n";

    return 0;
}

// Function Declarations
void getnLSB(int &nLSB) {
    int size = 0;
    //cout << "Enter in pattern history table index size(i.e. 1024): ";
    cin >> size;
    nLSB = size;
}

void getCounter(int &nCounter) {
    int size = 0;
    //cout << "Enter in the BIT size for the saturation counter(i.e. 2): ";
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