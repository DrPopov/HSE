//
// Created by ypopov on 15.05.2020.
//
#pragma once // защита от двойного подключения заголовочного файла

#include "../Headers/fio.h"
#include "../Headers/flightTime.h"
#include <string>
#include <vector>
#include <ctime>

using namespace std;


/**
 * @brief - Класс, описывающий одного пассажира
 */
class Passenger{
private:


    int flight_number;
    int seat_number;
    FlightTime flight_data;
    Fio fio;
    long long hash;

    const int p = 31;






public:
    /**
     *
     * @param flight_data  Даты рейса
     * @param flight_number Номер рейса
     * @param fio ФИО пассажира
     * @param seat_number Посадочное место
     */
    Passenger(FlightTime flight_data, int flight_number, Fio fio, int seat_number);
    Passenger(); //! Конструктор по умолчанию


    // Установка и получение даты рейса
    void set_flight_data(FlightTime data); //! Получение  даты рейса пассажира
    FlightTime  get_flight_data() const; //! Установка даты рейса пассажира

    // Установка и получение номера рейса
    void set_flight_number(int num); //! Получение номера рейса пассажира
    int get_flight_number() const; //! Установка номера рейса пассажира

    // Установка и получение  ФИО
    void set_fio(Fio fio); //! Получение ФИО пассажира
    Fio get_fio() const; //! Установка ФИО пассажира

    // Установка и получение  номера места в самолете
    void set_seat_number(int seat); //! Получение посадочного места
    int get_seat_number() const; //! Установка посадочного места


    //-------Operators overloading------------------------------------------------------------------------------------------
    bool operator == (Passenger const& other){ //! Перегрузка оператора ==
        return this->flight_data == other.flight_data && this->flight_number == other.flight_number && this->fio == other.fio && this->seat_number == other.seat_number;
    }
    bool operator != (Passenger const& other){ //! Перегрузка оператора !=
        return !(this->operator==(other));
    }
    bool operator <  (Passenger const& other){ //! Перегрузка оператора <
        if(this->flight_data < other.flight_data){return true;}
        else if(this->flight_data > other.flight_data){return false;}
        else if(this->flight_number < other.flight_number){return true;}
        else if(this->flight_number > other.flight_number){return false;}
        else if(this->fio < other.fio){return true;}
        else if(this->fio > other.fio){return false;}
        else return this->seat_number < other.seat_number;

    }
    bool operator >  (Passenger const& other){ //! Перегрузка оператора >
        return !(this->operator < (other) || this->operator == (other));
    }
    bool operator <= (Passenger const& other){ //! Перегрузка оператора <=
        return this->operator < (other) || this->operator == (other);
    }
    bool operator >= (Passenger const& other){ //! Перегрузка оператора >=
        return this->operator > (other) || this->operator == (other);
    }
    friend ostream& operator << (ostream &out, const Passenger& passenger); //! Перегрузка оператора вывода <<
    //---------------------------------------------------------------------------------------------------------------------

    /**
    *
    *  h(S)  =  S[0]  +  S[1] * P  +  S[2] * P^2  +  S[3] * P^3  +  ...  +  S[N] * P^N
    */
    long long hash_function_effective(string str, int p, int m);
};

