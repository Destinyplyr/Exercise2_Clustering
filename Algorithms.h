#include "ListData.h"
#include "DistanceMatrixFunctions.h"
#include "ClusterTable.h"

void KMedoidsPP(Conf* myConf, Metrics* myMetric, double** distanceMatrix, int* centroids);
void Concentrate(Conf* myConf, Metrics* myMetric, double** distanceMatrix, int* centroids);
void PAM(Conf* myConf, Metrics* myMetric, double** distanceMatrix, int* centroids, ClusterTable* clusterTable,  int** clusterAssign);
bool ALaLoyds(Conf* myConf, Metrics* myMetric, double** distanceMatrix, int* centroids,  ClusterTable* clusterTable, int** clusterAssign);
bool CLARANS(Conf* myConf, Metrics* myMetric, double** distanceMatrix, int* centroids,  ClusterTable* clusterTable, int** clusterAssign);
void CLARA(Conf* myConf, Metrics* myMetric, double** distanceMatrix, int* centroids,  ClusterTable* clusterTable, int** clusterAssign);
void FullPAM(Conf* myConf, double** distanceMatrix, int* centroids,  ClusterTable* clusterTable, int** clusterAssign, int* current_sample, int n_sample_size);
void quickSort_twolist(double** myArray, int first, int last );
int parition_twolist(double** myArray, int first, int last);
