//
// Created by ypopov on 31.05.2020.
//
#include <iostream>
#include <vector>
#include <cmath>
#include "../Headers/make_sample.h"
#include "../Headers/sort.h"

using namespace std;


pair<double, size_t> chi_sq(uint32_t sample[], int leng){
    auto N = leng;  //! Количество сгенерированных чисел
   size_t interval_count  = static_cast<size_t>(1 + 3.322 *log(N)); //! Определяем число интервалов по правилу Стерджеса

    vector<int> n_i_vector; //! Количество случайных чисел, попавший в каждый интервал
    vector<int> p_i_vector; //! Теоретическая вероятность попадания в k-ый интервал
    // Длина интервала = 1/k
    uint32_t results = make_samples_1(sample); //! Запускается ГСПЧ N раз
    //vector<Num> results = make_sample_2<Num>(N);
    HeapSort(sample, N);
    //uint32_t  sorted = HeapSort(results, N);

    //! Заполняем вектор n_i_vector
    auto beg = 0;
    int temp = 0;
    int i = 0;
    while(true){
        if(beg < sample[i] && sample[i] < beg + interval_count){
            temp++;
            i++;
        }else{
            n_i_vector.push_back(temp);
            temp = 0;
            beg += interval_count;
        }
        if(beg == 1){break;}
    }


    //! Заполняем вектор p_i_vector;
    for(int j = 0; j < interval_count; j++){
        auto p = 1 / j;
        p_i_vector.push_back(p);
    }


    //! Значение Хи-квадарат для эксперементальных данных
    double chi_sq_exp;
    for(int k = 0; k < interval_count; k++ ){
        chi_sq_exp += (n_i_vector[k] - p_i_vector[k] * N)^2 /(p_i_vector[k] * N);
    }


    return {chi_sq_exp, interval_count - 1};
}


bool check_chi_sq(uint32_t sample[], int leng){
    vector<double> quantiles = {3.8, 6 , 7.8 , 9.5 , 11.1 , 12.6 , 14.1 , 15.5 , 16.9 , 18.3 , 19.7 , 21.0 , 22.4 , 23.7 , 25 , 26.3 , 27.6 , 28.9 , 30.1 , 31.4 , 32.7 , 33.9 , 35.2 , 36.4, 37.7, 38.9, 40.1 ,41.3, 42.6, 43.8};

    auto [chi, k] = chi_sq(sample, leng);
    cout << (chi < quantiles[k - 1]);
    return (chi < quantiles[k - 1]);
}