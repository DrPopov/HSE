//
// Created by ypopov on 14.03.2020.
//
#pragma once // защита от двойного подключения заголовочного файла
#include "fio.h"
#include "passenger.h"
#include "generator.h"
#include <string>



using namespace std;


/**
 * @brief - Класс, описывающий запись в файл и чтение из него
 */
class ReadWriter{
public:
    fstream fin; // input file
    fstream fout;// output file


        /**
     *
     * @param filename  Файл, в который будет происходить запись
     * @param passengers Вектор пассажиров
     */
    void writeValues(string filename, vector<Passenger> passengers);


    /**
     *
     * @param filename Файл, из которого будут читаться данные
     * @return Вектор пассажиров
     */
    vector<Passenger> readValues(string filename);

};
