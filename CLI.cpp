#include "mainSample.h"

void CLI(ifstream& inputFile, ofstream& outputFile, Conf* myConf, Metrics* myMetric, ClusterTable* clusterTable, double** distance_matrix, int* centroids, int** clusterAssign, int L, int k, bool complete_printing) 
{
	int total;
	string GARBAGE;
	int point_number, size_of_cluster;
	int* items_in_cluster_itemNo;
	string*	items_in_cluster_itemName;
	bool first_time_lsh = 1; 	
	int hashCreationDone = 0;

	/*if (strcmp(myMetric->metric_space.c_str(), "hamming") == 0)
	{

	}
	if (strcmp(myMetric->metric_space.c_str(), "vector") == 0)
	{
		if (strcmp(myMetric->metric.c_str(), "euclidean") == 0)
		{

		}
		
		if (strcmp(myMetric->metric.c_str(), "cosine") == 0)
		{

		}
	}
	if (strcmp(myMetric->metric_space.c_str(), "matrix") == 0)
	{


	}*/

	if (strcmp(myMetric->metric_space.c_str(), "hamming") == 0)
	{
		ListData<bitset<64> >* hammingList = new ListData<bitset<64> >();
		hammingList->ListInsertionHamming(inputFile, myMetric);

		//cout << "********************************************************" << endl;
		clusterTable->Init_Tables(&distance_matrix, myMetric, myConf, &centroids, &clusterTable, &clusterAssign);
		SetClaransFraction(myConf, myMetric);
		//cout << "********************************************************" << endl;

		hammingList->DistanceMatrixComputationHamming(myMetric, distance_matrix);
		hammingList->Printer( inputFile, outputFile, myConf, myMetric, clusterTable, distance_matrix, centroids, clusterAssign, L,  k, complete_printing);
		delete hammingList;
	}


	if (strcmp(myMetric->metric_space.c_str(), "vector") == 0)
	{
		if (strcmp(myMetric->metric.c_str(), "euclidean") == 0)
		{
			ListData<double*>* euclideanList = new ListData<double*>();
			//cout << "tralalo" <<endl;
			euclideanList->ListInsertionVector(inputFile, myMetric);

			//cout << "********************************************************" << endl;
			clusterTable->Init_Tables(&distance_matrix, myMetric, myConf, &centroids, &clusterTable, &clusterAssign);
			SetClaransFraction(myConf, myMetric);
			//cout << "********************************************************" << endl;
			//cout << "bururur" << euclideanList->getNode()->getKey()[0] <<endl;
			euclideanList->DistanceMatrixComputationVector(myMetric, distance_matrix);

			euclideanList->Printer( inputFile, outputFile, myConf, myMetric, clusterTable, distance_matrix, centroids, clusterAssign, L,  k, complete_printing);
			delete euclideanList;
		}
		
		if (strcmp(myMetric->metric.c_str(), "cosine") == 0)
		{
			ListData<double*>* cosineList = new ListData<double*>();
			cosineList->ListInsertionVector(inputFile, myMetric);
			//cout << "********************************************************" << endl;
			clusterTable->Init_Tables(&distance_matrix, myMetric, myConf, &centroids, &clusterTable, &clusterAssign);
			SetClaransFraction(myConf, myMetric);
			//cout << "********************************************************" << endl;
			cosineList->DistanceMatrixComputationVector(myMetric, distance_matrix);

			cosineList->Printer( inputFile, outputFile, myConf, myMetric, clusterTable, distance_matrix, centroids, clusterAssign, L,  k, complete_printing);
			delete cosineList;
		}
	}

	if (strcmp(myMetric->metric_space.c_str(), "matrix") == 0)
	{
		ListData<double*>* DBHList = new ListData<double*>();
		DBHList->ListInsertionDB(inputFile, myMetric);

		cout << "********************************************************" << endl;
		clusterTable->Init_Tables(&distance_matrix, myMetric, myConf, &centroids, &clusterTable, &clusterAssign);
		SetClaransFraction(myConf, myMetric);
		cout << "********************************************************" << endl;

		DBHList->DistanceMatrixComputationDB(inputFile, myMetric, distance_matrix);
		DBHList->Printer( inputFile, outputFile, myConf, myMetric, clusterTable, distance_matrix, centroids, clusterAssign, L,  k, complete_printing);
		delete DBHList;
	}
	//DELETE SEGMENT
	for (int i = 0; i < myMetric->point_number; i++) {
	    delete [] distance_matrix[i];
	}
	delete[] distance_matrix;       //distance matrix deletion
	//cout << "ekana to distance" << endl;
	delete[] centroids;
	//cout << "ekana to insertion" << endl;

	//delete clusterTable;
	//cout << "list: " << (*clusterTable)->getArray() <<endl;
	/*for (int i = 0; i < myMetric->point_number; ++i)
	{
	    delete[] clusterAssign[i];
	}
	delete[] clusterAssign;*/

}
