#include "Returns.h"
#include "Algorithms.h"

void Init_Conf(Conf* myConf, std::ifstream& conFile);
void Init_Metrics(Metrics* myMetric, std::ifstream& inputFile);
void SetClaransFraction(Conf* myConf, Metrics* myMetric);
bool Exists(int* items, int pos, int newItem);
double ObjectiveCost(int** clusterAssign, double** distanceMatrix, Metrics* myMetric);
void Init_Tables(double*** distanceMatrix, Metrics* myMetric, Conf* myConf, int** centroids, ClusterTable** clusterTable, int*** clusterAssign);
int ReturnCluster(Conf* myConf, int* centroids, int centroid);