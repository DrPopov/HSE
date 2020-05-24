//
// Created by ypopov on 24.05.2020.
//

#include "../Headers/passenger.h"
#include "../Headers/searches.h"
#include "../Headers/hash.h"
#include <map>

vector<Passenger> linearSearch(const vector<Passenger>& passengers, const Fio& key){
    vector<Passenger> found_passengers;

    for(auto & passenger : passengers){

        if(passenger.get_fio() == key){
            found_passengers.push_back(passenger);
        }

    }

    // Вывод найденых пассажиров
    cout << "It was linear search. Here are your passengers: \n";
    for(auto & passenger : found_passengers){
        cout << passenger;
    }

    return found_passengers;
}

vector<Passenger> binarySearch(vector<Passenger> sorted_passengers, const Fio& key){

    vector<Passenger> found_passengers;

    int left_border = 0;
    int right_border = sorted_passengers.size() - 1;
    int middle = ( left_border + right_border ) / 2;
    bool flag = false;

    // Поиск певрого найденого элемента
    while((left_border < right_border) && !flag){
        middle = ( left_border + right_border ) / 2;

        if(sorted_passengers[middle].get_fio() == key){flag = true;found_passengers.push_back(sorted_passengers[middle]);}
        if(sorted_passengers[middle].get_fio() > key){
            right_border = middle - 1;
        }
        else{left_border = middle + 1;}
    }

    // При условиии, что найден хотя бы один элемент: начиная с середины идем влево до левой границы
    int ind = middle;
    if(flag){
        while(sorted_passengers[ind - 1].get_fio() == sorted_passengers[ind].get_fio()){
            found_passengers.push_back(sorted_passengers[ind - 1]);
            ind--;
            if(ind == 0){break;}
        }
    }

    //При условиии, что найден хотя бы один элемент: начиная с середины идем вправо до правой границы
    int ind_2 = middle;
    if(flag){
        while(sorted_passengers[ind_2 + 1].get_fio() == sorted_passengers[ind_2].get_fio()){
            found_passengers.push_back(sorted_passengers[ind_2 + 1]);
            ind_2++;
            if(ind_2 == sorted_passengers.size() - 1){break;}
        }
    }

    // Вывод найденных пассажиров
    cout << "\nIt was binary search with presorted array! Here are you passengers: \n";
    for(auto i : found_passengers){
        cout << i;
    }
    return found_passengers;
}

/*
vector<Passenger> hash_search(map<unsigned int, vector<Passenger>> hash_table, const Fio& key){
    unsigned int hash_value = get_hash(key, )
}
 */