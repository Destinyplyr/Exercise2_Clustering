#include "ListData.h"
#include "DistanceMatrixFunctions.h"

template <typename T>
void KMedoidsPP(Conf* myConf, Metrics* myMetric, double** distanceMatrix, ListData<T>* myList, int* centroids);
template <typename T>
void Concentrate(Conf* myConf, Metrics* myMetric, double** distanceMatrix, ListData<T>* myList, int* centroids);