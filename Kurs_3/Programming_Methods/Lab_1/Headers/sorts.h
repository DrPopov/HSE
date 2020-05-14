//
// Created by ypopov on 05.04.2020.
//
#include "passenger.h"

/**
 *@brief - Алгритм сортировки пузыркем
 *
 *
 * @param passengers - пассажиры, которые должны быть отсортированы
 * @return - отсортированные пассажиры
 */
vector<Passenger> BubbleSort(vector<Passenger> passengers) {
    for(int i = 1; i < passengers.size(); i++){
        for(int j = 0; j < passengers.size() - i; j++){
            if(passengers[j + 1] < passengers[j]){
                swap(passengers[j], passengers[j + 1]);
            }

        }

    }
    return passengers;

}

/**
 *@brief - Алгритм сортировки методом простых вставок
 *
 *
 * @param passengers - пассажиры, которые должны быть отсортированы
 * @return - отсортированные пассажиры
 */
vector<Passenger> InsertionSort(vector<Passenger> passengers){
    //vector<Passenger> out; //sorted passengers
    Passenger  temp; // временная переменная для хранения значения элемента сортируемого массива

    for (int i = 0; i < passengers.size(); ++i)
    {
        temp = passengers[i];
        int j = i;
        while (j > 0 && temp < passengers[j - 1])
        {
            passengers[j] = passengers[j - 1];
            j--;
        }
        passengers[j] = temp;
    }

    return passengers;
}

/**
 *@brief - Метод построения бинарного дерева
 *
 * @param passengers - пассажиры, которые должны быть отсортированы
 * @param n - размер кучи
 * @param i - корень
 */
void BiTree(vector<Passenger> &passengers, int n, int i){
    int max = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && passengers[l] > passengers[max])
        max = l;

    if (r < n && passengers[r] > passengers[max])
        max = r;

    if (max != i) {
        Passenger passenger = passengers[i];
        passengers[i] = passengers[max];
        passengers[max] = passenger;

        BiTree(passengers, n, max);
    }
}

/**
 *@brief - Алгритм пирамидальной сортировки
 *
 *
 * @param passengers - пассажиры, которые должны быть отсортированы
 * @return - отсортированные пассажиры
 */
vector<Passenger> HeapSort(vector<Passenger> passengers){
    for (int i = passengers.size() / 2 - 1; i >= 0; --i)
        BiTree(passengers, passengers.size(), i);

    for (int i = passengers.size() - 1; i >= 0; --i)
    {
        Passenger passenger = passengers[0];
        passengers[0] = passengers[i];
        passengers[i] = passenger;

        BiTree(passengers, i, 0);
    }
    return passengers;
}
/*
 * Реалищация сортировок вставить в маин при необзодимости
 *
 *
 *
 *     for(int i:temp1_2){
        amount_of_passengers = i;


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
