//
// Created by Sid Bradshaw on 4/8/21.
//

#ifndef SORT_QS_H
#define SORT_QS_H
#include <iostream>
#include <ostream>
#include <sstream>
#include "QSInterface.h"


using namespace std;
template<typename T>
class QS : public QSInterface<T>
{
private:
    size_t maxCapacity;
    T* myArray;
    size_t numItems;
    size_t numComp;
    size_t numSwap;


public:
    QS() : maxCapacity(0), myArray(NULL), numItems(0), numComp(0), numSwap(0) {}
    ~QS() {delete[] myArray;}

    bool setMaxCapacity(int value)
    {
        maxCapacity = value;
        myArray = new T[maxCapacity];
        for (unsigned int i = 0; i < maxCapacity; i++)
        {
            myArray[i] = NULL;
        }
        return true;
    }

    void reallocate()
    {
        int newSize = maxCapacity * 2;
        T* dummyArray = new T[newSize];

        for (unsigned int i = 0; i < numItems; i++)
        {
            dummyArray[i] = myArray[i];
        }

        maxCapacity = newSize;
        swap(myArray, dummyArray);
        delete[] dummyArray;
    }

    /** Add an element to the QuickSort array. Dynamically grow array as needed. */
    bool addElement(T element)
    {

        if (numItems == maxCapacity)
        {
            reallocate();
        }

             myArray[numItems] = element;
             numItems++;
             return true;



    }


    /** Sort the elements of a QuickSort subarray using median and partition functions. */
    bool sort(size_t left, size_t right) //arguments are indices
    {
        if (right == 1)
            return true;

        for (unsigned int i = left; i < right - 1; i++)
        {
            numComp++;
            if (myArray[i] > myArray[i + 1])
            {
                swap(myArray[i], myArray[i + 1]);
                numSwap++;
            }
        }

        sort(left, right - 1);

    }

    /** Sort all elements of the QuickSort array using median and partition functions. */
    bool sortAll()
    {
        int pivot;
        pivot = medianOfThree(0,numItems);
        partition(0, numItems, pivot);
        sort(0,pivot);
        sort(pivot, numItems);
        sort(0,pivot);
        return true;
    }

    /** Removes all items from the QuickSort array. */
    bool clear()
    {
        if (numItems == 0)
        {
            return false;
        }

        else
        {
            for(unsigned int i = 0; i < numItems; i++)
            {
                myArray[i] = 0;
            }
            numItems = 0;
            return true;
        }

    }

    /** Return size of the QuickSort array. */
    size_t capacity() const
    {
        return maxCapacity;
    }

    /** Return number of elements in the QuickSort array. */
    size_t size() const
    {
        return numItems;
    }

    /** The median of three pivot selection has two parts:
    1) Calculates the middle index by averaging the given left and right indices:
       middle = (left + right)/2
    2) Then bubble-sorts the values at the left, middle, and right indices.

    After this method is called, data[left] <= data[middle] <= data[right].

    @param left - the left boundary for the subarray from which to find a pivot
    @param right - the right + 1 boundary for the subarray from which to find a pivot
    @return the index of the pivot (middle index).
    Return -1 if  1) the array is empty,
                  2) if either of the given integers is out of bounds,
                  3) or if the left index is not less than the right index.
    */
    int medianOfThree(size_t left, size_t right)
    {
        if (numItems == 0)
        {
            return -1;
        }

        else if (left < 0)
        {
            return -1;
        }

        else if (right >= maxCapacity)
        {
            return -1;
        }

        else if (left >= right)
        {
            return -1;
        }
        else
        {
        int middle = (left + right) / 2;
        recMed(left, middle, right);
        return middle;
        }

    }

    void recMed(int left, int middle, int right)
    {
        numComp++;
        if (myArray[left] > myArray[middle])
        {
            swap(myArray[left], myArray[middle]);
            numSwap++;
        }
        numComp++;
        if (myArray[middle] > myArray[right - 1])
        {
            swap(myArray[right - 1], myArray[middle]);
            numSwap++;
        }
        numComp++;
        if (myArray[left] > myArray[right - 1])
        {
            swap(myArray[left], myArray[right - 1]);
            numSwap++;
        }
        numComp++;
        if (myArray[left] > myArray[middle])
        {
            swap(myArray[left], myArray[middle]);
            numSwap++;
        }

    }



    /** Partitions a subarray around a pivot value selected according
    to median-of-three pivot selection. Because there are multiple ways
    to partition a list, follow the algorithm on page 611.

    The values less than or equal to the pivot should be placed to the left of the pivot;
    the values greater than the pivot should be placed to the right of the pivot.

    @param left - left index for the subarray to partition.
    @param right - right index + 1 for the subarray to partition.
    @param pivotIndex - index of the pivot in the subarray.
    @return the pivot's ending index after the partition completes:
    Return -1 if  1) the array is empty,
                  2) if any of the given indexes are out of bounds,
                  3) if the left index is not less than the right index.
    */
    int partition(size_t left, size_t right, size_t pivotIndex)
    {
        if (numItems == 0)
        {
            return -1;
        }

        else if (left < 0)
        {
            return -1;
        }

        else if (right - 1 > maxCapacity)
        {
            return -1;
        }

        else if (left >= right)
        {
            return -1;
        }

        else if (pivotIndex > right)
        {
            return -1;
        }


        else
        {
            swap(myArray[left], myArray[pivotIndex]);
            numSwap++;

            int up = left + 1;
            int down = right - 1;
            do
            {
                while ((up != right -1) && !(myArray[left] < myArray[up]))
                {
                    ++up;
                }
                while (myArray[left] < myArray[down])
                {
                    --down;
                }
                numComp++;
                if (up < down)
                {
                    swap(myArray[up], myArray[down]);
                    numSwap++;
                }
            } while (up < down);

            swap(myArray[left], myArray[down]);
            numSwap++;
            return down;

        }


    }

    /** @return: comma delimited string representation of the array. */
    std::string toString() const
    {
        stringstream print;
        if (numItems == 0)
        {
            print << "Empty";
            return print.str();
        }

        else
        {
            for (unsigned int i = 0; i < numItems; i++)
            {
                print << myArray[i];
                if (i != numItems - 1)
                {
                    print << ",";
                }


            }

            return print.str();
        }


    }

    friend std::ostream& operator<< (std::ostream& os, QS<T>& quickSort)
    {
        os << quickSort.toString();
        return os;
    }

    int statCompFunc()
    {
        return numComp;
    }
    int statSwapFunc()
    {
        return numSwap;
    }



};


#endif //SORT_QS_H
