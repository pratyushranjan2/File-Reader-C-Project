#ifndef UCINET_DL_READER_H_
#define UCINET_DL_READER_H_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<algorithm>
#include <map>
#include "StringUtility.h"
#include "Node.h"
#include "NodeComparator.h"
#include "base.h"
using namespace std;

class UCINET_DL_READER: public base {
    private:
        string fileName;
        int n; // number of nodes
        vector<string> labels;
        vector<Node> nodes;
    
    public:
        UCINET_DL_READER(string _fileName);
        UCINET_DL_READER(const UCINET_DL_READER &udr);
        ~UCINET_DL_READER();
    
    public:
        void generateOutputFile();
        void testing();

    private:
        void readAndStoreData();
        void storeLabels(vector<string> rawData);
        void initializeNodes();
        void reIndexNodes();
        void filterNodes(int threshold_index);
        void writeback();

    // Base class methods
    public:
        void fileRead();
        void execute();
        void fileWrite();
};

#endif