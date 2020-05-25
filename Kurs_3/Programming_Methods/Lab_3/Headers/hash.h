//
// Created by ypopov on 16.05.2020.
//
#pragma one;

#include "iostream"
#include "fio.h"

using namespace std;

/**
 * @brief Выполняет хеширование строки str по "плохому" алгоритму с коллизиями
 *
 * @details: Код элемента умножается на 10 в степени его порядкового номера, начиная с 0
 *
 * Итоговая сумма- хеш
 *
 * @param str: Строка, которую надо захешировать
 * @return: int хеш от строки str
 */
unsigned long long elf_hash(Fio fio);



/**
 * @brief Выполняет хеширование строки str по "хорошему" алгоритму с малым количеством коллизий
 *
 * @param str: Строка, которую надо захешировать
 * @return: int хеш от строки str
 */
unsigned long long simple_hash(Fio fio);

/**
 * @brief Ф-ия, определяющая какой хеш вызывать: хороший или плохой
 *
 * @param key ФИО, от которого будет браться хеш
 * @param Is_simple_hash По умолчанию - false, то есть по умолчанию берется хороший хеш
 * @return Хеш ключа
 */
unsigned long long get_hash(Fio key, bool Is_simple_hash);