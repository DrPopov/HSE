//
// Created by ypopov on 15.05.2020.
//

#pragma once // защита от двойного подключения заголовочного файла
#include "fio.h"
#include "flightTime.h"
#include "passenger.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>



/**
 * @brief - Класс, описывающий генерацию одного пасажира или вектор пассажиров
 */
class Generator{
private:
    static int flight_number;
    int seat_number;
    FlightTime flight_data;
    Fio fio;


public:


    /**
     *
     * @return Случайную дату рейса
     */
    static int  random_flight_number();

    /**
     *
     * @return Случайное посадочное место
     */
    static int random_seat_number();

    /**
     *
     * @return Случайное ФИО пассажира
     */
    static Fio random_fio();

    /**
     *
     * @return Сучайную дату рейса
     */
    static FlightTime random_flight_data();

    /**
     *
     * @return  Случайного пассажира
     */
    static Passenger generate_passenger();

    /**
     *
     * @param n  Количество пассажиров
     * @return Вектор пассажиров
     */
    static vector<Passenger> get_passengers(int n);



    friend ostream& operator << (ostream &out, const vector<Passenger>& passengers);

};

