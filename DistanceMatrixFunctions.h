#include "Headers.h"
#include "Returns.h"

double DistanceMatrixDistance(double** inputFile, double item1, double item2);
void quickSort(double* myArray, int first, int last );
int parition(double* myArray, int first, int last);
void swap(int& a, int& b);
double FindRadiusForAssignment(Conf* myConf,double** distanceMatrix, int* centroids);