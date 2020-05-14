//
// Created by ypopov on 14.03.2020.
//
#pragma once
#include <string>
#include <iostream>


using namespace std;


class FlightTime{
private:
    int day;
    int month;
    int year;

public:
    //Конструктор
    FlightTime(int day, int month, int year);
    FlightTime();



    //Get and Set
    int get_day() const;
    void set_day(int day);

    int get_month() const;
    void  set_month(int month);

    int get_year() const;
    void set_year(int year);

    //-------------Operators overloading-------------------------------------------------------------------------------

    bool  operator == (FlightTime const& other){
        return this->year == other.year && this->month == other.month && this->day == other.day;
    }
    bool  operator != (FlightTime const& other){
        return !(this->operator == (other));
    }
    bool  operator <  (FlightTime const& other){
        if(this->year < other.year) {
            return true;
        }else if(this->year > other.year) {
            return false;
        //--один и тот же год
        }else if(this->month < other.month){
            return true;
        }else if(this->month > other.month) {
            return false;
         //--один и тот же месяц
        }else if(this->day < other.day) {
            return true;
        }return false;

    }
    bool  operator >  (FlightTime const& other){
        return !(this->operator < (other) || this->operator == (other));
    }
    bool  operator <= (FlightTime const& other){
        return this->operator < (other) || this->operator == (other);
    }
    bool  operator >= (FlightTime const& other){
        return this->operator > (other) || this->operator == (other);
    }

    friend ostream& operator << (ostream &out, const FlightTime &data);

    //---------------------------------------------------------------------------------------------------------------
};

