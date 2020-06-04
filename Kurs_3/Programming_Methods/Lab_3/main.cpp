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
    cout << "How many passengers do you want: ";
    int n_k;
    cin >> n_k;

    cout << "Do you want simple hash_function(1) or good hash_function(0)?\n";
    bool simple_hash;
    cin >> simple_hash;

    cout << "Which FIO are you looking for?(rgrx, jxpn, fxugac)\n";

    string f1, f2, f3;
    cout << "Enter first name: \n";
    cin >> f1;
    cout << "Enter second name: \n";
    cin >> f2;
    cout << "Enter third name: \n";
    cin >> f3;

    Fio key = Fio(f1, f2, f3);


    ifstream fin;
    ofstream fout;

    Generator generator = Generator();
    ReadWriter readWriter = ReadWriter();

    auto passengers_1 = generator.generate_passengers(n_k, simple_hash);
    if(simple_hash){
        readWriter.writeValues("../raw_passengers_with_bad_hash/passengers_" + to_string(n_k) + ".txt", passengers_1);
    }else{
        readWriter.writeValues("../raw_passengers_with_good_hash/passengers_" + to_string(n_k) + ".txt", passengers_1);
    }

    if(simple_hash){
        fout.open("../Demonstration's results: bad hash", ios::out | ios::app);
        fout << "\t\t\t\t\tIt was Map search with bab hash!\n";
        fout.close();

    }else{
        fout.open("../Demonstration's results: good hash", ios::out | ios::app);
        fout << "\t\t\t\t\tIt was Map search with good hash!\n";
        fout.close();
    }



    vector<int> amount_coll;
    vector<Passenger> passengers;

    if(simple_hash){
        passengers = readWriter.readValues("../raw_passengers_with_bad_hash/passengers_" + to_string(n_k) + ".txt");
    }else{
        passengers = readWriter.readValues("../raw_passengers_with_good_hash/passengers_" + to_string(n_k) + ".txt");
    }


    hashTable hashT = hashTable();
    map<std::size_t, vector<Passenger>> hash_table;



    int amount = hashT.make_hashTable(hash_table, passengers, simple_hash);
    hashT.displayHash(hash_table);

    amount_coll.push_back(amount);
    cout << "\nAmount of passengers is:  " << setw(10) << left  << n_k << " Collisins are:  " << amount << endl;

    auto start = std::chrono::steady_clock::now();
    auto found_passengers = hashT.find(hash_table,  key, simple_hash);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    if(simple_hash){
        fout.open("../Demonstration's results: bad hash", ios::out | ios::app);
        fout << "Amount of passengers: "  << setw(10) << left <<n_k << "The time of searching: " <<  setw(10) << left << elapsed_ms.count() << "   The amount of collisions:  " << setw(10) << left << amount <<endl;       fout.close();

    }else{
        fout.open("../Demonstration's results: good hash", ios::out | ios::app);
        fout << "Amount of passengers: "  << setw(10) << left << n_k << "The time of searching: " <<  setw(10) << left << elapsed_ms.count() << "   The amount of collisions:  " << setw(10) << left << amount <<endl;
        fout.close();
    }

    for(auto i : found_passengers){
        cout << "Here are they:  \n";
        cout << i;
    }

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
    //auto passengers = generator.generate_passengers(n, bad_hash);
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

    vector<int> list_n = {100, 500, 1000, 5000, 10000, 15000, 25000, 50000, 75000, 100000};


    //! Map
    simple_hash = true;
    fout.open("../Results: Map search", ios::out | ios::app);
    fout << "\t\t\t\t\tIt was Map search!\n";
    fout.close();

    vector<int> amount_coll;
    for(int n_k : list_n){
        auto passengers = readWriter.readValues("../raw_passengers_with_good_hash/passengers_" + to_string(n_k) + ".txt");

        hashTable hashT = hashTable();
        map<std::size_t, vector<Passenger>> hash_table;

        int amount = hashT.make_hashTable(hash_table, passengers, simple_hash);
        amount_coll.push_back(amount);
        cout << "Amount of passengers is:  " << setw(10) << left  << n_k << " Collisins are:  " << amount << endl;

        auto start = std::chrono::steady_clock::now();
        //hashT.find(hash_table, Fio("ro", "m", "dj"), bad_hash);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

        //fout.open("../Results: Map search", ios::out | ios::app);
        //fout << "Amount of passengers: "  << setw(10) << left <<n_k << "The time of searching: " <<  elapsed_ms.count() << endl;
        //fout.close();
    }


