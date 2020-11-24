#include <iostream>
#include <string>
#include "include/UCINET_DL_READER.h"
#include "include/CsvFileReader.h"
#include "include/CSV.h"
#include "include/base.h"
using namespace std;

// The sample files for input files for each task is stored in input_files directory
// They are named according to the task numbers.

// Taking input as command line arguements
// ./main <task number> <filename> <...>
// example: for UCINET FILE READER (TASK-5) having data in task_3.txt file in input_files directory
// ./main 5 task_5.txt
// for CSV File Reader (TASK-8) having data in task_8.csv file in input_files directory
// ./main 8 task_8.csv A B
// for CSV (TASK-3) having data in task_3.csv in input_files directory
// ./main 3 task_3.csv

// All header files are included from the 'include' directory

// Output files for each individual task goes into the output_files directory
// They are named as task_<task no.>
// For example for task-3, output is stored in output_files with the name 'task_3.csv'


string processString(string str) {
    return str.erase(str.find_last_not_of(" \n\r\t")+1);
}

string getOutputFileName(int task) {
    return "output_files/task_"+task;
}

int main(int argc, char** argv) {
    string fileName;
    base *FileReader;
    
    // Task-5 
    if (argv[1][0] == '5') {
        fileName = "input_files/"+processString(argv[2]);
        FileReader = new UCINET_DL_READER(fileName);
    }

    // Task-8
    else if (argv[1][0] == '8') {
        fileName = "input_files/"+processString(argv[2]);
        FileReader = new CsvFileReader(fileName,processString(argv[3]),processString(argv[4]));
    }

    // Task-3
    else if (argv[1][0] == '3') {
        fileName = "input_files/"+processString(argv[2]);
        const int rows = CSV::getNumberOfRows(fileName);
        const int columns = CSV::getNumberOfColums(fileName);
        FileReader = new CSV(fileName,rows,columns);
    }

    // Reading, Executing and Writing output for the file.
    FileReader->fileRead();
    FileReader->execute();
    FileReader->fileWrite();
    delete FileReader;

    return 0;
}