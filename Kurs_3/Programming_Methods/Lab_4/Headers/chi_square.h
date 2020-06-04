//
// Created by ypopov on 31.05.2020.
//

#ifndef LAB_4_CHI_SQUARE_H
#define LAB_4_CHI_SQUARE_H

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/**
 * @brief Ф-ия вычисления эксперементального критерия Xи- квдрат
 *
 * @tparam Num  Тип элементов выборки
 * @param sample Выборка
 * @return  Критерий Хи-квадарат
 */
pair<double, size_t> chi_sq(uint32_t k[], int leng);


/**
 * @brief Ф-ия соответствия критерию Хи-квадарат
 *
 * @tparam Num  Тип элементов выборки
 * @param sample Выборка
 * @return Соответствует или нет
 */
bool check_chi_sq(uint32_t k[], int leng);


#endif //LAB_4_CHI_SQUARE_H
