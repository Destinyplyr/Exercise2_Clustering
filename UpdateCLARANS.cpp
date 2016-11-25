#include "Headers.h"
#include "UtilsH.h"
#include "Algorithms.h"



bool CLARANS(Conf* myConf, Metrics* myMetric, double** distanceMatrix, int* centroids,  ClusterTable* clusterTable, int** clusterAssign)
{
	int newMedoid;
	int cluster;
	bool changed = false;
	int randomCentroid, randomNonCentroid;
	int minimumCentroid, minimumNonCentroid;
	double currentSubtraction;
	double maximumSubtraction;

	for (int i = 0; i < myConf->clarans_iterations; ++i)
	{
		maximumSubtraction = INT_MIN;
		cout << "PAM number : " << i << endl;
		if (i > 0) {
			cout << "oeoeo" << clusterTable->getArray()[2]->getItemNo() <<endl;
		}
		PAM(myConf, myMetric, distanceMatrix, centroids, clusterTable, clusterAssign);
		//cout << "oeoeo" << clusterTable->getArray()[2]->getItemNo() <<endl;
		for (int j = 0; j < myConf->clarans_set_fraction; j ++) {
			cout << "clarans_set_fraction proxorame : " << j << endl;
			randomCentroid = (int)(((double)rand() / (double) RAND_MAX)*(myConf->number_of_clusters));
			cout << "randomCentroid : " << randomCentroid << endl;
			if (randomCentroid == myConf->number_of_clusters) 
			{
				randomCentroid--;
			}
			do 
			{
				randomNonCentroid = (int)(((double)rand() / (double) RAND_MAX)*(myMetric->point_number));
				cout << "randomNonCentroid : " << randomNonCentroid << endl;
				if (randomNonCentroid == myMetric->point_number) 
				{
					randomCentroid--;
				}

			}while(Exists(centroids, myConf->number_of_clusters, randomNonCentroid));
			//cluster = ReturnCluster(myConf, centroids, randomCentroid);
			cluster = randomCentroid;
			//cout << "cluster : " << cluster << endl;
			//if noncentroid better
			currentSubtraction = clusterTable->ClusterDistanceFromCentroid(distanceMatrix, cluster, centroids[randomCentroid]) - clusterTable->ClusterDistanceFromCentroid(distanceMatrix, cluster, randomNonCentroid);
			if (currentSubtraction > 0)
			{
				cout << "centroid is better " << endl;
				//if change is the best we have
				if (currentSubtraction > maximumSubtraction)
				{
					maximumSubtraction = currentSubtraction;
					cout << "chan is the best we have - maximumSubtraction is  : " << maximumSubtraction << endl;
					minimumCentroid = randomCentroid;
					cout << "minimumCentroid : " << minimumCentroid << endl;
					minimumNonCentroid = randomNonCentroid;
					cout << "minimumNonCentroid : " << minimumNonCentroid << endl;
				}
			}
		}
		cout << "going for the swap" << endl;
		//swapping
		cout << "==================" << endl << "PRINTING CLRS" <<endl;
		for (int w = 0; w <myConf->number_of_clusters; w++) {
			cout << centroids[w] << " ";
		}
		cout <<endl;
		
		cout << "swapping CLARANS : " << centroids[cluster] <<endl;
		cluster = minimumCentroid;//= ReturnCluster(myConf, centroids, minimumCentroid);
		cout << "cluster after swapping : " << minimumNonCentroid << endl;
		for (int j = 0; j < myMetric->point_number; ++j)		//updating clusterAssign
		{
			if(clusterAssign[j][0] == minimumCentroid) {
				clusterAssign[j][0] = minimumNonCentroid;
			}
			if(clusterAssign[j][1] == minimumCentroid) {
				clusterAssign[j][1] = minimumNonCentroid;
			}
			if(clusterAssign[j][2] == minimumCentroid) {
				clusterAssign[j][2] = minimumNonCentroid;
			}
		}
		centroids[cluster]  = minimumNonCentroid;
		cout << "update clusterAssign donr!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

		
		// newMedoid = clusterTable->ClusterDistance(distanceMatrix, i);
		// if (newMedoid == -1) {
		// 	cout << "There was a serious problem in the previous assignment - Aborting" <<endl;
		// 	exit(-1);
		// }
		// if (newMedoid != centroids[i]) {
		// 	changed = true;
		// 	centroids[i] = newMedoid;
		// 	cout << "changed centroid - "<< centroids[i] <<endl;
		// }
	}
	return changed;
 //    int* new_centroids;
 //    int* best_centroids;
 //    double minDistance;
 //    double secondBest;
	// cout << "IN PAM" << endl;
	// int column, row, j;
	// //struct with distance?
	// // for (int i = 0; i < myConf->number_of_clusters; ++i)
	// // {
	// // 	cout << "centroid : " << i << " is " << centroids[i] << endl;
	// // }

	// for (int i = 0; i < myMetric->point_number; ++i)
	// {
	// 	cout << "point_number  -------  " << i << endl;
	// 	minDistance = INT_MAX;
	// 	secondBest = INT_MAX;
	// 	for (int k = 0; k < myConf->number_of_clusters; ++k)
	// 	{
	// 		j = centroids[k];
	// 		cout << "THE CENTRO " << j << endl;
	// 		if (j != i)
	// 		{
	// 			if (j < i)
	// 			{
	// 				column = i;
	// 				row = j;
	// 			}
	// 			else
	// 			{
	// 				column = j;
	// 				row = i;
	// 			}

	// 			if (distanceMatrix[row][column] < minDistance)
	// 			{
	// 				secondBest = minDistance;
	// 				cout << "secondBest -----> " << secondBest << endl;
	// 				clusterAssign[i][1] = clusterAssign[i][0];
	// 				//cout << "secondBest done change" << endl;
	// 				minDistance = distanceMatrix[row][column];
	// 				cout << "actual min -----> " << minDistance << endl;
	// 				clusterAssign[i][0] = j;
	// 				//cout << "minDistance done change" << endl;
	// 			}
	// 		}
	// 	}

	// 	cout << "paw gia Remove" << endl;
	// 	clusterTable->Remove(i, clusterAssign[i][2]);
	// 	cout << "Remove DONE!!!!!!!!!!!!!!! " << endl;
	// 	for(int k = 0; k < myConf->number_of_clusters; k++) {
	// 		if (centroids[k] == clusterAssign[i][0]) 
	// 		{
	// 			clusterTable->InsertAtCluster(i, k);
	// 			break;
	// 		}
	// 	}
		
	// 	cout << "InsertAtCluster DONE!!!!!!!!!!!!!!!!!" << endl;
	// 	clusterAssign[i][2] = clusterAssign[i][0]; 
	// 	cout << "change after InsertAtCluster DON!!!!" << endl;
	// 	cout <<  "NEAREST CENTRO : ^^^^^^^^^^^^^^^^^^^^^^^^" << clusterAssign[i][2] << endl;
	// }

	// /*for (int i= 0; i < myMetric->point_number; ++i)
	// {
	// 	for (int j = 0; j < myMetric->point_number; ++j)
	// 	{
	// 		cout << "distance : " << distanceMatrix[i][centroids[i]] << endl;
	// 	}
	// }*/

}