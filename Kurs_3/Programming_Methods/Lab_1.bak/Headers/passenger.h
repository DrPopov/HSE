//
// Created by ypopov on 13.03.2020.
//
#pragma once // защита от двойного подключения заголовочного файла

#include "../Headers/fio.h"
#include "flightTime.h"
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class Passenger{
private:


    int flight_number;
    int seat_number;
    FlightTime flight_data;
    Fio fio;


public:
    //Конструктор класса
    Passenger(FlightTime flight_data, int flight_number, Fio fio, int seat_number);
    Passenger();


    // Установка и получение даты рейса
    void set_flight_data(FlightTime data);
    FlightTime  get_flight_data() const;

    // Установка и получение номера рейса
    void set_flight_number(int num);
    int get_flight_number() const;

    // Установка и получение  ФИО
    void set_fio(Fio fio);
    Fio get_fio() const;

    // Установка и получение  номера места в самолете
    void set_seat_number(int seat);
    int get_seat_number() const;


    //-------Operators overloading------------------------------------------------------------------------------------------
    bool operator == (Passenger const& other){
        return this->flight_data == other.flight_data && this->flight_number == other.flight_number && this->fio == other.fio && this->seat_number == other.seat_number;
    }
    bool operator != (Passenger const& other){
        return !(this->operator==(other));
    }
    bool operator <  (Passenger const& other){
        if(this->flight_data < other.flight_data){return true;}
        else if(this->flight_data > other.flight_data){return false;}
        else if(this->flight_number < other.flight_number){return true;}
        else if(this->flight_number > other.flight_number){return false;}
        else if(this->fio < other.fio){return true;}
        else if(this->fio > other.fio){return false;}
        else return this->seat_number < other.seat_number;

    }
    bool operator >  (Passenger const& other){
        return !(this->operator < (other) || this->operator == (other));
    }
    bool operator <= (Passenger const& other){
        return this->operator < (other) || this->operator == (other);
    }
    bool operator >= (Passenger const& other){
        return this->operator > (other) || this->operator == (other);
    }
    friend ostream& operator << (ostream &out, const Passenger& passenger);
    //---------------------------------------------------------------------------------------------------------------------
};
