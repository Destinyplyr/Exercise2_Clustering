#include "Headers.h"
#include "UtilsH.h"


void PAM(Conf* myConf, Metrics* myMetric, double** distanceMatrix, int* centroids,  ClusterTable* clusterTable, int** clusterAssign)
{
    int* new_centroids;
    int* best_centroids;
    double minDistance;
    double secondBest;
	cout << "IN PAM" << endl;
	int column, row, j;
	//struct with distance?
	// for (int i = 0; i < myConf->number_of_clusters; ++i)
	// {
	// 	cout << "centroid : " << i << " is " << centroids[i] << endl;
	// }

	for (int i = 0; i < myMetric->point_number; ++i)
	{
		cout << "point_number  -------  " << i << endl;
		minDistance = INT_MAX;
		secondBest = INT_MAX;
		for (int k = 0; k < myConf->number_of_clusters; ++k)
		{
			j = centroids[k];
			cout << "THE CENTRO " << j << endl;
			if (j != i)
			{
				if (j < i)
				{
					column = i;
					row = j;
				}
				else
				{
					column = j;
					row = i;
				}

				if (distanceMatrix[row][column] < minDistance)
				{
					secondBest = minDistance;
					cout << "secondBest -----> " << secondBest << endl;
					clusterAssign[i][1] = clusterAssign[i][0];
					//cout << "secondBest done change" << endl;
					minDistance = distanceMatrix[row][column];
					cout << "actual min -----> " << minDistance << endl;
					clusterAssign[i][0] = j;
					//cout << "minDistance done change" << endl;
				}
			}
		}

		cout << "paw gia Remove" << endl;
		clusterTable->Remove(i, clusterAssign[i][2]);
		cout << "Remove DONE!!!!!!!!!!!!!!! " << endl;
		for(int k = 0; k < myConf->number_of_clusters; k++) {
			if (centroids[k] == clusterAssign[i][0]) 
			{
				cout << "centroid before instert : " << centroids[k] << endl;
				clusterTable->InsertAtCluster(i, k);
				break;
			}
		}
		
		cout << "InsertAtCluster DONE!!!!!!!!!!!!!!!!!" << endl;
		clusterAssign[i][2] = clusterAssign[i][0]; 
		cout << "change after InsertAtCluster DON!!!!" << endl;
		cout <<  "NEAREST CENTRO : ^^^^^^^^^^^^^^^^^^^^^^^^" << clusterAssign[i][2] << endl;
	}

	/*for (int i= 0; i < myMetric->point_number; ++i)
	{
		for (int j = 0; j < myMetric->point_number; ++j)
		{
			cout << "distance : " << distanceMatrix[i][centroids[i]] << endl;
		}
	}*/

}
