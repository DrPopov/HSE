//
// Created by ypopov on 31.05.2020.
//

//
// Created by ypopov on 05.04.2020.
//

#include <vector>
#include <cstdint>
#include "../Headers/sort.h"

using namespace std;
/**
 *@brief - Метод построения бинарного дерева
 *
 * @param passengers - пассажиры, которые должны быть отсортированы
 * @param n - размер кучи
 * @param i - корень
 */
void BiTree(uint32_t sample[], int n, int i){
    int max = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && sample[l] > sample[max])
        max = l;

    if (r < n && sample[r] > sample[max])
        max = r;

    if (max != i) {
        auto temp = sample[i];
        sample[i] = sample[max];
        sample[max] = temp;

        BiTree(sample, n, max);
    }
}

/**
 *@brief - Алгритм пирамидальной сортировки
 *
 *
 * @param passengers - пассажиры, которые должны быть отсортированы
 * @return - отсортированные пассажиры
 */
uint32_t HeapSort(uint32_t sample[], int leng){
    for (int i = leng / 2 - 1; i >= 0; --i)
        BiTree(sample, leng, i);

    for (int i = leng - 1; i >= 0; --i)
    {
        auto temp = sample[0];
        sample[0] = sample[i];
        sample[i] = temp;

        BiTree(sample, i, 0);
    }
    //return sample;
}
