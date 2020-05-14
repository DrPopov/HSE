//
// Created by ypopov on 15.05.2020.
//
#include "../Headers/flightTime.h"
#include <iomanip>      // std::setw

// Конструктор
FlightTime::FlightTime(int day, int month, int year){
    FlightTime::set_day(day);
    FlightTime::set_month(month);
    FlightTime::set_year(year);
}

FlightTime::FlightTime(){
    FlightTime::set_day(1);
    FlightTime::set_month(1);
    FlightTime::set_year(1900);

};

int FlightTime::get_day() const{
    return FlightTime::day;
}
void FlightTime::set_day(int day) {
    FlightTime::day = day;

}

int FlightTime::get_month() const{
    return FlightTime::month;
}
void FlightTime::set_month(int month) {
    FlightTime::month = month;
}

int FlightTime::get_year() const{
    return FlightTime::year;
}
void FlightTime::set_year(int year){
    FlightTime::year = year;
}

ostream& operator<<(ostream& out,  const  FlightTime &data){
    out  << setw(2) <<  data.get_day() << " " << setw(2) <<   data.get_month() << " " << setw(4) << data.get_year();
    return out;
}


