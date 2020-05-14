//
// Created by ypopov on 15.05.2020.
//

#include "passenger.h"
#include "ReadWriter.h"
#include <chrono>

int linearSearch(string filename, Fio key){
    int elapsed_seconds;
    std::chrono::time_point<std::chrono::system_clock> start, end;


    ReadWriter readWriter = ReadWriter();

    vector<Passenger> passengers = readWriter.readValues(filename);

    start = std::chrono::system_clock::now();

    for(int i = 0; i < passengers.size(); i++){

        if(passengers[i].get_fio() == key){
            end = std::chrono::system_clock::now();

            elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds> (end-start).count();

            cout << "It was linear search! THe time is: " << elapsed_seconds << endl;

            cout << "We find him! This passenger is on board! \nHis number is "  <<  i << endl;
            cout << "Here it  is: " << passengers[i] << endl;



            return i;
        }

    }
    cout << "\n Ups, This passenger is NOT on board. Maybe next time" << endl;

    end = std::chrono::system_clock::now();

    elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds> (end-start).count();

    cout << "It was linear search! THe time is: " << elapsed_seconds << endl;
    return -1;
}

int binarySearch(string filename, Fio key){
    ReadWriter readWriter = ReadWriter();

    vector<Passenger> sorted_passengers = readWriter.readValues(filename);

    int elapsed_seconds;
    std::chrono::time_point<std::chrono::system_clock> start, end;


    int left_border = 0;
    int right_border = sorted_passengers.size() - 1;
    int middle = ( left_border + right_border ) / 2;
    bool flag = false;



    start = std::chrono::system_clock::now();


    while((left_border < right_border) && !flag){
        middle = ( left_border + right_border ) / 2;

        if(sorted_passengers[middle].get_fio() == key){flag = true;}
        if(sorted_passengers[middle].get_fio() > key){
            right_border = middle - 1;
        }
        else{left_border = middle + 1;}
    }


    if(flag){
        end = std::chrono::system_clock::now();

        elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds> (end-start).count();

        cout << "\nIt was binary search! THe time is: " << elapsed_seconds << endl;

        cout << "We find your passenger!\n His index is " << middle << endl;
        cout << "Here it is " << sorted_passengers[right_border] << endl;

        return middle;
    }else{
        end = std::chrono::system_clock::now();

        elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds> (end-start).count();

        cout << "\nIt was binary search! THe time is: " << elapsed_seconds << endl;

        cout << "\nUups, no such passenger on board:((";
        return -1;


    }
}