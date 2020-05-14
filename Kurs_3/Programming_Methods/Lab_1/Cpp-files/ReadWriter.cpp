//
// Created by ypopov on 14.03.2020.
//

#include "../Headers/ReadWriter.h"


void ReadWriter::writeValues(string filename, vector<Passenger> passengers){

    fout.open(filename, ios::out | ios::trunc);



    if (!fout.is_open()) {
        cout << "Error opening file data_out.txt.\n";
        exit(EXIT_FAILURE);
    }


    for(int i = 0; i < passengers.size(); i ++){
        fout << passengers[i];
    }

    fout.close();

}

vector<Passenger> ReadWriter::readValues(string filename){

    /**
    * Count amount of strings in file
    */
    int counter = 0;
    int counter_2 = 0;
    for(char letter:filename){
        if(isdigit(letter)){
            counter_2 = counter;
            break;
        }
         counter++;
    }

    string  n_str = &filename[counter_2];
    int n = stoi(n_str);


    fin.open(filename);

    if (!fin.is_open()) {
        cout << "\nI'm creating a new file! It's file is " << filename << endl;
        Generator generator = Generator();
        auto passengers = generator.get_passengers(n);

        ReadWriter readWriter = ReadWriter();
        readWriter.writeValues(filename, passengers);

    }



    vector<Passenger> passengers{};

    string temp1, temp2, temp3, temp4, temp5, temp6, first_name, second_name, father_name;

    int day, month, year, flight_number,seat_number;



    for(int i = 0; i < n; i++ ){
        Passenger passenger = Passenger();
        fin >> temp1 >> day >> month >> year >> temp2 >>  flight_number >> temp3 >> temp4 >> first_name >> temp5 >> second_name >> temp6 >> father_name >> temp5 >> seat_number;
        passenger.set_flight_data(FlightTime(day, month, year));
        passenger.set_flight_number(flight_number);
        passenger.set_fio(Fio(first_name, second_name, father_name));
        passenger.set_seat_number(seat_number);
        passengers.push_back(passenger);
    }


    fin.close();
    return passengers;
}