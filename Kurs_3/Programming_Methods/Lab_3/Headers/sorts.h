//
// Created by ypopov on 15.05.2020.
//
#include "passenger.h"

/**
 *@brief - Алгритм сортировки пузыркем
 *
 *
 * @param passengers - пассажиры, которые должны быть отсортированы
 * @return - отсортированные пассажиры
 */
vector<Passenger> BubbleSort(vector<Passenger> passengers) {
    for(int i = 1; i < passengers.size(); i++){
        for(int j = 0; j < passengers.size() - i; j++){
            if(passengers[j + 1] < passengers[j]){
                swap(passengers[j], passengers[j + 1]);
            }

        }

    }
    return passengers;

}

/**
 *@brief - Алгритм сортировки методом простых вставок
 *
 *
 * @param passengers - пассажиры, которые должны быть отсортированы
 * @return - отсортированные пассажиры
 */
vector<Passenger> InsertionSort(vector<Passenger> passengers){
    //vector<Passenger> out; //sorted passengers
    Passenger  temp; // временная переменная для хранения значения элемента сортируемого массива

    for (int i = 0; i < passengers.size(); ++i)
    {
        temp = passengers[i];
        int j = i;
        while (j > 0 && temp < passengers[j - 1])
        {
            passengers[j] = passengers[j - 1];
            j--;
        }
        passengers[j] = temp;
    }

    return passengers;
}

/**
 *@brief - Метод построения бинарного дерева
 *
 * @param passengers - пассажиры, которые должны быть отсортированы
 * @param n - размер кучи
 * @param i - корень
 */
void BiTree(vector<Passenger> &passengers, int n, int i){
    int max = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && passengers[l] > passengers[max])
        max = l;

    if (r < n && passengers[r] > passengers[max])
        max = r;

    if (max != i) {
        Passenger passenger = passengers[i];
        passengers[i] = passengers[max];
        passengers[max] = passenger;

        BiTree(passengers, n, max);
    }
}

/**
 *@brief - Алгритм пирамидальной сортировки
 *
 *
 * @param passengers - пассажиры, которые должны быть отсортированы
 * @return - отсортированные пассажиры
 */
vector<Passenger> HeapSort(vector<Passenger> passengers){
    for (int i = passengers.size() / 2 - 1; i >= 0; --i)
        BiTree(passengers, passengers.size(), i);

    for (int i = passengers.size() - 1; i >= 0; --i)
    {
        Passenger passenger = passengers[0];
        passengers[0] = passengers[i];
        passengers[i] = passenger;

        BiTree(passengers, i, 0);
    }
    return passengers;
}

