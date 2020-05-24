//
// Created by ypopov on 24.05.2020.
//
#include "../Headers/hash.h"


unsigned long long bad_hash(Fio fio){
    unsigned int hash = 0;
    string str = fio.get_first_name() + fio.get_second_name() + fio.get_father_name();

    for(int i = 0; i < str.size(); i++ ){
        hash += static_cast<unsigned int>(str[i]) * 10^i ;
    }

    return hash;
}


unsigned long long good_hash(Fio fio){
    unsigned long long hash;
    string temp;
    string str = fio.get_first_name() + fio.get_second_name() + fio.get_father_name();

    for(auto i : str){
       temp += to_string(static_cast<unsigned int>(i) % 99) ;
    }

    hash = stoull(temp);
    return hash;

}


unsigned long long get_hash(Fio key, bool bad_hash_bool){
    unsigned int hash_value;
    if(bad_hash_bool){
        hash_value = bad_hash(key);
    } else{ hash_value = good_hash(key);}
    return hash_value;
}



