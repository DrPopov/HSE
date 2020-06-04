/*!
 *
 * \mainpage
 *
 * <CENTER>
 * ##  Проект в рамках лабораторной работы № 4 по дисциплине "Методы программирования"
 * ##  Выполнил студент СКБ-172 Попов Юрий
 * ##  Вариант 11
 * </CENTER>
 *
 *
 *  Реализовать две метода генерции псевдослучайных чисел
 *
 *
 *
 *
 *
 * ![Графики](p1.png)
 *
 *
 * [Ссылка на github с исходным кодом](https://github.com/DrPopov/HSE/tree/master/Kurs_3/Programming_Methods)
*/

/**
 *
 * \file main.cpp
*
*  Файл с реализацией
 */



#include <iostream>
#include <fstream>
#include <random>
#include "Headers/matstat.h"
#include "Headers/make_sample.h"
#include "Headers/PRNG.h"
#include <chrono>

using namespace std;

void func(){
    uint32_t sample1[250], sample2[250];
    make_samples_1(sample1);
    //make_samples_2(sample2);
}

int main() {

    ifstream fin;
    ofstream fout;




    //-----------------------

    //uint32_t sample1[100], sample2[100];
    uint32_t x = 123, y = 987, next ;
    for(int i =0; i< 20; i++){
        next =  PRNG_1(x, y);
        x = y;
        y = next;
        cout << PRNG_1(x, y) % 100 << endl;
    };
    //cout << PRNG_1(x, y);
    //func();
    /*
    uint32_t x = 123, y = 987, next;

    for(int i = 0; i < 10; i++){
        for(int h = 0; h < 250; h++){
            next = PRNG_1(x, y);

            fout.open("../samples/sample1_" + to_string(i) + ".txt", ios::out | ios::app);
            fout << next  << " "<< endl;
            fout.close();

            x = y;
            y = next;

            sample1[h] = next;
        }

    }



    */
    /*
    int leng[] = {1000, 5000, 10000, 100000, 250000, 400000, 600000, 800000, 1000000};

    for(int i = 0; i < (sizeof(leng)/sizeof(int)) ; i++){
        //cout << "Hello, World!" << endl;

        //! 1-ый метод генерации
        uint32_t x = 311, y = 1609, next;

        uint32_t *sample1 = new uint32_t[leng[i]];

        auto begin = std::chrono::steady_clock::now();

        for(int r = 0; r < leng[i] ; r++){
            next = PRNG_1(x, y);
            x = y;
            y = next;

            sample1[r] = next;
        }
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

        cout << "Time_1 is: " << elapsed_ms.count() << endl;
        fout.open("../Results", ios::out | ios::app);
        fout << "Time_1 is: " << elapsed_ms.count() << endl;
        fout.close();

        //! 2 -ой метод генерации
        x = 121, y = 1231;
        uint32_t *sample2 = new uint32_t[leng[i]];

        begin = std::chrono::steady_clock::now();
        for(int r=0; r < leng[i] ; r++)
        {
            next = PRNG_2(x, y);
            x = y;
            y = next;
            sample2[r] = next;
        }

        end = std::chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

        cout << "Time_2 is: " << elapsed_ms.count() << endl;
        fout.open("../Results", ios::out | ios::app);
        fout << "Time_2 is: " << elapsed_ms.count() << endl;
        fout.close();


        //! Классический метод генерации чисел в С++
        uint32_t *sample3 = new uint32_t[leng[i]];
        srand(1231); // устанавливаем стартовое значение - 1231

        begin = std::chrono::steady_clock::now();
        for(int r=0; r < leng[i] ; r++){

            sample3[r] = (rand() & 0xffff);
        }
        end = std::chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

        cout << "Time_3 is: " << elapsed_ms.count() << endl;
        fout.open("../Results", ios::out | ios::app);
        fout << "Time_3 is: " << elapsed_ms.count() << endl;
        fout.close();



        delete sample1;
        delete sample2;
        delete sample3;

    }
    */

    return 0;
}
