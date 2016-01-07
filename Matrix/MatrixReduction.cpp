//
//  MatrixReduction.cpp
//  Matrix
//
//  Created by Gianluca Rago on 12/22/15.
//  Copyright © 2015 Ragoware LLC. All rights reserved.
//

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector< vector<double> > matrix;
bool hasREF = false;

void printMatrix() {
    for (int rowI = 0; rowI < matrix.size(); rowI++) {
        for (int cellI = 0; cellI < matrix[rowI].size(); cellI++) {
            cout << setw(10) << matrix[rowI][cellI];
        }
        cout << "\n";
    }
    cout << "\n";
}

void set0(int rowI, int toCellI) {
    vector<double> newRow;
    newRow.resize(matrix[rowI].size());
    vector<double> referenceRow;
    referenceRow.resize(newRow.size());
    newRow = matrix[rowI];
    for (int referenceRowI = 0; referenceRowI < matrix.size(); referenceRowI++) {
        if (matrix[referenceRowI][toCellI] == 1.0) {
            if (toCellI == 0) {
                referenceRow = matrix[referenceRowI];
                if (!hasREF) {
                    break;
                }
            } else {
                bool hasZeros = true;
                for (int referenceRowCellI = 0; referenceRowCellI < toCellI; referenceRowCellI++) {
                    if (matrix[referenceRowI][referenceRowCellI] != 0.0) {
                        hasZeros = false;
                    }
                }
                if (hasZeros) {
                    referenceRow = matrix[referenceRowI];
                    if (!hasREF) {
                        break;
                    }
                }
            }
        }
    }
    for (int cellI = 0; cellI < newRow.size(); cellI++) {
        newRow[cellI] = (-matrix[rowI][toCellI]*referenceRow[cellI])+newRow[cellI];
    }
    matrix[rowI] = newRow;
}

void set1(int rowI) {
    vector<double> newRow;
    newRow.resize(matrix[rowI].size());
    for (int cellI = 0; cellI < newRow.size(); cellI++) {
        double newVal = matrix[rowI][cellI]/matrix[rowI][rowI];
        if (newVal == -0.0) {
            newVal = 0.0;
        }
        newRow[cellI] = newVal;
    }
    matrix[rowI] = newRow;
}

void getREF() {
    long matrixWidth = matrix[0].size();
    for (int rowI = 0; rowI < matrix.size(); rowI++) {
        for (int cellI = 0; cellI < matrixWidth; cellI++) {
            if (matrix[rowI][cellI] != 0.0 && cellI < rowI && rowI != 0) {
                set0(rowI, cellI);
            }
            if (matrix[rowI][cellI] != 1.0 && cellI == rowI) {
                set1(rowI);
            }
        }
    }
    hasREF = true;
}

void getRREF() {
    long matrixWidth = matrix[0].size();
    for (int rowI = (int)matrix.size()-1; rowI >= 0; rowI--) {
        for (int cellI = (int)matrixWidth-2; cellI > rowI; cellI--) {
            if (matrix[rowI][cellI] != 0.0 && cellI != rowI) {
                set0(rowI, cellI);
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    //matrix = { {1.0, 2.0, 1.0, 6.0}, {2.0, -1.0, -1.0, 1.0}, {1.0, 3.0, -4.0, -3.0} };
    //matrix = { {1.0, 1.0, 0.0, 5.0}, {-2.0, -1.0, 2.0, -10.0}, {3.0, 6.0, 7.0, 14.0} };
    matrix = { {1.0, 0.0, 3.0}, {0.0, 2.0, 4.0}, {2.0, 0.0, 8.0} };
    
    cout << "Original Matrix: \n";
    printMatrix();
    getREF();
    cout << "REF: \n";
    printMatrix();
    getRREF();
    cout << "RREF: \n";
    printMatrix();
    
    return 0;
}
