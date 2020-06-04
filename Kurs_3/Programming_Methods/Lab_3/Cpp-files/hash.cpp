//
// Created by ypopov on 24.05.2020.
//
#include "../Headers/hash.h"


std::size_t bad_hash(Fio fio){

    string temp;
    string str = fio.get_first_name() + fio.get_second_name() + fio.get_father_name();

    std::size_t hash = 0;
    for (char letter : str)
        hash += static_cast<uint32_t>(letter);
    return hash;

}

std::size_t good_hash(const Fio fio){
    string str = fio.get_first_name() + fio.get_second_name() + fio.get_father_name();

    std::size_t hash = 0;
    for (std::size_t i = 0; i < str.length(); ++i)
        hash += (i * static_cast<std::size_t>(str[i]) - hash * 11) & 0xFFFFFFFF;
    return hash;
}




std::size_t get_hash(Fio key, bool Is_simple_hash){
    std::size_t hash_value;
    if(Is_simple_hash){
        hash_value = bad_hash(key);
    } else{hash_value = good_hash(key);}
    return hash_value;
}



