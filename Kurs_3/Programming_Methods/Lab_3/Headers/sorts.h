//
// Created by ypopov on 15.05.2020.
//
#pragma one;
#include "passenger.h"

using namespace std;

/**
 *@brief - Метод построения бинарного дерева
 *
 * @param passengers - пассажиры, которые должны быть отсортированы
 * @param n - размер кучи
 * @param i - корень
 */
void BiTree(vector<Passenger> &passengers, int n, int i);


/**
 *@brief - Алгритм пирамидальной сортировки
 *
 *
 * @param passengers - пассажиры, которые должны быть отсортированы
 * @return - отсортированные пассажиры
 */
vector<Passenger> HeapSort(vector<Passenger> passengers);
