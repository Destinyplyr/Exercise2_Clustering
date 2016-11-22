#include "ListData.h"
#include "DistanceMatrixFunctions.h"

void KMedoidsPP(Conf* myConf, Metrics* myMetric, double** distanceMatrix, int* centroids);
void Concentrate(Conf* myConf, Metrics* myMetric, double** distanceMatrix, int* centroids);
template <typename T>
void PAM(Conf* myConf, Metrics* myMetric, double** distanceMatrix, ListData<T>* myList, int* centroids);
void quickSort_twolist(double** myArray, int first, int last );
int parition_twolist(double** myArray, int first, int last);
