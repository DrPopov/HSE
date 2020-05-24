//
// Created by ypopov on 15.05.2020.
//

#pragma one;
#include "passenger.h"
#include "hash.h"
#include <map>




/**
 * @brief Линейный поиск пассажиров в векторе пассажиров
 *
 * @param passengers Вектор пассажиров, в котором происходит поиск
 * @param key ФИО пассажиров, которых необходмо найти
 * @return Вектор найденных пассажиров с данным фИО
 */
vector<Passenger> linearSearch(const vector<Passenger>& passengers, const Fio& key);


/**
 * @brief Бинарный поиск пассажиров в отсортированном векторе пассажиров
 *
 * @param sorted_passengers Отсортированный вектор пассажиров, в котором происходит поиск
 * @param key ФИО пассажиров, которых необходмо найти
 * @return Вектор найденных пассажиров с данным фИО
 */
vector<Passenger> binarySearch(vector<Passenger> sorted_passengers, const Fio& key);


/**
 * @brief Поиск в хеш-таблице
 *
 * @param hash_table Хеш-таблица, в которой осуществляется поиск
 * @param key ФИО пассажирова, которых необходимо найти
 * @return Вектор найденных пассажиров
 */
vector<Passenger> hash_search(map<unsigned int, vector<Passenger>> hash_table, const Fio& key);