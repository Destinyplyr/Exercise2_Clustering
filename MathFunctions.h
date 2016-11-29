#include <math.h>
#include <iostream>

/*double dot_product(double* vector1, double* vector2, int vector_size);
double euclid_norm(double* vector1, int vector_size);
bool SameArray(double* array1, double* array2, int size);
double DistanceEuclid(double item1[], double item2[], int size);*/
template <typename T>
double dot_product(T vector1, double* vector2, int vector_size);
template <typename T>
double euclid_norm(T vector1, int vector_size);
template <typename T>
bool SameArray(T array1, T array2, int size);
template <typename T>
double DistanceEuclid(T item1[], T item2[], int size);