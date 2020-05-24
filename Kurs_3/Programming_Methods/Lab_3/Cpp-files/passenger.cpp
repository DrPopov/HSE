//
// Created by ypopov on 15.05.2020.
//

#include "../Headers/passenger.h"
#include "../Headers/hash.h"
#include <string>
#include <iomanip>      // std::setw


//Конструктор класса
Passenger::Passenger(Fio fio, FlightTime flight_data, int flight_number, int seat_number,  bool bad_hash_bool) {
    Passenger::set_flight_data(flight_data);
    Passenger::set_flight_number(flight_number);
    Passenger::set_fio(fio);
    Passenger::set_seat_number(seat_number) ;

    if(bad_hash_bool){
        Passenger::set_bad_hash(fio);
    }else{
        Passenger::set_good_hash(fio);
    }


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

//Установка хорошего хеша ФИО
void Passenger::set_good_hash(Fio fio) {
    Passenger::hash = good_hash(fio);
}

//Установка плохого хеша ФИО
void Passenger::set_bad_hash(Fio fio) {
    Passenger::hash = bad_hash(fio);
}

void Passenger::set_hash(unsigned long long hash) {
    Passenger::hash = hash;
}
//Получение хеша ФИО
unsigned long long Passenger::get_hash() const{
    return Passenger::hash;
}

ostream& operator<<(ostream& out, const Passenger& passenger){
    //out << "Flight_data_is: "  <<  passenger.get_flight_data()   << "   Flight_number_is: " << setw(10) << left <<   passenger.get_flight_number() <<  "   Fio_is: "   <<  passenger.get_fio()    << " Seat_number_is: " <<setw(3) <<  left << passenger.get_seat_number() <<  endl;
    out << "Fio_is: "   <<  passenger.get_fio()  << "Flight_data_is: "  <<  passenger.get_flight_data()   << "   Flight_number_is: " << setw(10) << left <<   passenger.get_flight_number() <<   " Seat_number_is: " <<setw(3) <<  left << passenger.get_seat_number()  << " Fio's_hash_is: " << passenger.get_hash() <<   endl;
    return out;
}



