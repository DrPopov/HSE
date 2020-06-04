//
// Created by ypopov on 15.05.2020.
//

#include "../Headers/fio.h"
#include "../Headers/flightTime.h"
#include "../Headers/passenger.h"
#include "../Headers/generator.h"
#include "../Headers/hash.h"



#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>



int Generator::random_flight_number() {
    //return Generator::flight_number = rand();
    return 1 + (rand() % static_cast<int>(10000 - 1 + 1));
}

int  Generator::random_seat_number(){
    //return Generator::seat_number = rand()%100;
    return  1 + (rand() % static_cast<int>(100 - 1 + 1));
}

Fio  Generator::random_fio(){
    string temp1;
    string temp2;
    string temp3;

    for(int j = 0; j <= rand()  % 9; j++ ){
        temp1.push_back(char('a' +   rand() % ('z' - 'a')));
    }

    for(int j = 0; j <= rand() % 9; j++ ){
        temp2.push_back(char('a'   + rand() % ('z' - 'a')));
    }

    for(int j = 0; j <= rand() % 9; j++ ){
        temp3.push_back(char('a'   + rand() % ('z' - 'a')));
    }

    //Generator::fio = Fio(temp1, temp2, temp3);
    return Fio(temp1, temp2, temp3);
}


FlightTime  Generator::random_flight_data(){
    int temp1=  1 + rand()%30;
    int temp2=  1 + rand()%12;
    int temp3 = rand()%2030;

    //Generator::flight_data = FlightTime(temp1, temp2, temp3);
    return FlightTime(temp1, temp2, temp3);

}


Passenger  Generator::generate_passenger(bool bad_hash_bool){
    Generator generator;
    Passenger passenger;

    passenger.set_fio(generator.random_fio());
    passenger.set_flight_data(generator.random_flight_data());
    passenger.set_flight_number(generator.random_flight_number());
    passenger.set_seat_number(generator.random_seat_number());

    //Passenger passenger = Passenger(Fio(generator.random_fio()), FlightTime(generator.random_flight_data()), generator.random_flight_number(), generator.random_seat_number(), bad_hash_bool);
    passenger.set_hash(get_hash(passenger.get_fio(), bad_hash_bool));
    /*
    if(bad_hash_bool){
        passenger.set_bad_hash(passenger.get_fio());
    } else{
        passenger.set_good_hash(passenger.get_fio());
    }
    */
    return passenger;

}

vector<Passenger> Generator::generate_passengers(int n, bool bad_hash_bool){
    vector<Passenger> people;

    for(int i = 0; i < n; i++){
        people.push_back(generate_passenger(bad_hash_bool));
    }

    return people;
}

ostream &operator << (ostream &out, const vector<Passenger> &passengers) {
    for(Passenger passenger:passengers){
        out << "Flight_data is: " <<  passenger.get_flight_data() << ". Flight_number is: " << passenger.get_flight_number() << ". FIO of passenger is: " << passenger.get_fio() << ". Seat_number is: " << passenger.get_seat_number() <<  endl;
    }

    return out;
}
