#include <iostream>
#include <string>
//#include "Headers/passenger.h"
#include "Headers/sorts.h"
#include "Headers/ReadWriter.h"
#include <chrono>
#include "Headers/searches.h"
#include <fstream>

using namespace std;

void CreateFile(int amount_of_passengers){
    ReadWriter readWriter = ReadWriter();
    Generator generator = Generator();
    auto passengers = generator.get_passengers(amount_of_passengers);

    readWriter.writeValues("../output/data" + to_string(amount_of_passengers), passengers);

}

bool IsArraySorted(vector<Passenger> mass){
    for(int i = 1; i < mass.size(); i++){
        if(mass[i - 1] <= mass[i]){
            continue;
        }else{
            cout << "Passengers aren't sorted";
            return false;
        }
    }
    cout << "Passengers are sorted!!!" << endl;
    return true;
}

int main(){

    srand(time(0));



    //CreateFile(10000);
    ofstream fout;
    fout.open("../results.txt",  ios::out  | ios_base::app);
    fout << "------------------Final results: ----------------------------";


    //Generator generator = Generator();

    int amount_of_passengers;
    int method;

    /**
     * Choose amount of passengers:
     * "Size options:
     *               10.000
     *               50.000
     *              100.000
     *              150.000
     *              200.000
     *              250.000
     *              500.000
     *              750.000
     *            1.000.000
     */
    vector<int> temp1 = {10000, 50000, 100000, 150000, 200000, 250000, 500000, 75000, 1000000};
    //vector<int> temp1_1 = {500000, 750000, 1000000};
    vector<int> temp1_2 = {10};



    /**
    *Choose method of sorting
    * Methods:
    *      1: bubble,
    *      2: insert,
    *      3: heap
    */
    vector<int> temp2 =  {1, 2, 3};

    int elapsed_seconds;
    std::chrono::time_point<std::chrono::system_clock> start, end;


/*

    for(int i:temp1_2){
        amount_of_passengers = i;

        /**
         * Read from correct file

        ReadWriter readWriter = ReadWriter();

        auto passengers = readWriter.readValues("../output/data_" + to_string(amount_of_passengers));



        for(int j:temp2){
            //auto passengers = generator.get_passengers(amount_of_passengers);

            //ReadWriter readwrite = ReadWriter();

            method = j;
            vector<Passenger> sorted;
            switch(method){
                case(1):
                    start = std::chrono::system_clock::now();

                    sorted = BubbleSort(passengers);

                    end = std::chrono::system_clock::now();

                    IsArraySorted(sorted);
                    readWriter.writeValues("../sortedArrays/output_bubble_" + to_string(amount_of_passengers), sorted);



                    elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds> (end-start).count();

                    fout << "It was BubbleSort! \n"
                            "The amount of passengers is: " << amount_of_passengers  << "\n" <<
                         "Sorting time is:  " << elapsed_seconds << "s\n" << "\n";

                    cout << "It was BubbleSort! \n"
                            "The amount of passengers is: " << amount_of_passengers  << "\n" <<
                         "Sorting time is:  " << elapsed_seconds << "s\n" << "\n";

                    //cout << "BubbleSort finished!" << endl;

                    break;

                case(2):
                    start = std::chrono::system_clock::now();

                    sorted = InsertionSort(passengers);

                    end = std::chrono::system_clock::now();

                    IsArraySorted(sorted);
                    readWriter.writeValues("../sortedArrays/output_insert_" + to_string(amount_of_passengers), sorted);



                    elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds> (end-start).count();


                    fout << "It was InsertSort! \n"
                            "The amount of passengers is: " << amount_of_passengers  << "\n" <<
                         "Sorting time is:  " << elapsed_seconds << "s\n" << "\n";

                    cout << "It was InsertSort! \n"
                            "The amount of passengers is: " << amount_of_passengers  << "\n" <<
                         "Sorting time is:  " << elapsed_seconds << "s\n" << "\n";

                    //cout << "InsertSort finished" << endl;

                    break;
                case(3):
                    start = std::chrono::system_clock::now();

                    sorted = HeapSort(passengers);

                    end = std::chrono::system_clock::now();

                    IsArraySorted(sorted);
                    readWriter.writeValues("../sortedArrays/output_heap_" + to_string(amount_of_passengers), sorted);



                    elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds> (end-start).count();

                    fout << "It was  HeapSort! \n"
                            "The amount of passengers is: " << amount_of_passengers  << "\n" <<
                         "Sorting time is:  " << elapsed_seconds << "s\n" << "\n";

                    cout << "It was  HeapSort! \n"
                            "The amount of passengers is: " << amount_of_passengers  << "\n" <<
                         "Sorting time is:  " << elapsed_seconds << "s\n" << "\n";

                    //cout << "HeapSort finished" << endl;

                    break;
                default:
                    break;
            }

        }
    }

*/

/*
 *!!!               MANUAL INPUT             !!!
 *
    cout << "Print amount of passengers. \n"
            "Size options:\n"
            "              10.000,\n"
            "              50.000,\n"
            "             100.000,\n"
            "             150.000,\n"
            "             200.000,\n"
            "             250.000,\n"
            "             500.000,\n"
            "             750.000,\n"
            "           1.000.000 \n";
    cin >> amount_of_passengers;


    cout << "Print what method you want.\n"
            "Methods:\n"
            "      1: bubble,\n"
            "      2: insert,\n"
            "      3: heap   \n";

    cin >> method;

    amount_of_passengers = 10000;



    ReadWriter readWriter = ReadWriter();

    auto passengers = readWriter.readValues("../output/data10000.txt", 10000);
*/
    /**
     * Generator works
     */
    //Generator generator = Generator();
    //auto passengers = generator.get_passengers(10);


    /**
     * Manual array
     */
     vector<Passenger> passengers{};
     /*

     Passenger passenger1 = Passenger(FlightTime(1, 1, 1),  11111, Fio("a", "a", "a"), 10 );
     Passenger passenger2 = Passenger(FlightTime(2, 2, 2),  22222, Fio("b", "b", "b"), 10 );
     Passenger passenger3 = Passenger(FlightTime(1, 1, 1),  33333, Fio("c", "c", "c"), 10 );
     Passenger passenger4 = Passenger(FlightTime(1, 1, 1),  11111, Fio("a", "a", "a"), 10 );

     passengers.push_back(passenger1);
     passengers.push_back(passenger2);
     passengers.push_back(passenger3);
     passengers.push_back(passenger4);
    */



     int k = linearSearch("../output/data_10", Fio("c", "c", "c"));
     cout << k;


    ReadWriter readWriter = ReadWriter();

    //passengers = readWriter.readValues("../output/data_500");
    //auto sorted = HeapSort(passengers);


    //IsArraySorted(sorted);
    //readWriter.writeValues("../sortedArrays/output_heap_" + to_string(passengers.size()), sorted);

     int bin = binarySearch("../sortedArrays/output_heap_500", Fio("c", "c","c"));

     cout << bin;





     return 0;
}

