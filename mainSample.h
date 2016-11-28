#include "NodeFunctions.cpp"
#include "ListsFunctions.cpp"
#include "VectorHammingListManagement.cpp"
#include "EuclideanList.cpp"
#include "CosineList.cpp"
#include "HammingListManagement.cpp"
#include "HashFunctions.cpp"
#include "DBListManagement.cpp"
#include "DBHManagement.cpp"
#include "HammingLSHManagement.cpp"
#include "Headers.h"
#include "UtilsH.h"
#include "Algorithms.h"

//below declared on MainFunctions.cpp
//void CLI(ifstream& inputFile, ofstream& outputFile, Conf* myConf, Metrics* myMetric);

//below declared on CLI.cpp
void CLI(ifstream& inputFile, ofstream& outputFile, Conf* myConf, Metrics* myMetric, ClusterTable* clusterTable, double** distance_matrix, int* centroids, int** clusterAssign, int L, int k, bool complete_printing);

//below declared on MainFunctions.cpp
void ReadFiles(ifstream& inputFile, Metrics* myMetric, int* N, double** distanceMatrix);