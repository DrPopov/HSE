//
// Created by ypopov on 24.05.2020.
//

#include "../Headers/passenger.h"
#include "../Headers/sorts.h"

void BiTree(vector<Passenger> &passengers, int n, int i){
    int max = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && passengers[l].get_fio() > passengers[max].get_fio())
        max = l;

    if (r < n && passengers[r].get_fio() > passengers[max].get_fio())
        max = r;

    if (max != i) {
        Passenger passenger = passengers[i];
        passengers[i] = passengers[max];
        passengers[max] = passenger;

        BiTree(passengers, n, max);
    }
}


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
