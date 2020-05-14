//
// Created by ypopov on 14.03.2020.
//
#pragma once
#include <string>
#include <iostream>


using namespace std;


/**
 * @brief - Класс, описывающий дату вылета
 *
 */
class FlightTime{
private:
    int day;
    int month;
    int year;

public:
    /**
     * @brief Конструктор с параметрами
     *
     * @param day День отлета
     * @param month Месяц отлета
     * @param year Год отлета
     */
    FlightTime(int day, int month, int year);
    FlightTime();//! Конструктор по умолчанию



    //Get and Set
    int get_day() const; //! Получить день отлета
    void set_day(int day); //! Установить день отлета

    int get_month() const; //! Получить месяц отлета
    void  set_month(int month);//! Установить месяц отлета

    int get_year() const;//! Получить год отлета
    void set_year(int year);//! Установить год отлета

    //-------------Operators overloading-------------------------------------------------------------------------------

    bool  operator == (FlightTime const& other){ //! Перегрузка оператора ==
        return this->year == other.year && this->month == other.month && this->day == other.day;
    }
    bool  operator != (FlightTime const& other){ //! Перегрузка оператора !=
        return !(this->operator == (other));
    }
    bool  operator <  (FlightTime const& other){ //! Перегрузка оператора <
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
    bool  operator >  (FlightTime const& other){ //! Перегрузка оператора >
        return !(this->operator < (other) || this->operator == (other));
    }
    bool  operator <= (FlightTime const& other){ //! Перегрузка оператора <=
        return this->operator < (other) || this->operator == (other);
    }
    bool  operator >= (FlightTime const& other){ //! Перегрузка оператора >=
        return this->operator > (other) || this->operator == (other);
    }

    friend ostream& operator << (ostream &out, const FlightTime &data); //! Перегрузка оператора вывода <<

    //---------------------------------------------------------------------------------------------------------------
};

