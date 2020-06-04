//
// Created by ypopov on 31.05.2020.
//

#ifndef LAB_4_MAKE_SAMPLE_H
#define LAB_4_MAKE_SAMPLE_H


#include <iostream>
#include <vector>
#include "../Headers/PRNG.h"

using namespace std;

/**
 * @brief Ф-ия генерирующая 10 выборок, каждая в своем файлов, в каждм файле по 250 элементов
 *
 * @tparam Num Тип случайной величины
 * @param k Объем выборки
 * @return Выборку, размером k
 */
uint32_t make_samples_1(uint32_t sample[]);


/**
 * @brief Ф-ия генерирующая случайную выборку вторым методом
 *
 * @tparam Num Тип случайной величины
 * @param k Объем выборки
 * @return Выборку, размером k
 */
vector<int> make_samples_2(uint32_t sample[]);




#endif //LAB_4_MAKE_SAMPLE_H
