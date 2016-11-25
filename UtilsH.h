#include "Returns.h"
//#include "Algorithms.h"
#include "DistanceMatrixFunctions.h"

void Init_Conf(Conf* myConf, std::ifstream& conFile);
void Init_Metrics(Metrics* myMetric, std::ifstream& inputFile);
void SetClaransFraction(Conf* myConf, Metrics* myMetric);
bool Exists(int* items, int pos, int newItem);
double ObjectiveCost(int** clusterAssign, double** distanceMatrix, Metrics* myMetric);
int ReturnCluster(Conf* myConf, int* centroids, int centroid);