#ifndef _MAIN_H
#define _MAIN_H

#include <string>

using namespace std;

// Function Prototypes
void getnLSB(int &nLSB);
void getCounter(int &nCounter);
string pick_predictor(string gs, string tll, int voteCount);
void update_voter(int gs, int tll, int &voteCount);



#endif