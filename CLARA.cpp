#include "Headers.h"
#include "UtilsH.h"


void CLARA(Conf* myConf, Metrics* myMetric, double** distanceMatrix, int* centroids,  ClusterTable* clusterTable, int** clusterAssign)
{
	int n_sample_size = 40 + 2* myConf->number_of_clusters;		//n'
	int s =5; 			//best experimental result
	int new_item = -1;
	int position;
    int* new_centroids;
    int* best_centroids;
    int cluster_no = 0;
    double min_cost, current_cost;
    double secondBest;
	cout << "IN CLARA" << endl;
	int column, row, j;
	string GARBAGE;
	//struct with distance?
	// for (int i = 0; i < myConf->number_of_clusters; ++i)
	// {
	// 	cout << "centroid : " << i << " is " << centroids[i] << endl;
	// }

	int* fullPAMcentroids = new int[myConf->number_of_clusters];
	int* min_centroids = new int[myConf->number_of_clusters];

	int** fullPAMclusterAssign = new int*[n_sample_size];
	for (int i = 0; i < n_sample_size; ++i)
	{
		fullPAMclusterAssign[i] = new int[3];
		fullPAMclusterAssign[i][0] = -1;
		fullPAMclusterAssign[i][1] = -1;
		fullPAMclusterAssign[i][2] = -1;
	}
	ClusterTable* fullPAMclusterTable = new ClusterTable(myConf->number_of_clusters);

	int* current_sample = new int[n_sample_size];		//holds the items of the sample
	for (int i = 0; i < n_sample_size; ++i)
	{
		current_sample[i] = -1;
	}

	for (int i = 0; i < s; ++i)
	{
		min_cost = INT_MAX;
		for (j = 0; j < n_sample_size; j++) 
		{
			do {
				new_item= (int)(((double)rand() / (double) RAND_MAX)*(myMetric->point_number));
			}while (Exists(current_sample, n_sample_size, new_item)); 
			current_sample[j] = new_item;
		}
		//apply custom FULL PAM
		FullPAM(myConf, distanceMatrix, fullPAMcentroids, fullPAMclusterTable, fullPAMclusterAssign, current_sample, n_sample_size);
		//moving fullPAMassign to assign
		cout << "again parampampam" <<endl;
		//cin >> GARBAGE;
		for (int j = 0; j < myMetric->point_number; ++j)
		{
			if (Exists(current_sample, n_sample_size, j)) {		//if an item exists in current_sample
				for (int k = 0; k < n_sample_size; k++) {		//find its position - it corresponds to fullPAMclusterAssign position
					if (current_sample[k] == j) {
						position = k;
						break;
					}
				}
				clusterAssign[j][0] = fullPAMclusterAssign[position][0];		//move to clusterAssign
				clusterAssign[j][1] = fullPAMclusterAssign[position][1];
				clusterAssign[j][2] = fullPAMclusterAssign[position][2];		
			}
		}
		PAM( myConf,  myMetric, distanceMatrix, fullPAMcentroids, fullPAMclusterTable,clusterAssign);
		//cin >> GARBAGE;
		current_cost = ObjectiveCost(clusterAssign, distanceMatrix, myMetric);
		if (current_cost < min_cost)
		{
			cout << "904 - mincost clara: " << current_cost <<endl;
			min_cost = current_cost;
			for (int w = 0; w < myConf->number_of_clusters; ++w)
			{ 
				min_centroids[w] = fullPAMcentroids[w];
				cout << min_centroids[w] << " " ;
			}
			cout << endl;
		}
	}
	cout <<"CLARA SENDS ITS REGARDS" <<endl;
	for (int w = 0; w < myConf->number_of_clusters; ++w)
	{
		centroids[w] = min_centroids[w];
		cout << min_centroids[w] << " " ;
	}
	cout << endl;
	return;

/*



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
		cout << "my current cluster - beofre rem - 906: old " << clusterAssign[i][2] << " new " << clusterAssign[i][0]<<endl;
		if (clusterAssign[i][2] != clusterAssign[i][0]) 
		{
			if (clusterAssign[i][2] != -1) {
				cluster_no = ReturnCluster(myConf, centroids, clusterAssign[i][0]);
			}
			clusterTable->Remove(i, cluster_no);
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
		
	}*/
}
