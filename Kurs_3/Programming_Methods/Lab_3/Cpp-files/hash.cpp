//
// Created by ypopov on 24.05.2020.
//
#include "../Headers/hash.h"


unsigned long long elf_hash(const Fio fio){
    unsigned long long hash = 0, x;
    string str = fio.get_first_name() + fio.get_second_name() + fio.get_father_name();
    //cout << "Elf" << endl;
    for (char c : str)
    {
        hash = (hash << 4) + static_cast<std::size_t>(c);
        if ((x = (hash & 0xF0000000)))
            hash ^= x >> 24;
        hash &= ~x;
    }
    return hash;
}


unsigned long long simple_hash(Fio fio){
    unsigned long long hash;
    string temp;
    string str = fio.get_first_name() + fio.get_second_name() + fio.get_father_name();

    for(auto i : str){
       temp += to_string((static_cast<unsigned int>(i)) % 99) ;
    }

    hash = stoull(temp);
    return hash;

}

unsigned long long get_hash(Fio key, bool Is_simple_hash){
    unsigned long long hash_value;
    if(Is_simple_hash){
        hash_value = simple_hash(key);
    } else{ hash_value = elf_hash(key);}
    return hash_value;
}



