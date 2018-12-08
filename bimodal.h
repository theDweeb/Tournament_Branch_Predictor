#ifndef _BIMODAL_H
#define _BIMODAL_H

#include <string>
#include <unordered_map>
#include "math.h"
#include <iostream>

using namespace std;

//Functions
string bimodal(string address, string direction, int nLSB, int nBitCounter);
int getCounterThreshold_bm(int nBitCounter);
void taken(unordered_map<int,int> &pht, unsigned long int index, int max);
void notTaken(unordered_map<int, int> &pht, unsigned long int index);

#endif