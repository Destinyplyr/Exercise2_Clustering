#include "MathFunctions.h"
using namespace std;

double dot_product(double* vector1, double* vector2, int vector_size) {
	double dot_product = 0;
	for (int i =0; i < vector_size; i++) {
        //cout << "vector 1 - vector 2: " << vector1[0] << " - " << vector2[0] <<endl;
		dot_product += vector1[i] * vector2[i];
	}
	return dot_product;
}

double euclid_norm(double* vector1, int vector_size) {
    double norm = 0;
    for (int i = 0; i < vector_size; i++) {
        norm += (pow(vector1[i], 2));
    }
    return sqrt(norm);
}

bool SameArray(double* array1, double* array2, int size) {
    for (int i = 0; i < size; i++) {
        //cout << array1[i]<< "-" << array2[i] <<endl;
        if (array1[i] != array2[i]) {
            return false;
        }
    }
    return true;
}