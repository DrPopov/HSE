//
// Created by ypopov on 14.03.2020.
//
#include <string>
//#include <iostream>
#include "../Headers/fio.h"
#include <iomanip>      // std::setw



Fio::Fio(string second_name, string first_name, string father_name){
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
    ss << setw(10) << "hui" ;
    //auto outputstr = "First_name: " + person.get_first_name() + " Second_name: " + person.get_second_name() + " Third_name: " + person.get_father_name();
    out <<  "First_name: "  << setw(10) << person.get_first_name() << " Second_name: "  << setw(10) << person.get_second_name() << " Third_name: " << setw(10) << person.get_father_name();
    return out;

}



