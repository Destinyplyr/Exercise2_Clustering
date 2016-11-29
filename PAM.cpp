#include "Headers.h"
#include "UtilsH.h"
#include "Algorithms.h"


void FullPAM(Conf* myConf, double** distanceMatrix, int* centroids,  ClusterTable* clusterTable, int** clusterAssign, int* current_sample, int n_sample_size)
{
	int current_point;
	int minimumCentroid, minimumNonCentroid;
	double currentSubtraction,maximumSubtraction;
    int* new_centroids;
    int* best_centroids;
    int cluster = 0;
    int cluster_no = 0;
    double minDistance, minDistanceSecond;
    double secondBest;
	//cout << "IN PAM" << endl;
	int column, row, j;

	for (int i = 0; i < myConf->number_of_clusters; ++i)
	{
		centroids[i] = current_sample[(int)(((double)rand() / (double) RAND_MAX)*(n_sample_size))];		//random centroids		
	}

	//assignment
	for (int i = 0; i < n_sample_size; ++i)
	{
		current_point = current_sample[i];
		minDistance = INT_MAX;
		secondBest = INT_MAX;
		for (int k = 0; k < myConf->number_of_clusters; ++k)
		{
			j = centroids[k];
			//cout << "THE CENTRO " << j << endl;
			if (j != current_point)
			{
				if (j < current_point)
				{
					column = current_point;
					row = j;
				}
				else
				{
					column = j;
					row = current_point;
				}

				if (distanceMatrix[row][column] < minDistance)
				{
					secondBest = minDistance;
					//cout << "secondBest -----> " << secondBest << endl;
					clusterAssign[i][1] = clusterAssign[i][0];
					//cout << "secondBest done change" << endl;
					minDistance = distanceMatrix[row][column];
					//cout << "actual min -----> " << minDistance << endl;
					clusterAssign[i][0] = j;
					//cout << "minDistance done change" << endl;
					if (clusterAssign[i][1] == -1)
					{
						minDistanceSecond = INT_MAX;
						for (int remain_cluster = k+1; remain_cluster < myConf->number_of_clusters; ++remain_cluster)
						{
							if (DistanceMatrixDistance(distanceMatrix, i, remain_cluster) < minDistanceSecond)
							{
								clusterAssign[i][1] = centroids[remain_cluster];
							}
						}
					}
				}
			}
		}

		cout << "paw gia Remove" << endl;
		cout << "my current cluster - beofre rem - 906: old " << clusterAssign[i][2] << " new " << clusterAssign[i][0]<<endl;
		if (clusterAssign[i][2] != clusterAssign[i][0]) 
		{
			if (clusterAssign[i][2] != -1) {
				cluster_no = ReturnCluster(myConf, centroids, clusterAssign[i][2]);
			}
			clusterTable->Remove(current_point, cluster_no);
			cout << "Remove DONE!!!!!!!!!!!!!!! " << endl;
			for(int k = 0; k < myConf->number_of_clusters; k++) {
				if (centroids[k] == clusterAssign[i][0]) 
				{
					cout << "centroid before instert : " << centroids[k] << endl;
					if(!clusterTable->ClusterDuplicate(current_point, k))
					{
						clusterTable->InsertAtCluster(current_point, k);
					}
					break;
				}
			}
			cout << "InsertAtCluster DONE!!!!!!!!!!!!!!!!!" << endl;
			//THIS IS SO WROOOOOOOOOOOOOOOOOOOOOOOOOOOOOOONG!!!!!!!!!!!!!!!!!!!!!!!!!!
			clusterAssign[i][2] = clusterAssign[i][0]; 
			cout << "change after InsertAtCluster DON!!!!" << endl;
			cout <<  "NEAREST CENTRO for" << i << "IN FULL PAM : ^^^^^^^^^^^^^^^^^^^^^^^^" << clusterAssign[i][2] << endl;
		}
		
	}
	//update
	while(1)
	{

		for (int i = 0; i < myConf->number_of_clusters; ++i)		//i is cluster
		{
			maximumSubtraction = INT_MIN;
			cluster = i;
			for (int j = 0; j < n_sample_size; ++j)			//j is current item
			{
				cout << "clusterTable->ClusterDistanceFromCentroid(distanceMatrix, cluster, centroids[cluster]): " << clusterTable->ClusterDistanceFromCentroid(distanceMatrix, cluster, centroids[cluster]) << endl;
				cout << "clusterTable->ClusterDistanceFromCentroid(distanceMatrix, cluster, current_sample[j]): " << clusterTable->ClusterDistanceFromCentroid(distanceMatrix, cluster, current_sample[j]) << endl;
				currentSubtraction = clusterTable->ClusterDistanceFromCentroid(distanceMatrix, cluster, centroids[cluster]) - clusterTable->ClusterDistanceFromCentroid(distanceMatrix, cluster, current_sample[j]);
				cout << "cur sub: " << currentSubtraction <<endl;
				if (currentSubtraction > 0)
				{
					cout << "centroid is better " << endl;
					//if change is the best we have
					if (currentSubtraction > maximumSubtraction)
					{
						maximumSubtraction = currentSubtraction;
						cout << "chan is the best we have - maximumSubtraction is  : " << maximumSubtraction << endl;
						minimumCentroid = cluster;						//MINIMUM CENTROID IS CLUSTER - index			
						cout << "minimumCentroid : " << minimumCentroid << endl;
						minimumNonCentroid = current_sample[j];			//MINIMUM NON CENTROID IS ITEM
						cout << "minimumNonCentroid : " << minimumNonCentroid << endl;
					}
				}
			}
		}
		cout << "going for the swap" << endl;
		//swapping
		cluster = minimumCentroid;//= ReturnCluster(myConf, centroids, minimumCentroid);
		cout << "cluster after swapping : " << cluster << endl;
		if (centroids[cluster] == minimumNonCentroid) {
			cout << "finished Full PAM" <<endl;
			break;
		}
		
		for (int j = 0; j < n_sample_size; ++j)		//updating clusterAssign
		{
			if(clusterAssign[j][0] == centroids[minimumCentroid]) {
				clusterAssign[j][0] = minimumNonCentroid;
			}
			if(clusterAssign[j][1] == centroids[minimumCentroid]) {
				clusterAssign[j][1] = minimumNonCentroid;
			}
			if(clusterAssign[j][2] == centroids[minimumCentroid]) {
				clusterAssign[j][2] = minimumNonCentroid;
			}
		}
		centroids[cluster]  = minimumNonCentroid;
	}
}
