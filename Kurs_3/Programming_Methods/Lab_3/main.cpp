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
 *
 *  Время поиска элементов в различных структурах данные показаны на графике
 *
 *
 *  ![рафик 1](hash.png)
 *
 *
 *  График зависимости количества коллизий от числа элементов массива:
 *
 *  ![График 2](Collis.png)
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
#include "Headers/hash.h"
#include "Headers/hashTable.h"
#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>
#include <iomanip>      // std::setw
#include <fstream>

using namespace std;


void demonstration(){
    cout << "\t\tIt's demonstration variant with user's input! Let's start!!!\n";
}

void experiment(){
    ifstream fin;
    ofstream fout;

    bool simple_hash;
    cout << "\t\tIt's experiment variant! Here I intersect time and build charts! Let's go:\n";
    Generator generator = Generator();
    ReadWriter readWriter = ReadWriter();

    // Запись пассажиров в файл-------------------------
    int n = 9;
    //auto passengers = generator.generate_passengers(n, simple_hash);
    //readWriter.writeValues("../raw_data/passengers_" + to_string(n) + ".txt", passengers);
    //for(auto l : passengers){cout <<l;}
    //--------------------------------------------------

    //auto passengers = readWriter.readValues("../raw_data/passengers_" + to_string(n) + ".txt");
    /*
    hashTable hashT = hashTable();

    map<unsigned long long, vector<Passenger>> hash_table;
    unordered_map<unsigned long long, vector<Passenger>> hash_table_1;

    //! Map
    hashT.make_hashTable(hash_table, passengers, simple_hash);
    hashT.displayHash(hash_table);
    hashT.find(hash_table,  Fio("ro", "m", "dj"), simple_hash);


    //! Unordered_map
    hashT.make_hashTable(hash_table_1, passengers, simple_hash);
    hashT.displayHash(hash_table_1);
    hashT.find(hash_table_1,  Fio("ro", "m", "dj"), simple_hash);
    */
    vector<int> list_n = {100, 500, 1000, 5000, 10000, 15000, 25000, 50000, 75000, 100000};
   /*
    //! Linear search
    fout.open("../Results: linear search", ios::out | ios::app);
    fout << "\t\t\t\t\tIt was Linear search!\n";
    fout.close();
    for(int n_k : list_n){
        auto passengers = readWriter.readValues("../raw_data/passengers_" + to_string(n_k) + ".txt");

        auto start = std::chrono::steady_clock::now();
        linearSearch(passengers, Fio("a", "a", "a"));
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        fout.open("../Results: linear search", ios::out | ios::app);
        fout << "Amount of passengers: "  << setw(10) << left <<n_k << "The time of searching: " <<  elapsed_ms.count() << endl;
        fout.close();


    }
    */

    //! Map
    simple_hash = true;
    fout.open("../Results: Map search", ios::out | ios::app);
    fout << "\t\t\t\t\tIt was Map search!\n";
    fout.close();

    vector<int> amount_coll;
    for(int n_k : list_n){
        auto passengers = readWriter.readValues("../raw_passengers_with_good_hash/passengers_" + to_string(n_k) + ".txt");

        hashTable hashT = hashTable();
        map<unsigned long long, vector<Passenger>> hash_table;

        int amount = hashT.make_hashTable(hash_table, passengers, simple_hash);
        amount_coll.push_back(amount);
        cout << "Amount of passengers is " << n_k << " Collisins are " << amount << endl;

        auto start = std::chrono::steady_clock::now();
        hashT.find(hash_table, Fio("ro", "m", "dj"), simple_hash);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

        //fout.open("../Results: Map search", ios::out | ios::app);
        //fout << "Amount of passengers: "  << setw(10) << left <<n_k << "The time of searching: " <<  elapsed_ms.count() << endl;
        //fout.close();
    }


    /*
    //! Unordered_map
    simple_hash = true;
    fout.open("../Results: Unordered_map search with bad hash", ios::out | ios::app);
    fout << "\t\t\t\t\tIt was Unordered_map search!\n";
    fout.close();

    for(int n_k : list_n){
        auto passengers = readWriter.readValues("../raw_passengers_with_bad_hash/passengers_" + to_string(n_k) + ".txt");

        hashTable hashT = hashTable();
        map<unsigned long long, vector<Passenger>> hash_table;

        hashT.make_hashTable(hash_table, passengers, simple_hash);

        auto start = std::chrono::steady_clock::now();
        hashT.find(hash_table,  Fio("ro", "m", "dj"), simple_hash);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

        fout.open("../Results: Unordered_map search with bad hash", ios::out | ios::app);
        fout << "Amount of passengers: "  << setw(10) << left <<n_k << "The time of searching: " <<  elapsed_ms.count() << endl;
        fout.close();
    }

    /*
    //! Binary
    fout.open("../Results: binary search pre sorted", ios::out | ios::app);
    fout << "\t\t\t\t\tIt was binary search!\n";
    fout.close();
    for(int n_k : list_n){
        auto passengers = readWriter.readValues("../raw_passengers_with_bad_hash/passengers_" + to_string(n_k) + ".txt");

        auto sorted = HeapSort(passengers);
        auto start = std::chrono::steady_clock::now();
        binarySearch(sorted, Fio("a", "a", "a"));
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        fout.open("../Results: binary search pre sorted", ios::out | ios::app);
        fout << "Amount of passengers: "  << setw(10) << left <<n_k << "The time of searching: " <<  elapsed_ms.count() << endl;
        fout.close();


    }


   //! Map
   simple_hash = true;
   fout.open("../Results: Map search with bad hash", ios::out | ios::app);
   fout << "\t\t\t\t\tIt was Map search!\n";
   fout.close();

   for(int n_k : list_n){
       auto passengers = readWriter.readValues("../raw_passengers_with_bad_hash/passengers_" + to_string(n_k) + ".txt");

       hashTable hashT = hashTable();
       map<unsigned long long, vector<Passenger>> hash_table;

       hashT.make_hashTable(hash_table, passengers, simple_hash);

       auto start = std::chrono::steady_clock::now();
       hashT.find(hash_table,  Fio("ro", "m", "dj"), simple_hash);
       auto end = std::chrono::steady_clock::now();
       auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

       fout.open("../Results: Map search with bad hash", ios::out | ios::app);
       fout << "Amount of passengers: "  << setw(10) << left <<n_k << "The time of searching: " <<  elapsed_ms.count() << endl;
       fout.close();
   }

*/

}
int main() {
    Generator generator = Generator();
    ReadWriter readWriter = ReadWriter();


    vector<int> list_n = {100, 500, 1000, 5000, 10000, 15000, 25000, 50000, 75000, 100000};

    vector<int> list_n_1 = {100};



    //int n;
    //cin >> n;
    //auto passengers = generator.generate_passengers(n);
    //readWriter.writeValues("../raw_data/passengers_" + to_string(n) + ".txt", passengers);

    //auto passengers = readWriter.readValues("../raw_data/passengers_5.txt");
    //linearSearch(passengers, Fio("a", "a", "a"));


    //auto sorted_passengers = HeapSort(passengers);
    //readWriter.writeValues("../sorted_arrays/passengers_5.txt", sorted_passengers);
    //auto sorted_passengers = readWriter.readValues("../sorted_arrays/passengers_5.txt");
    //binarySearch(sorted_passengers,Fio("a", "a", "a") );


    //unsigned int a = simple_hash(Fio("abc", "a", "r"));
    //cout << a << endl;


    //int b = elf_hash("abc");
    //cout << b;

    //Passenger passenger1 = Passenger(Fio("a", "a", "a"),FlightTime(1, 1, 1), 10, 1);
    //auto passenger2 = generator.generate_passengers(10, true);
    //for(auto i: passenger2){cout << i;};

    //demonstration();
    experiment();




    return 0;
}


