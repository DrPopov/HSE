//
// Created by ypopov on 14.03.2020.
//
#pragma once // защита от двойного подключения заголовочного файла
#include "fio.h"
#include "passenger.h"
#include "generator.h"
#include <string>



using namespace std;



class ReadWriter{
public:
    fstream fin; // input file
    fstream fout;// output file

    void writeValues(string filename, vector<Passenger> passengers);

    vector<Passenger> readValues(string filename);

};
