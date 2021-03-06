//
// Created by ypopov on 15.05.2020.
//
#include <string>
#include "../Headers/fio.h"
#include <iomanip>      // std::setw



Fio::Fio( string first_name,string second_name, string father_name){
    Fio::set_second_name(second_name);
    Fio::set_first_name(first_name);
    Fio::set_father_name(father_name);
}

Fio::Fio(){};



string Fio::get_first_name() const{
    return Fio::first_name;
}

string Fio::get_second_name() const{
    return Fio::second_name;
}

string Fio::get_father_name() const{
    return Fio::father_name;
}

void Fio::set_first_name(string first_name) {
    Fio::first_name = first_name;

}

void Fio::set_second_name(string second_name) {
    Fio::second_name = second_name;

}
void Fio::set_father_name(string father_name) {
    Fio::father_name = father_name;

}


ostream& operator<<(ostream& out, const Fio& person) {
    stringstream ss;
    //auto outputstr = "First_name: " + person.get_first_name() + " Second_name: " + person.get_second_name() + " Third_name: " + person.get_father_name();
    out <<  "First_name: "  << setw(15)  << left << person.get_first_name() << " Second_name: "  << setw(15) << left << person.get_second_name() << " Third_name: " << setw(15)  << left << person.get_father_name();
    return out;

}