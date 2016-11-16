#include <bitset>
#include "NodeFunctions.cpp"
#include "ListsFunctions.cpp"
#include "VectorHammingListManagement.cpp"
#include "DBListManagement.cpp"
#include "Headers.h"
#include "UtilsH.h"
#include "ListData.h"

void CLI(ifstream& inputFile, ofstream& outputFile, Conf* myConf, Metrics* myMetric);
void ReadFiles(ifstream& inputFile, Metrics* myMetric, int* N, double** distanceMatrix);