*/


}


void lin( bool simple_hash){ //! Linear search
    ifstream fin;
    ofstream fout;

    Generator generator = Generator();
    ReadWriter readWriter = ReadWriter();

    vector<int> list_n = {100, 500, 1000, 5000, 10000, 15000, 25000, 50000, 75000, 100000};


    fout.open("../Results: linear search", ios::out | ios::app);
    fout << "\t\t\t\t\tIt was Linear search!\n";
    fout.close();

    for(int n_k : list_n){
        vector<Passenger> passengers;

        if(simple_hash){
            passengers = readWriter.readValues("../raw_passengers_with_bad_hash/passengers_" + to_string(n_k) + ".txt");
        }else{
            passengers = readWriter.readValues("../raw_passengers_with_good_hash/passengers_" + to_string(n_k) + ".txt");
        }

        auto start = std::chrono::steady_clock::now();
        linearSearch(passengers, Fio("a", "a", "a"));
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

        fout.open("../Results: linear search", ios::out | ios::app);
        fout << "Amount of passengers: "  << setw(10) << left <<n_k << "The time of searching: " <<  elapsed_ms.count() << endl;
        fout.close();
    }
}

void bin(bool simple_hash){ //! Binary
    ifstream fin;
    ofstream fout;

    Generator generator = Generator();
    ReadWriter readWriter = ReadWriter();

    vector<int> list_n = {100, 500, 1000, 5000, 10000, 15000, 25000, 50000, 75000, 100000};


    fout.open("../Results: binary search pre sorted", ios::out | ios::app);
    fout << "\t\t\t\t\tIt was binary search!\n";
    fout.close();

    for(int n_k : list_n){
        vector<Passenger> passengers;

        if(simple_hash){
            passengers = readWriter.readValues("../raw_passengers_with_bad_hash/passengers_" + to_string(n_k) + ".txt");
        }else{
            passengers = readWriter.readValues("../raw_passengers_with_good_hash/passengers_" + to_string(n_k) + ".txt");
        }

        auto sorted = HeapSort(passengers);
        auto start = std::chrono::steady_clock::now();
        binarySearch(sorted, Fio("a", "a", "a"));
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

        fout.open("../Results: binary search pre sorted", ios::out | ios::app);
        fout << "Amount of passengers: "  << setw(10) << left <<n_k << "The time of searching: " <<  elapsed_ms.count() << endl;
        fout.close();

    }

}

