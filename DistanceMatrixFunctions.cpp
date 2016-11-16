#include "DistanceMatrixFunctions.h"

using namespace std;


double DistanceMatrixDistance(double** distanceMatrix, double item1, double item2) {

    int driver = 0;
    int left = 0;

    if (item1 >= item2) {   //Driver the smallest to also work with the instructions
        driver = item2;
        left = item1;
    }
    else {
        driver = item1;
        left = item2;
    }
    return distanceMatrix[driver][left];
}


void quickSort(double* myArray, int first, int last ){
    int pivot;
    if(first < last){
        pivot = parition(myArray, first, last);
        quickSort(myArray, first, pivot-1);
        quickSort(myArray, pivot+1, last);
    }
}


int parition(double* myArray, int first, int last){
    int  piv = first;
    int pivot = myArray[first];

    for(int i = first+1 ; i <= last ; i++){
        if(myArray[i] <= pivot)
        {
            swap(myArray[i], myArray[piv]);
            piv++;
        }
    }
    swap(myArray[piv], myArray[first]);
    return piv;
}


void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}