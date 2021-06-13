#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>
#include "list.h"
#include "QS.h"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 3)
    {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;

    ifstream in(argv[1]);

    if (!in)
    {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    cout << "Output file: " << argv[2] << endl;

    ofstream out(argv[2]);

    if (!out)
    {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    }
    QS<int> mySort;
    list<int> numList;
    string line, command;
    string item1;
    int numVar;
    while (getline(in, line))
    {
        if (line.size() == 0) continue;
        istringstream iss(line);
        iss >> command;

        if (command == "QuickSort")
        {
            iss >> item1;
            numVar = stoi(item1);
            out << command << " " << item1 << " ";
            mySort.clear();
            if (!mySort.setMaxCapacity(numVar))
            {
                out << "Error" << endl;
            }

            else
            {

                out << "OK" << endl;
            }


        }

        if (command == "AddToArray")
        {
            string newLine;
            int numVar;
            line = line.substr(10);
            out << command << "  ";
            numList.clear();

            while (iss >> newLine)
            {
                numVar = stoi(newLine);
                mySort.addElement(numVar);
                numList.push_front(numVar);
            }
            list<int>::Iterator iter = numList.begin();
            while (iter != numList.end()) {
                out << endl << *iter << ",";
                ++iter;
            }


            out << " OK" <<  endl;

        }

        if (command == "Capacity")
        {
            out << command << " " << mySort.capacity() << endl;

        }

        if (command == "Size")
        {
            out << command << " " << mySort.size() << endl;
        }

        if (command == "Clear")
        {
            out << command << " OK" << endl;
            mySort.clear();
        }

        if (command == "PrintArray")
        {
            out << command << " ";
            out << mySort.toString() << endl;
        }

        if (command == "MedianOfThree")
        {
            string paramOne;
            string paramTwo;
            iss >> paramOne;
            iss >> paramTwo;
            int numOne;
            int numTwo;

            numOne = stoi(paramOne);
            numTwo = stoi(paramTwo);
            out << command << " " << numOne << "," << numTwo << " = " << mySort.medianOfThree(numOne, numTwo) << endl;


        }

        if (command == "Partition")
        {
            string paramOne;
            string paramTwo;
            string paramThree;
            iss >> paramOne;
            iss >> paramTwo;
            iss >> paramThree;
            int numOne;
            int numTwo;
            int pivot;

            numOne = stoi(paramOne);
            numTwo = stoi(paramTwo);
            pivot = stoi(paramThree);
            out << command << " " << numOne << "," << numTwo << "," << pivot << " = " << mySort.partition(numOne, numTwo, pivot) << endl;
        }

        if (command == "SortAll")
        {
            out << command << " OK" << endl;
            mySort.sortAll();
        }

        if (command == "Sort")
        {
            string paramOne;
            string paramTwo;
            iss >> paramOne;
            iss >> paramTwo;
            int numOne;
            int numTwo;
            numOne = stoi(paramOne);
            numTwo = stoi(paramTwo);
            out << command << " " << numOne << "," << numTwo << " OK" << endl;
            mySort.sort(numOne, numTwo);
        }

        if (command == "Stats")
        {
            out << command << " " << mySort.statCompFunc() << "," << mySort.statSwapFunc() << endl;
        }


    }


    return 0;
}