void m_func(bool simple_hash){ //! Map
    ifstream fin;
    ofstream fout;

    Generator generator = Generator();
    ReadWriter readWriter = ReadWriter();

    vector<int> list_n = {100, 500, 1000, 5000, 10000, 15000, 25000, 50000, 75000, 100000};
    vector<int> list_n_2 = {101, 501, 1001, 5001, 1001, 15001, 25000, 50001, 75001, 100001};
    vector<int> list_n_3 = { 100002, 100003};

    if(simple_hash){
        fout.open("../Results: Map search with bad hash", ios::out | ios::app);
        fout << "\t\t\t\t\tIt was Map search with bab hash!\n";
        fout.close();

    }else{
        fout.open("../Results: Map search with good hash", ios::out | ios::app);
        fout << "\t\t\t\t\tIt was Map search with good hash!\n";
        fout.close();
    }


    for(int n_k : list_n){
        vector<int> amount_coll;
        vector<Passenger> passengers;

        if(simple_hash){
            passengers = readWriter.readValues("../raw_passengers_with_bad_hash/passengers_" + to_string(n_k) + ".txt");
        }else{
            passengers = readWriter.readValues("../raw_passengers_with_good_hash/passengers_" + to_string(n_k) + ".txt");
        }


        hashTable hashT = hashTable();
        map<std::size_t, vector<Passenger>> hash_table;

        int amount = hashT.make_hashTable(hash_table, passengers, simple_hash);
        amount_coll.push_back(amount);
        cout << "Amount of passengers is:  " << setw(10) << left  << n_k << " Collisins are:  " << amount << endl;

        auto start = std::chrono::steady_clock::now();
        //hashT.find(hash_table,  Fio("ro", "m", "dj"), bad_hash);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

        if(simple_hash){
            fout.open("../Results: Map search with bad hash", ios::out | ios::app);
            fout << "Amount of passengers: "  << setw(10) << left <<n_k << "The time of searching: " <<  setw(10) << left << elapsed_ms.count() << "   The amount of collisions:  " << setw(10) << left << amount <<endl;       fout.close();

        }else{
            fout.open("../Results: Map search with good hash", ios::out | ios::app);
            fout << "Amount of passengers: "  << setw(10) << left << n_k << "The time of searching: " <<  setw(10) << left << elapsed_ms.count() << "   The amount of collisions:  " << setw(10) << left << amount <<endl;
            fout.close();
        }
    }

}

void un_func(bool simple_hash){ //! Unordered_map

    ifstream fin;
    ofstream fout;

    Generator generator = Generator();
    ReadWriter readWriter = ReadWriter();

    vector<int> list_n = {100, 500, 1000, 5000, 10000, 15000, 25000, 50000, 75000, 100000};

    if(simple_hash){
        fout.open("../Results: Unordered_map search with bad hash", ios::out | ios::app);
        fout << "\t\t\t\t\tIt was Unordered_map search with bad hash!\n";
        fout.close();

    }else{
        fout.open("./Results: Unordered_map search with good hash", ios::out | ios::app);
        fout << "\t\t\t\t\tIt was Unordered_map search with good hash!\n";
        fout.close();
    }


    for(int n_k : list_n){
        vector<Passenger> passengers;

        if(simple_hash){
            passengers = readWriter.readValues("../raw_passengers_with_bad_hash/passengers_" + to_string(n_k) + ".txt");
        }else{
            passengers = readWriter.readValues("../raw_passengers_with_good_hash/passengers_" + to_string(n_k) + ".txt");
        }


        hashTable hashT = hashTable();
        map<std::size_t, vector<Passenger>> hash_table;

        hashT.make_hashTable(hash_table, passengers, simple_hash);

        auto start = std::chrono::steady_clock::now();
        //hashT.find(hash_table,  Fio("ro", "m", "dj"), bad_hash);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

        if(simple_hash){
            fout.open("../Results: Unordered_map search with bad hash", ios::out | ios::app);
            fout << "Amount of passengers: "  << setw(10) << left <<n_k << "The time of searching: " <<  elapsed_ms.count() << endl;
            fout.close();

        }else{
            fout.open("./Results: Unordered_map search with good hash", ios::out | ios::app);
            fout << "Amount of passengers: "  << setw(10) << left <<n_k << "The time of searching: " <<  elapsed_ms.count() << endl;
            fout.close();
        }

    }
}



int main() {
    bool bad_hash_bool = false;

    //Generator generator = Generator();
    //ReadWriter readWriter = ReadWriter();
    //int n= 5;
    //auto passengers = generator.generate_passengers(n);
    //readWriter.writeValues("../raw_passengers_with_good_hash/passengers_" + to_string(n) + ".txt", passengers);
   // m_func(bad_hash_bool);

    demonstration();

    return 0;
}