//
// Created by ypopov on 05.04.2020.
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




class Generator{
private:
    static int flight_number;
    int seat_number;
    FlightTime flight_data;
    Fio fio;


public:


    // Установка и получение даты рейса
    static int  random_flight_number();

    // Установка и получение номера рейса
    static int random_seat_number();

    // Установка и получение  ФИО
    static Fio random_fio();

    // Установка и получение  номера места в самолете
    static FlightTime random_flight_data();

    /**
     *
     * @return random passenger
     */
    static Passenger generate_passenger();

    /**
     *
     * @param n - amount of passengers
     * @return passengers
     */
    static vector<Passenger> get_passengers(int n);



    friend ostream& operator << (ostream &out, const vector<Passenger>& passengers);

};

