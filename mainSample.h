#include "NodeFunctions.cpp"
#include "ListsFunctions.cpp"
#include "VectorHammingListManagement.cpp"
#include "EuclideanList.cpp"
#include "HammingListManagement.cpp"
#include "HashFunctions.cpp"
#include "DBListManagement.cpp"
#include "DBHManagement.cpp"
#include "HammingLSHManagement.cpp"
#include "Headers.h"
#include "UtilsH.h"
#include "Algorithms.h"

void CLI(ifstream& inputFile, ofstream& outputFile, Conf* myConf, Metrics* myMetric);
void ReadFiles(ifstream& inputFile, Metrics* myMetric, int* N, double** distanceMatrix);