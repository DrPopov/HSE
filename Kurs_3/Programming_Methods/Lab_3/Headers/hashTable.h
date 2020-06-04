//
// Created by ypopov on 24.05.2020.
//

#ifndef LAB_3_HASHTABLE_H
#define LAB_3_HASHTABLE_H

#include "fio.h"
#include "passenger.h"
#include <map>
#include <unordered_map>

/**
 *
 * @brief Хеш-таблица, хранящая пары ключ-значение, где ключ - это ФИО пассажира, а значение - хеш от этого ФИО
 */
class hashTable {
private:
    Fio key;
    int value;

public:
    hashTable();

    //! Ф-ия составления хеш-таблицы(map) из заданного вектора и подсчета кол-ва коллизий
    int make_hashTable(map <std::size_t, vector<Passenger>> &hash_table, vector<Passenger> passengers, bool bad_hash_bool = false);

    //! Ф-ия составления хеш-таблицы(unordered_map) из заданного вектора и подсчета кол-ва коллизий
    int make_hashTable(unordered_map <std::size_t, vector<Passenger>> &hash_table, vector<Passenger> passengers, bool bad_hash_bool = false);

    //! Ф-ия вывода хеш-таблицы(map)
    void displayHash(map <std::size_t, vector<Passenger>> &hash_table);

    //! Ф-ия вывода хеш-таблицы(unordered_map)
    void displayHash(unordered_map <std::size_t, vector<Passenger>> &hash_table);

    //! Операция поиска по ключу в unordered_map
    vector<Passenger> find(unordered_map<std::size_t, vector<Passenger>> &hash_table, const Fio &key, bool bad_hash_bool = false);

    //! Операция поиска по ключу в map
    vector<Passenger> find(map<std::size_t, vector<Passenger>> &hash_table, const Fio &key, bool bad_hash_bool = false);
    //---------------------------------------------------------------------


};


#endif //LAB_3_HASHTABLE_H
