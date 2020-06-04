//
// Created by ypopov on 14.03.2020.
//

#include "../Headers/ReadWriter.h"
#include <iostream>

using namespace std;

void ReadWriter::writeValues(string filename){

    fout.open(filename, ios::out | ios::trunc);


    if (!fout.is_open()) {
        cout << "Error opening file data_out.txt.\n";
        exit(EXIT_FAILURE);
    }


    fout.close();

}

