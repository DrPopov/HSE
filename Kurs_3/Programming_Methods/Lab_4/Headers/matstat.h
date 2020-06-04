//
// Created by ypopov on 31.05.2020.
//
#ifndef LAB_4_MATSTAT_H
#define LAB_4_MATSTAT_H

#include <vector>
#include <cmath>

using namespace std;


/**
 * @brief Ф-ия вычисления выборочного среднего выборки
 *
 * @tparam Num Случайная величина
 * @param sample Вектор случайных чисел
 * @return Математическое ожидание
 */
double mean(u_int32_t sample[], int leng);


/**
 * @brief Ф-ия вычисления дисперсии выборки
 *
 * @tparam Num Случайная величина
 * @param sample Вектор случайных величин
 * @return Дисперсия
 */
double variance(u_int32_t sample[], int leng);


/**
 * @brief Ф-ия вычисления среднеквадратичное отклонение выборки
 *
 * @tparam Num Случайная величина
 * @param sample Вектор случайных величин
 * @return Дисперсия
 */
double deviation(u_int32_t sample[], int leng);


/**
 * @brief Ф-ия вычисления коэффициента вариации выборки
 *
 * @tparam Num Случайная величина
 * @param sample Вектор случайных величин
 * @return Коэффициент вариации в %
 */
double coeff_of_variation(u_int32_t sample[], int leng);

/**
 * @brief Ф-ия, делающая вывод об однородности выборки
 *
 *@details koeff < 33 - Однородная, >= 33 - Неоднородна
 *
 * @tparam Num
 * @param sample
 */
void uniformity(u_int32_t sample[], int leng);

#endif //LAB_4_MATSTAT_H
