#pragma once
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <bitset>
#include <memory>
#include<cmath>
#include <cctype>
#include <stdlib.h>
using namespace::std;

struct Line {//represents line in a cache
    int line, tag; //line or set depending on associativity
    int counter = -1;
};

class Cache {
public:
    void initParams(int lineSize, int cacheSize, int linesPerSet, bool fifoReplace);
    float hitRate = 0;

private:
    void resetVals();
    void readFile();
    string hexToBinary(string& hex);
    void search(int& tag, int& line);
    void replace(int& tag, int& line);
    //bool compareByLine(const Address &a, const Address &b); //not used 
    int hits = 0;
    int total = 0;
    int lineSize = 0;
    int cacheSize = 0;
    int numLines = 0; // cache size / line size
    int numSets = 0; // # lines / lines per set 
    int linesPerSet = 0; //by associativity
    int offsetWidth = 0;
    int lineWidth = 0;
    int tagWidth = 0;
    bool fifoReplace = 1; 

    vector<shared_ptr<Line>> cacheMem;//represents cache memory 
};