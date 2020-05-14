//
// Created by ypopov on 14.03.2020.
//

#pragma once
//#include "date.h"

#include <string>
using namespace std;

class Fio{
private:

    string first_name;
    string second_name;
    string father_name;


public:
    //Constructor
    Fio(string second_name, string first_name, string father_name);
    Fio();


    string get_first_name() const;
    void set_first_name(string first_name);

    string get_second_name() const;
    void set_second_name(string second_name);

    string get_father_name() const;
    void set_father_name(string father_name);

    //---------Operators overloading------------------------------------------------------------------------------------

    bool operator == (Fio const& other){
        return this->second_name == other.second_name && this->first_name == other.first_name &&
               this->father_name == other.father_name;
    }
    bool operator != (Fio const& other) {
        return !(this->operator == (other));
    }
    bool operator <  (Fio const& other){
        if(this->second_name < other.second_name) {
            return true;
        }else if(this->second_name > other.second_name) {
            return false;
        }else if(this-> first_name < other.first_name){
            return true;
        }else if(this-> first_name > other.first_name) {
            return false;
        }else if(this-> father_name < other.father_name) {
            return true;
        }return false;

    }
    bool operator >  (Fio const& other){
        return !(this->operator < (other) || this->operator == (other));
    }
    bool operator <= (Fio const& other) {
        return this->operator < (other) || this->operator == (other);
    }
    bool operator >= (Fio const& other){
        return this->operator > (other) || this->operator == (other);
    }
    //----------------------------------------------------------------------------------------------------------------------

    friend ostream& operator << (ostream &out, const Fio&);


};


