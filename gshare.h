//gshare.h
#ifndef _GSHARE_H
#define _GSHARE_H

#include <string>
#include <unordered_map>
#include <math.h>

using namespace std;

// Functions
string gshare(string address, string direction, int nLSB, int nBitCounter);
void taken(unsigned long int &ght, unordered_map<int,int> &pht, unsigned long int index, int max);
void notTaken(unsigned long int &ght, unordered_map<int,int> &pht, unsigned long int index);
int getCounterThreshold_gs(int nBits);


#endif