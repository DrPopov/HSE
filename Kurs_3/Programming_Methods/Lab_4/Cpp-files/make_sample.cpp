//
// Created by ypopov on 31.05.2020.
//
#include <fstream>
#include <iostream>
#include <vector>
#include "../Headers/make_sample.h"
#include "../Headers/matstat.h"
#include "../Headers/chi_square.h"

using namespace std;

ifstream fin;
ofstream fout;


uint32_t make_samples_1(uint32_t sample[]){

    uint32_t x = 123, y = 987, next;

    for(int i = 0; i < 10; i++){
        for(int h = 0; h < 100; h++){
            next = PRNG_1(x, y);

            fout.open("../samples/sample1_" + to_string(i) + ".txt", ios::out | ios::app);
            fout << next  << " "<< endl;
            fout.close();

            x = y;
            y = next;

            sample[h] = next;
        }
        /*
        cout << "Mean is: " << mean(sample, 100) << endl;
        cout << "Variance is: " << variance(sample, 100) << endl;
        cout << "Deviation is: " << deviation(sample, 250) << endl;
        cout << "Coeff of var is: " << coeff_of_variation(sample, 250) << endl;
        uniformity(sample, 250);
        cout << "Xi^2 is: " << check_chi_sq << endl;
        cout << endl;
    */

    }



}


vector<int> make_samples_2(uint32_t sample[]){
    uint32_t x = 123, y = 987, next;

    for(int i = 0; i < 10; i++){
        for(int h = 0; h < 250; h++){
            next = PRNG_2(x, y);

            fout.open("../samples/sample2_" + to_string(i) + ".txt", ios::out | ios::app);
            fout << next  << " "<< endl;
            fout.close();

            x = y;
            y = next;

            sample[h] = next;
        }

        cout << "Mean <is: " << mean(sample, 250) << endl;
        cout << "Variance is: " << variance(sample, 250) << endl;
        cout << "Deviation is: " << deviation(sample, 250) << endl;
        cout << "Coeff of var is: " << coeff_of_variation(sample, 250) << endl;
        uniformity(sample, 250);

    }

}

