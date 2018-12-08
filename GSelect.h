//gshare.h
#ifndef _GSELECT_H
#define _GSELECT_H

#include <string>
#include <unordered_map>
#include <math.h>

using namespace std;

// Functions
string gselect(string address, string direction, int nLSB, int nBitCounter);
void taken_s(unsigned long int &ght, unordered_map<int,int> &pht, unsigned long int index, int max);
void notTaken_s(unsigned long int &ght, unordered_map<int,int> &pht, unsigned long int index);
int getCounterThreshold_s(int nBits);


#endif