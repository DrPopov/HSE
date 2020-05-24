//
// Created by ypopov on 24.05.2020.
//

#include "../Headers/hashTable.h"
#include "../Headers/hash.h"
#include <map>

//using namespace std;

//template <typename K, typename V> HashNode;

hashTable::hashTable() {}


void hashTable::make_hashTable(map<unsigned long long, vector<Passenger>> &hash_table, vector<Passenger> passengers, bool bad_hash_bool) {
    int collision;

    for(auto passenger : passengers){
        int count =0; //Кол-во записей с таким хешем
        unsigned long long hash_value = get_hash(Fio(passenger.get_fio()), bad_hash_bool);

        auto it = hash_table.find(hash_value);
        if(it != hash_table.end()) {
            for(int j = 0; j < hash_table[hash_value].size(); j++){
                if(hash_table[hash_value][j].get_fio() == passenger.get_fio()){
                    count++;
                    hash_table[hash_value].push_back(passenger);
                    break;
                }
            }

            if(count == 0){
                hash_table[hash_value].push_back(passenger);
                collision++;
            }



        } else{ // Если такого хеша не нашел, значит добавляем новую запись
            hash_table.emplace(hash_value, vector<Passenger>{passenger});
        }

    }
}

void hashTable::make_hashTable(unordered_map<unsigned long long int, vector<Passenger>> &hash_table, vector<Passenger> passengers, bool bad_hash_bool) {
    int collision;

    for(auto passenger : passengers){
        int count =0; //Кол-во записей с таким хешем
        unsigned long long hash_value = get_hash(Fio(passenger.get_fio()), bad_hash_bool);

        auto it = hash_table.find(hash_value);
        if(it != hash_table.end()) {
            for(int j = 0; j < hash_table[hash_value].size(); j++){
                if(hash_table[hash_value][j].get_fio() == passenger.get_fio()){
                    count++;
                    hash_table[hash_value].push_back(passenger);
                    break;
                }
            }

            if(count == 0){
                hash_table[hash_value].push_back(passenger);
                collision++;
            }



        } else{ // Если такого хеша не нашел, значит добавляем новую запись
            hash_table.emplace(hash_value, vector<Passenger>{passenger});
        }

    }
}

void hashTable::displayHash(map<unsigned long long, vector<Passenger>> hash_table) {
    map<unsigned long long, vector<Passenger>>::iterator it;

    for(it=hash_table.begin(); it!= hash_table.end(); it++){
        cout << it->first << " ";

        for(int k = 0; k < it-> second.size(); k++){
            cout << it->second[k].get_fio() << "  ||  ";
        }

        cout << endl;
    }
}

void hashTable::displayHash(unordered_map<unsigned long long, vector<Passenger>> hash_table) {
    unordered_map<unsigned long long, vector<Passenger>>::iterator it;

    for(it=hash_table.begin(); it!= hash_table.end(); it++){
        cout << it->first << " ";

        for(int k = 0; k < it-> second.size(); k++){
            cout << it->second[k].get_fio() << "  ||  ";
        }

        cout << endl;
    }
}

vector<Passenger>hashTable::find(map<unsigned long long int, vector<Passenger>> &hash_table, const Fio &key, bool bad_hash_bool) {
    vector<Passenger> found_passengers;

    unsigned long long hash_value = get_hash(key, bad_hash_bool);
    auto it = hash_table.find(hash_value);

    vector<Passenger> this_hash = hash_table[hash_value];

    if(it != hash_table.end()){ //  Если что-то нашел
        for(int k = 0; k < this_hash.size(); k++){
            if(this_hash[k].get_fio() == key){
                found_passengers.push_back(this_hash[k]);
            }
        }
    }

    if(found_passengers.size() == 0){
        cout << "Sorry, we didn't find any Passengers in map HashTable:(\n\n\n";
    }else{
        cout << "It was search in unordered_map! Here are they:\n";
        for(auto i : found_passengers){cout << i;}
    }

    return found_passengers;

}

vector<Passenger>hashTable::find(unordered_map<unsigned long long int, vector<Passenger>> &hash_table, const Fio &key, bool bad_hash_bool) {
    vector<Passenger> found_passengers;

    unsigned long long hash_value = get_hash(key, bad_hash_bool);
    auto it = hash_table.find(hash_value);

    vector<Passenger> this_hash = hash_table[hash_value];

    if(it != hash_table.end()){ //  Если что-то нашел
        for(int k = 0; k < this_hash.size(); k++){
            if(this_hash[k].get_fio() == key){
                found_passengers.push_back(this_hash[k]);
            }
        }
    }

    if(found_passengers.size() == 0){
        cout << "Sorry, we didn't find any Passengers in unordered_map HashTable:(\n\n\n";
    }else{
        cout << "It was search in unordered_map! Here are they:\n";
        for(auto i : found_passengers){cout << i;}
    }
    return found_passengers;
}








