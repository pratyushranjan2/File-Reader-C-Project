#ifndef CsvFileReader_h_
#define CsvFileReader_h_
#include<fstream>
#include<vector>
#include<string>
#include "base.h"
using namespace std;
class CsvFileReader: public base{
    private:
        string fileName;
        ifstream fin;
        string col1;
        string col2;
        vector< vector<string> > _table;
        int _cols;
        int _rows;
        int excelNumber(string s);
    public:
        CsvFileReader();
        CsvFileReader(string fileName,string column1,string column2);
        ~CsvFileReader();
        CsvFileReader(const CsvFileReader &csv);
        void storeData();
        void printData();
        vector< vector<string> > getTable();
        int getTotalRows();
        int getTotalColumns();
        void setTotalRows(int rows);
        void setTotalColumns(int cols);
    
    // Base class methods
    public:
    	void fileRead();
        void execute();
        void fileWrite();
        
};
#endif
