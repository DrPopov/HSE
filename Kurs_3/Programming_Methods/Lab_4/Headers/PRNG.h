//
// Created by ypopov on 28.05.2020.
//

#ifndef LAB_4_PRNG_H
#define LAB_4_PRNG_H


#include <random>

/**
 * @brief Генерирует псевдослучайное число в диапазоне от [0, 65535]
 *
 * @details ((x+y+3)*x >> 8) & 0xffff
 *
 * @param x  32 битное неотриательное число
 * @param y  32 битное неотриательное число
 * @return   Случайное число в диапазоне от [0, 65535]
 */
uint32_t PRNG_1(uint32_t x, uint32_t y);


/**
 * @brief Генерирует псевдослучайное число в диапазоне от [0, 65535]
 *
 * @details (x+y)^2 & 0xffff
 *
 * @param x  32 битное неотриательное число
 * @param y  32 битное неотриательное число
 * @return   Случайное число в диапазоне от [0, 65535]
 */
uint32_t PRNG_2(uint32_t x, uint32_t y);


#endif //LAB_4_PRNG_H
