//gshare.h
#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <string>
#include <unordered_map>
#include <math.h>

using namespace std;

// Functions
string global(string address, string direction, int nLSB, int nBitCounter);
void taken_g(unsigned long int &ght, unordered_map<int,int> &pht, unsigned long int index, int max);
void notTaken_g(unsigned long int &ght, unordered_map<int,int> &pht, unsigned long int index);
int getCounterThreshold_g(int nBits);


#endif