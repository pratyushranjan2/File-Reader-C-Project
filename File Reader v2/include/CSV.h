#include <string>
#include "base.h"
using namespace std;
#ifndef CSV_H
#define CSV_H
//Class which can be pictured as CSV file
class CSV: public base{
    private:
        /* data */
        string fileName;        //Fine name of CSV file
        string **matrix;    //Matrix to store the contents of the file
        string **transMatrix; //Matrix which is transpose of original matrix
        int rows;  //Number of rows in given CSV file
        int columns;    //Number of columns in given CSV file
    public:
        //Constructors,Desctuctors,Copy Constructors
        CSV(string name,int height,int width);
        ~CSV();
        CSV(const CSV &F);
        //Getters and setters
        void setRows(int );
        void setColumns(int );
        void setMatrix(string **m);
        void setFilename(string name);
        string getFileName();
        int getRows();
        int getColumns();
        string** getMatrix();
        string** getTransMatrix();
        //Function to read CSv files
        void readCSV();
        //Function to take transpose of matrix
        void transpose();
        //Function to create a new CSV file using the contents
        //transposed matrix
        void createCSV(string filename);
        //Utility static functions to get number of rows and columns
        static int getNumberOfRows(string fileName);
        static int getNumberOfColums(string fileName);

    // Base class methods
    void fileRead();
    void execute();
    void fileWrite();
};
#endif
