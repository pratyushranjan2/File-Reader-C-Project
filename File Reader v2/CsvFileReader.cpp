#include<iostream>
#include "include/CsvFileReader.h"
#include<sstream>
#include<algorithm>

int column1,column2;
//Default constructor
CsvFileReader::CsvFileReader(){

}
//Construvtor with inputs
CsvFileReader::CsvFileReader(string _fileName,string _col1,string _col2): fileName(_fileName), col1(_col1), col2(_col2)
{
    // ifstream fin;
    fin.open(fileName);
    column1 = excelNumber(col1);
    column2 = excelNumber(col2);
    //fileRead(fin);
}

//Copy constructor
CsvFileReader::CsvFileReader(const CsvFileReader &csv){
    _table = csv._table;
    _cols = csv._cols;
    _rows = csv._rows;
}

//Destructor
CsvFileReader::~CsvFileReader(){
}

//Function to read file and create table
void CsvFileReader::fileRead(){
    string line,word;
    int check = 0;
    while(fin.good())
    {
        int count = 0;
        getline(fin,line);
        if(line != "")
        {
            std::stringstream iss(line);
            vector<string> row;
            while(getline(iss,word,','))
            {
                row.push_back(word);
                count++;
            }
             _cols = count;
            _table.push_back(row);
            check++;
        }
    }
    setTotalRows(check);
}

//Private function to return the value for given excel column(A = 0,B = 1.....AA = 26...)
int CsvFileReader::excelNumber(string s) {
    int number = 0;
        for (const auto& c : s) {
            number *= 26;
            number += c  - 'A';
        }
        return number;
}

//Getter for total number of rows
int CsvFileReader::getTotalRows(){
    return _rows;
}

//Getter for total number of columns
int CsvFileReader::getTotalColumns(){
    return _cols;
}

//Setter for total number of rows
void CsvFileReader::setTotalRows(int rows)
{
    _rows = rows;
}

//Setter for total number of columns
void CsvFileReader::setTotalColumns(int cols)
{
    _cols = cols;
}

//Comparator function for sorting based on 2 indices
bool sortByFields(vector<string> v1, vector<string> v2)
{
    
    if(v1[column1] != v2[column1])
    {

        return v1[column1] < v2[column1];
    }

    return v1[column2] < v2[column2];
}

//Execute function which calls sort function
void CsvFileReader::execute(){
    if(column1 > this->getTotalColumns() -1 || column2 > this->getTotalColumns()-1)
    {
        std::cout << "Column index out of bounds, please check your column indices";
        exit(0);
    }
    sort(_table.begin() + 1,_table.end(),sortByFields);
}



//Function to print data in the table
void CsvFileReader::printData()
{
    vector< vector<string> > table = this->getTable();
    for(int i = 0;i< table.size();i++)
    {
        for(int j = 0;j<table.at(i).size();j++)
        {
            cout << table.at(i).at(j)<<',';
        }
        cout << endl;
    }
}

//Getter to return the table
vector< vector<string> > CsvFileReader::getTable(){
    return _table;
}

//Function to write the table into the file
void CsvFileReader::fileWrite()
{
    ofstream fout;
    fout.open("./output_files/task_8.csv",ios::out);
    vector< vector<string> > tableUpdated = this->getTable();
    for(int i = 0;i< tableUpdated.size();i++)
    {
        for(int j = 0;j<tableUpdated.at(0).size();j++)
        {
            fout << tableUpdated.at(i).at(j);
            if(j != tableUpdated.at(i).size() - 1)
                fout << ',';
        }
        fout << endl;
    }
}
