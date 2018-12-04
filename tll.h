//tll.h
#ifndef _TLL_H  
#define _TLL_H

#include <string>
#include <unordered_map>
#include "math.h"
using namespace std;

// Functions
string tll(string address, string direction, int nLSB, int nBitCounter);
void taken(unordered_map<int, int> &lht, unsigned long int lht_index, unordered_map<int,int> &pht, unsigned long int pht_index, int max);
void notTaken(unordered_map<int, int> &lht, unsigned long int lht_index, unordered_map<int,int> &pht, unsigned long int pht_index);
int getCounterThreshold(int nBits);


#endif