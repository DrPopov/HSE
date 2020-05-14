/*!
 *
 * \mainpage
 *
 * <CENTER>
 * ##  Проект в рамках лабораторной работы № 1 по дисциплине "Методы программирования"
 * ##  Выполнил студент СКБ-172 Попов Юрий
 * ##  Вариант 11
 * </CENTER>
 *
 * ### Сортировки :
 * #### - Сортировка пузыркем
 * #### - Сортировка простыми вставками
 * #### - Пирамидальная сортировка
 *
 * Массив данных о пассажирах некоторой авиакомпании: номер рейса, дата рейса, ФИО пассажира, номер места в самолете (сравнение по полям – дата рейса, номер рейса, ФИО, номер места)
 *
 * Данные для сортировки генерируются в папку output/  в файлы  формата "data_количествоПассажировов(строк)Вфайле"
 *
 * Отсортированные массивы хранятся в ппке sortedArrays/ в файлы формата "output_сортировка_количествоПассажиров"
 *
 *
 * В результате првоеденной работы были получены следующие графиики:
 *
 * <CENTER>
 * ![Графики](/home/ypopov/Pictures/sorts.png)
 * </CENTER>
 *
 *
 * Согласно теоретически данным, сортировки имеют следующую асимптотическую сложность:
 * - Пузырькем: n^2
 * - Простыми вставками: n^2
 * - Пирамидальная: n * log(n)
 *
 *
 * [Ссылка на github с исходным кодом](https://github.com/DrPopov/Programming_Methods)
*/

/**
 *
 * \file main.cpp
*
*  Фвйл с реалищацией
 */


#include <iostream>
#include <string>
//#include "Headers/passenger.h"
#include "Headers/sorts.h"
#include "Headers/ReadWriter.h"
#include <chrono>
#include "Headers/searches.h"
//#include <fstream>

using namespace std;
/***
 *
 * Создает файл ывыв
 * @param amount_of_passengers
 */
void CreateFile(int amount_of_passengers){
    ReadWriter readWriter = ReadWriter();
    Generator generator = Generator();
    auto passengers = generator.get_passengers(amount_of_passengers);

    readWriter.writeValues("../output/data" + to_string(amount_of_passengers), passengers);

}

bool IsArraySorted(vector<Passenger> mass){
    for(int i = 1; i < mass.size(); i++){
        if(mass[i - 1] <= mass[i]){
            continue;
        }else{
            cout << "Passengers aren't sorted";
            return false;
        }
    }
    cout << "Passengers are sorted!!!" << endl;
    return true;
}

int main(){

    srand(time(0));



    //CreateFile(10000);
    ofstream fout;
    fout.open("../results.txt",  ios::out  | ios_base::app);
    fout << "------------------Final results: ----------------------------";


    //Generator generator = Generator();

    int amount_of_passengers;
    int method;

    /**
     * Choose amount of passengers:
     * "Size options:
     *               10.000
     *               50.000
     *              100.000
     *              150.000
     *              200.000
     *              250.000
     *              500.000
     *              750.000
     *            1.000.000
     */
    vector<int> temp1 = {10000, 50000, 100000, 150000, 200000, 250000, 500000, 75000, 1000000};
    //vector<int> temp1_1 = {500000, 750000, 1000000};
    vector<int> temp1_2 = {5000};



    /**
    *Choose method of sorting
    * Methods:
    *      1: bubble,
    *      2: insert,
    *      3: heap
    */
    vector<int> temp2 =  {1, 2, 3};

    int elapsed_seconds;
    std::chrono::time_point<std::chrono::system_clock> start, end;









    /**
     * Generator works
     */
    //Generator generator = Generator();
    //auto passengers = generator.get_passengers(10);


    /**
     * Manual array
     */
     vector<Passenger> passengers{};
     /*

     Passenger passenger1 = Passenger(FlightTime(1, 1, 1),  11111, Fio("a", "a", "a"), 10 );
     Passenger passenger2 = Passenger(FlightTime(2, 2, 2),  22222, Fio("b", "b", "b"), 10 );
     Passenger passenger3 = Passenger(FlightTime(1, 1, 1),  33333, Fio("c", "c", "c"), 10 );
     Passenger passenger4 = Passenger(FlightTime(1, 1, 1),  11111, Fio("a", "a", "a"), 10 );

     passengers.push_back(passenger1);
     passengers.push_back(passenger2);
     passengers.push_back(passenger3);
     passengers.push_back(passenger4);
    */



     int k = linearSearch("../output/data_10", Fio("c", "c", "c"));
     cout << k;


    ReadWriter readWriter = ReadWriter();

    //passengers = readWriter.readValues("../output/data_500");
    //auto sorted = HeapSort(passengers);


    //IsArraySorted(sorted);
    //readWriter.writeValues("../sortedArrays/output_heap_" + to_string(passengers.size()), sorted);

     int bin = binarySearch("../sortedArrays/output_heap_500", Fio("c", "c","c"));

     cout << bin;





     return 0;
}

