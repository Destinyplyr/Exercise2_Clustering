#include "Returns.h"


void Init_Conf(Conf* myConf, std::ifstream& conFile);
void Init_Metrics(Metrics* myMetric, std::ifstream& inputFile);
void SetClaransFraction(Conf* myConf, Metrics* myMetric);
bool Exists(int* items, int pos, int newItem);