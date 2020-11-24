#include "include/CSV.h"
#include <fstream>
#include <iostream>
#include <sstream> // std::stringstream

using namespace std;

//Constructor
CSV::CSV(string name,int height,int width): base(){
    fileName = name;
    rows = height;
    columns = width;
    //Memory allocation to matrices
    matrix = new string*[rows];
    transMatrix = new string*[columns];
    for(int i=0;i<rows;i++){
        matrix[i] = new string[columns];
    }
    for(int i=0;i<columns;i++){
        transMatrix[i] = new string[rows];
    }
    //Initialize the matrix to empty strings
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            matrix[i][j] = "";
        }
    }
    for(int i=0;i<columns;i++){
        for(int j=0;j<rows;j++){
            transMatrix[i][j] = "";
        }
    }
}

//Destructor
CSV::~CSV(){
    delete []matrix;
    delete []transMatrix;
}

//Copy-Constructor
CSV::CSV(const CSV &F){
    fileName = F.fileName;
    rows = F.rows;
    columns = F.columns;
    matrix = F.matrix;
}

//Setters
void CSV::setColumns(int width){
    columns = width;
}
void CSV::setRows(int height){
    rows = height;
}
void CSV::setFilename(string name){
    fileName = name;
}
void CSV::setMatrix(string **m){
    matrix = m;
}
//Getters
int CSV::getColumns(){
    return columns;
}
int CSV::getRows(){
    return rows;
}
string CSV::getFileName(){
    return fileName;
}
string** CSV::getMatrix(){
    return matrix;
}
string** CSV::getTransMatrix(){
    return transMatrix;
}

//Utility function to split the string using a regex and store in array
void splitString(string arrToBeSplitted[], string str, char regex){
    string subStr = "";
    int i = 0;
    for(int j=0;j<str.length();j++){
        if (str[j] == regex){
            arrToBeSplitted[i++] = subStr;
            subStr = "";
        }
        else{
            subStr = subStr + str[j];
        }
    }
    arrToBeSplitted[i] = subStr;
}

//Function to read the CSV files and store 
//in original matrix
void CSV::readCSV(){

    // Create an input filestream
    ifstream myFile(fileName);

    // Make sure the file is open
    if(!myFile.is_open()) throw runtime_error("Could not open file");

    // Helper vars
    string line, colname,colVal;
    string val;

    // Read the column names
    if(myFile.good()){
        int row = 0;
        while(getline(myFile, line)){
            string values[columns];
            splitString(values,line,',');
            for(int i=0;i<columns;i++){
                matrix[row][i] = values[i];
                // cout<<matrix[row][i]<<endl;
            }
            row++;
        }
    }
    // Close file
    myFile.close();
}

//Function to take transpose of original 
//matrix and store in transMatrix
void CSV::transpose(){
    for (int i=0;i<columns;i++) {
        for (int j=0;j<rows;j++) {
            transMatrix[i][j] = matrix[j][i]; 
        }
    }
}

//Utility function to create a CSV files
//using the transpose matrix
void CSV::createCSV(string filename){
    // Create an output filestream object
    ofstream myFile(filename);
    
    for(int i=0;i<columns;i++){
        for(int j=0;j<rows;j++){
            if(j == rows-1){
                myFile << transMatrix[i][j];
            }
            else{
                myFile << transMatrix[i][j];
                myFile<<",";
            }

        }
        if(i != columns-1){
            myFile<<"\n";
        }
    } 
    // Close the file
    myFile.close();
}

//Utility function to find number of rows in given file
int CSV::getNumberOfRows(string filename){
    int count = 0;
    // Create an input filestream
    ifstream myFile(filename);
    string line;
    while(getline(myFile,line)){
        count++;
    }
    return count;
}
//Utility function to find number of columns in given file
int CSV::getNumberOfColums(string filename){
    int count = 0;
    // Create an input filestream
    ifstream myFile(filename);
    string line,word;
    getline(myFile,line);
    stringstream ss(line);
    while(getline(ss,word,',')){
        count++;
    }
    return count;
}


// Base class methods
void CSV::fileRead() {
    readCSV();
}

void CSV::execute() {
    transpose();
}

void CSV::fileWrite() {
    createCSV("output_files/task_3.csv");
}
