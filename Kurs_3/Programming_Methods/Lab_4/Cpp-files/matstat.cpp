//
// Created by ypopov on 31.05.2020.
//

#include "../Headers/matstat.h"
#include <iostream>
//#include <iterator>
//#include <numeric>
//#include <vector>
#include <cmath>

using namespace std;


double mean(uint32_t sample[], int leng){
    uint64_t summ=0;
    for(int t=0; t < leng; t++)
    {
        summ += sample[t];
    }

    return static_cast<double>(summ)/leng;
}


double variance(uint32_t sample[], int leng){
    uint32_t MeanV = mean(sample, leng);
    double disp = 0;
    for(int i=0; i < leng; i++)
    {
        disp += pow((sample[i] - MeanV), 2);
    }

    return disp/leng;
}



double deviation(uint32_t sample[], int leng){
    return sqrt(variance(sample, leng));
}


double coeff_of_variation(uint32_t sample[], int leng){
    return deviation(sample, leng)/ mean(sample, leng) * 100;
}


void uniformity(uint32_t sample[], int leng){
    double k = coeff_of_variation(sample, leng);

    if(k < 33){
        cout << "Выборка однородна\n";
    }else if(k >= 3){
        cout << "Выборка неоднородна\n";
    }else{
        cout << " Неправильные вычисления! Переделывай!\n";
    }
}

