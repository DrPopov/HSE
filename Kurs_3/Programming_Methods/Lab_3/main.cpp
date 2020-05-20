/*!
 *
 * \mainpage
 *
 * <CENTER>
 * ##  Проект в рамках лабораторной работы № 3 по дисциплине "Методы программирования"
 * ##  Выполнил студент СКБ-172 Попов Юрий
 * ##  Вариант 11
 * </CENTER>
 *
 * [Ссылка на github с исходным кодом](https://github.com/DrPopov/HSE/tree/master/Kurs_3/Programming_Methods)
*/

/**
 *
 * \file main.cpp
*
*  Файл с реализацией
 */


#include "Headers/sorts.h"
#include "Headers/searches.h"
#include "Headers/ReadWriter.h"
#include "Headers/generator.h"
#include <chrono>
#include <iostream>
#include <string>
//#include <fstream>

using namespace std;

int main() {

    Generator generator = Generator();
    ReadWriter readWriter = ReadWriter();

    //int n;
    //cin >> n;
    //auto passengers = generator.generate_passengers(n);
    //readWriter.writeValues("../raw_data/passengers_" + to_string(n) + ".txt", passengers);

    auto passengers = readWriter.readValues("../raw_data/passengers_5.txt");


    linearSearch(passengers, Fio("a", "a", "a"));

    //auto sorted_passengers = HeapSort(passengers);
    auto sorted_passengers = readWriter.readValues("../sorted_arrays/passengers_5.txt");

    binarySearch(sorted_passengers,Fio("a", "a", "a") );
    return 0;
}
