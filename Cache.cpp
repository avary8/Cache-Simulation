#include "Cache.h"

void Cache::initParams(int lineSize, int cacheSize, int linesPerSet, bool fifoReplace) {
    resetVals();
    this->fifoReplace = fifoReplace;
    this->lineSize = lineSize;
    this->cacheSize = cacheSize;
    this->linesPerSet = linesPerSet;
    numLines = cacheSize / lineSize;
    numSets = numLines/linesPerSet;

    offsetWidth = log2(lineSize);  
    lineWidth = 0;
    if (linesPerSet != numLines){
        lineWidth = log2(numSets);
    }
    tagWidth = 32 - offsetWidth - lineWidth;
    
    readFile();
    hitRate = float(hits)/float(total);
    //cout << "hits: " << hits << " total: " << total << "\n";
}

void Cache::readFile() {
    string fileLine, var;
    ifstream file("gcc.trace");
    int i = 1;
    while (getline(file, fileLine)) {//gets line by line
        istringstream iss(fileLine);//gets values by space delimiter
        //cout << '\n' << fileLine << "\n   ";
        iss >> var; //this is the store vs load variable
        iss >> var; //this is the address variable
        //don't need the number of bytes variable

        //cout << var;

        var = hexToBinary(var);    
        string tag = var.substr(0, tagWidth); // this is tag number

        //cout << "::" << var << "\n      ";
        //cout << "tag num : " << tag << "\n      ";

        string line = "0";
        if (lineWidth != 0){//if not associative
            line = var.substr(tagWidth, lineWidth);// this is line number
            //cout << "line number: " << line << "\n      ";
        }
        //convert tag and line to decimal
        int tagDec = stoi(tag, 0, 2);
        int lineDec = stoi(line, 0, 2);
        //cout << "tagDec: " << tagDec << "\n      ";
        //cout << "lineDec: " << lineDec << "\n       ";

        search(tagDec, lineDec);//search in cache
        //cout << "hits: " <<hits << " total: " << total << "\n\n";
    }
    //cout << '\n';

    file.close();
}

void Cache::search(int& tag, int& line){
    total += 1;
    if (cacheMem.size() == 0){
        shared_ptr<Line> newLine (new Line);
        newLine->line = line;
        newLine->tag = tag;
        newLine->counter = total;
        if (linesPerSet == numLines){//fully assoc
            cacheMem.push_back(newLine);//add to cache
        } else {//direct or n-way set 
            shared_ptr<Line> temp (new Line);
            for (int i = 0; i < numLines; i++){
		        cacheMem.push_back(temp);
	        }
            cacheMem.at(line*linesPerSet) = newLine;
        }
    }
    else {//search for tag in cache
        bool found = 0;
        int startIndex = line * linesPerSet;
        //cout << "startIndex : " << startIndex << " line: " << line << " linesPerSet: " << linesPerSet << "\n";
        for (int i = 0; i < linesPerSet; i++){
            /*startIndex and i allow this one loop to search regardless of associativity
                linesPerSet :: FA = numOfLines = vector size
                    DM = 1 (only one possible place)
                    N-Way Set = n lines per m sets. (if 2-way, there are 2 lines that a particular set can hold)
            */
            if (cacheMem.size() > startIndex + i){
                if ((cacheMem.at(startIndex + i)->counter != -1) && (cacheMem.at(startIndex + i)->tag == tag)){
                    if (fifoReplace == 0){//if LRU, update counter
                        cacheMem.at(startIndex + i)->counter = total;
                    }
                    hits += 1;
                    found = 1;
                    break;
                }
            }
            else {
                break;
            }
        }
        if (found == 0){//not found. replace
            replace(tag, line);
        }
    } 
}

void Cache::replace(int& tag, int& line){
    shared_ptr<Line> newLine (new Line);
    newLine->line = line;
    newLine->tag = tag;
    newLine->counter = total;
    if (linesPerSet == numLines && cacheMem.size() != numLines){//fully associative and cache not full yet
        cacheMem.push_back(newLine); 
    } else if (linesPerSet == 1) {//direct mapped
        cacheMem.at(line) = newLine;
    }
    else {
        int startIndex = line * linesPerSet;
        int replaceIndex = startIndex; 
        int smallestCounter = cacheMem.at(startIndex)->counter; 

        for (int i = 0; i < linesPerSet; i++){
            if (cacheMem.size() > startIndex + i){
                if (cacheMem.at(startIndex + i)->counter < smallestCounter){
                    smallestCounter = cacheMem.at(startIndex + i)->counter;
                    replaceIndex = startIndex + i; 
                    if (fifoReplace == 0){//if LRU, update counter
                        cacheMem.at(startIndex + i)->counter = total;
                    }
                }
            }
        }
        cacheMem.at(replaceIndex) = newLine;
    }
}


string Cache::hexToBinary(string& hex){
    string binary;
    char hexValue[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    int n = sizeof(hexValue) / sizeof(hexValue[0]);

    for (int i = 2; i < hex.length(); i++){
        char c = hex.at(i);
        //cout << i << ": " << c ;
        c = toupper(c);
        auto dec = find(hexValue, hexValue + n, c) - hexValue;
        //cout << " dec val: " << dec;
        string temp = bitset<4>(dec).to_string();
        //cout << " bin val: " << temp << "\n";
        binary.append(temp);
    }
    return binary;
}

void Cache::resetVals(){
    hitRate = 0;
    hits = 0;
    total = 0;
    lineSize = 0;
    cacheSize = 0;
    numLines = 0; // cache size / line size
    numSets = 0; // # lines / lines per set 
    linesPerSet = 0; //by associativity
    offsetWidth = 0;
    lineWidth = 0;
    tagWidth = 0;
    fifoReplace = 1; 
    cacheMem.clear();
}


// bool Cache::compareByLine(const Address &a, const Address &b){
//     return a.line < b.line;
// }