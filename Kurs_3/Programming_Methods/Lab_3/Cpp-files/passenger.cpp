//
// Created by ypopov on 15.05.2020.
//

#include "../Headers/passenger.h"
#include <string>
#include <iomanip>      // std::setw


//Конструктор класса
Passenger::Passenger(FlightTime flight_data, int flight_number, Fio fio, int seat_number){
    Passenger::set_flight_data(flight_data);
    Passenger::set_flight_number(flight_number);
    Passenger::set_fio(fio);
    Passenger::set_seat_number(seat_number) ;
}

Passenger::Passenger(){};

// Установка и поулчение даты рейса
void Passenger::set_flight_data(FlightTime data){
    Passenger::flight_data = data;

}
FlightTime Passenger::get_flight_data() const {
    return Passenger::flight_data;
}

// Установка и получение номера рейса
void Passenger::set_flight_number(int num){
    Passenger::flight_number = num;
}
int Passenger::get_flight_number() const{
    return Passenger::flight_number;
}

// Установка и получние  ФИО
void Passenger::set_fio(Fio fio){
    Passenger::fio = fio;
}
Fio Passenger::get_fio()const {
    return Passenger::fio;
}

// Установка и получение номера места в самолете
void Passenger::set_seat_number(int seat){
    Passenger::seat_number = seat;
}
int  Passenger::get_seat_number() const {
    return seat_number;
}

ostream& operator<<(ostream& out, const Passenger& passenger){
    out << "Flight_data_is: "  <<  passenger.get_flight_data()   << "   Flight_number_is: " << setw(10) << left <<   passenger.get_flight_number() <<  "   Fio_is: "   <<  passenger.get_fio()    << " Seat_number_is: " <<setw(3) <<  left << passenger.get_seat_number() <<  endl;
    return out;
}


long long Passenger::hash_function_effective(string str,  int p = 31, int m = 31) {
    long long hash = 0;
    long long p_pow = 1;

    for(char i : str){
        hash += (i - 'a' + 1) * p_pow;
        p_pow *= p;
    }

    hash %= m;

    return hash;
}