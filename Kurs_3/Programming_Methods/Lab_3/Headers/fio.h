//
// Created by ypopov on 15.05.2020.
//
#pragma once

#include <string>
using namespace std;

/**
 * @brief - Класс, описывающий ФИО человека
 */
class Fio{
private:

    string first_name;
    string second_name;
    string father_name;
    string fio_for_hash = first_name + ' ' + second_name + ' '+ father_name;


public:
    /**
     * @brief Конструктор с параметрами
     *
     * @param second_name  Фамилия
     * @param first_name Имя
     * @param father_name Отчество
     */
    Fio(string second_name, string first_name, string father_name);
    Fio(); //! Конструктор по умаолчаниб


    string get_first_name() const; //! Получить имя
    void set_first_name(string first_name); //! Установить имя

    string get_second_name() const; //! Получить фамилию
    void set_second_name(string second_name); //! Установить фамилию

    string get_father_name() const; //! Получить отчество
    void set_father_name(string father_name);  //! Установить отчество

    string get_fio_for_hash() const; //! Получить, склеенное ФИО, от которого в дальнейшем будется браться хеш

    //---------Operators overloading------------------------------------------------------------------------------------

    bool operator == (Fio const& other){ //! Перегрузка оператора ==
        return this->second_name == other.second_name && this->first_name == other.first_name &&
               this->father_name == other.father_name;
    }
    bool operator != (Fio const& other) {  //! Перегрузка оператора !=
        return !(this->operator == (other));
    }
    bool operator <  (Fio const& other){ //! Перегрузка оператора <
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
    bool operator >  (Fio const& other){ //! Перегрузка оператора >
        return !(this->operator < (other) || this->operator == (other));
    }
    bool operator <= (Fio const& other) { //! Перегрузка оператора <=
        return this->operator < (other) || this->operator == (other);
    }
    bool operator >= (Fio const& other){ //! Перегрузка оператора >=
        return this->operator > (other) || this->operator == (other);
    }
    //----------------------------------------------------------------------------------------------------------------------

    friend ostream& operator << (ostream &out, const Fio&);  //! Перегрузка оператора вывода <<


};


