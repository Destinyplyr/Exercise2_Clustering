#include "ListData.h"
#include "DistanceMatrixFunctions.h"
#include "ClusterTable.h"

void KMedoidsPP(Conf* myConf, Metrics* myMetric, double** distanceMatrix, int* centroids);
void Concentrate(Conf* myConf, Metrics* myMetric, double** distanceMatrix, int* centroids);
void PAM(Conf* myConf, Metrics* myMetric, double** distanceMatrix, int* centroids, ClusterTable* clusterTable,  int** clusterAssign);
void quickSort_twolist(double** myArray, int first, int last );
int parition_twolist(double** myArray, int first, int last);
