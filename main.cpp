#include <iostream>
#include <fstream>
using namespace std;

void readEntry(ifstream& in, int& entry);

int main() {


    // read table dimensions and allocate 2D array
    int nRows, nCols;

    ifstream inFile;
    ofstream  outFile;
    inFile.open("../inputData.txt");
    outFile.open("../outputData.txt");
    if  (!inFile.is_open()) {
        cout  << "Could not open input file" << endl;
        return 1;
    }
    if  (!outFile.is_open()) {
        cout << "Could not open output file" << endl;
        return 1;
    }

    inFile >> nRows;
    inFile >> nCols;

    int** table = new int*[nRows];
    for(int i = 0; i < nRows; i++) {
        table[i] = new int[nCols];
    }

    // read table data
    for(int i = 0; i < nRows; i++) {
        for(int j = 0; j < nCols; j++) {
            try {
              readEntry(inFile, table[i][j]);
            }
            catch (int x) {
                    cout << "Entry (" << i << "," << j << ") not an integer, was set to " << x << ", now setting it to 0" << endl;
                    table[i][j] = 0;
                    inFile.clear();
                    string tmp;
                    inFile >> tmp;
            }
        }
    }


    // write table data to the screen in transposed order
    cout << nCols << " " << nRows << endl;
    outFile << nCols  << " " << nRows << endl;
    for(int i = 0; i < nCols; i++) {
        for(int j = 0; j < nRows; j++) {
            cout << table[j][i] << " ";
            outFile << table[j][i] << " ";
        }
        cout << endl;
        outFile << endl;
    }


    // free memory
    for(int i = 0; i < nRows; i++) {
        delete [] table[i];
    }
    delete [] table;

}

void readEntry(ifstream& in, int& entry) {

    in >> entry;
    if(in.fail()) {
        throw entry;
    }
}