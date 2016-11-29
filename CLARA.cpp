#include "Headers.h"
#include "UtilsH.h"
#include "Algorithms.h"


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
	//cout << "IN CLARA" << endl;
	int column, row, j;
	string GARBAGE;
	ClusterTable* minfullPAMclusterTable = NULL;
	int** minfullPAMclusterAssign = NULL;
	//struct with distance?
	// for (int i = 0; i < myConf->number_of_clusters; ++i)
	// {
	// 	cout << "centroid : " << i << " is " << centroids[i] << endl;
	// }

    int** CLARAclusterAssign= new int*[myMetric->point_number];
    for (int i = 0; i < myMetric->point_number; ++i)
    {
        CLARAclusterAssign[i] = new int[3];
        CLARAclusterAssign[i][0] = -1;
        CLARAclusterAssign[i][1] = -1;
        CLARAclusterAssign[i][2] = -1;
    }


	int* fullPAMcentroids = new int[myConf->number_of_clusters];
	int* min_centroids = new int[myConf->number_of_clusters];

	int** fullPAMclusterAssign;
	ClusterTable* fullPAMclusterTable;

	int* current_sample = new int[n_sample_size];		//holds the items of the sample
	for (int i = 0; i < n_sample_size; ++i)
	{
		current_sample[i] = -1;
	}

	for (int i = 0; i < s; ++i)
	{
		fullPAMclusterAssign = new int*[n_sample_size];
		for (int j = 0; j < n_sample_size; ++j)
		{
			fullPAMclusterAssign[j] = new int[3];
			fullPAMclusterAssign[j][0] = -1;
			fullPAMclusterAssign[j][1] = -1;
			fullPAMclusterAssign[j][2] = -1;
		}
		fullPAMclusterTable= new ClusterTable(myConf->number_of_clusters);
		min_cost = INT_MAX;
		for (int j = 0; j < n_sample_size; j++) 
		{
			do {
				new_item= (int)(((double)rand() / (double) RAND_MAX)*(myMetric->point_number));
			}while (Exists(current_sample, n_sample_size, new_item)); 
			current_sample[j] = new_item;
		}
		//apply custom FULL PAM
		FullPAM(myConf, distanceMatrix, fullPAMcentroids, fullPAMclusterTable, fullPAMclusterAssign, current_sample, n_sample_size);
		//moving fullPAMassign to assign
		//cout << "again parampampam" <<endl;
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
				CLARAclusterAssign[j][0] = fullPAMclusterAssign[position][0];		//move to claraclusterAssign
				CLARAclusterAssign[j][1] = fullPAMclusterAssign[position][1];
				CLARAclusterAssign[j][2] = fullPAMclusterAssign[position][2];		
			}
		}
		PAM( myConf,  myMetric, distanceMatrix, fullPAMcentroids, fullPAMclusterTable, CLARAclusterAssign);
		//cin >> GARBAGE;
		current_cost = ObjectiveCost(CLARAclusterAssign, distanceMatrix, myMetric);
		if (current_cost < min_cost)
		{
			//cout << "904 - mincost clara: " << current_cost <<endl;
			min_cost = current_cost;
			minfullPAMclusterAssign = CLARAclusterAssign;
			minfullPAMclusterTable = fullPAMclusterTable;
			for (int w = 0; w < myConf->number_of_clusters; ++w)
			{ 
				for (int j = 0; j < myMetric->point_number; ++j)		//updating clusterAssign
				{
					if(minfullPAMclusterAssign[j][0] == min_centroids[w]) {
						minfullPAMclusterAssign[j][0] = fullPAMcentroids[w];
					}
					if(minfullPAMclusterAssign[j][1] == min_centroids[w]) {
						minfullPAMclusterAssign[j][1] = fullPAMcentroids[w];
					}
					if(minfullPAMclusterAssign[j][2] == min_centroids[w]) {
						minfullPAMclusterAssign[j][2] = fullPAMcentroids[w];
					}
				}
				min_centroids[w] = fullPAMcentroids[w];
				cout << min_centroids[w] << " " ;
			}
			cout << endl;
			//DELETE minfullPAMclusterAssign before next command!!!!!
			if (minfullPAMclusterAssign != NULL) 
			{
				for (int u = 0; u < myMetric->point_number; u++)
				{
					//delete[] minfullPAMclusterAssign[u];
				}
				//delete[] minfullPAMclusterAssign;
				minfullPAMclusterAssign = NULL;
			}
			//DELETE minfullPAMclusterTable before next command
			if (minfullPAMclusterTable != NULL) 
			{
				//delete minfullPAMclusterTable;
				minfullPAMclusterTable = NULL;
			}

			//minfullPAMclusterAssign = CLARAclusterAssign;
			//minfullPAMclusterTable = fullPAMclusterTable;
		}
		else
		{
			for (int u = 0; u < myMetric->point_number; u++)
			{
				//delete[] fullPAMclusterAssign[i];
			}
			//delete[] fullPAMclusterAssign;
			fullPAMclusterAssign = NULL;
			//delete fullPAMclusterTable;
			fullPAMclusterTable = NULL;
		}
	}
	cout <<"CLARA SENDS ITS REGARDS" <<endl;
	for (int w = 0; w < myConf->number_of_clusters; ++w)
	{
		/*cout << "fullPAMcentroids[" <<w<<"]: " << fullPAMcentroids[w] << " centroids[" <<w<<"]: " << centroids[w]<< " min_centroids[" <<w<<"]: " << min_centroids[w] <<endl;
		for (int j = 0; j < myMetric->point_number; ++j)		//updating clusterAssign
		{
			if(minfullPAMclusterAssign[j][0] == fullPAMcentroids[w]) {
				minfullPAMclusterAssign[j][0] = min_centroids[w];
			}
			if(minfullPAMclusterAssign[j][1] == fullPAMcentroids[w]) {
				minfullPAMclusterAssign[j][1] = min_centroids[w];
			}
			if(minfullPAMclusterAssign[j][2] == fullPAMcentroids[w]) {
				minfullPAMclusterAssign[j][2] = min_centroids[w];
			}
		}*/
		centroids[w] = min_centroids[w];
		//cout << min_centroids[w] << " " ;
		/*for (int j = 0; j < myMetric->point_number; ++j)		//updating clusterAssign
		{
			if(clusterAssign[j][0] == centroids[w]) {
				clusterAssign[j][0] = newMedoid;
			}
			if(clusterAssign[j][1] == centroids[i]) {
				clusterAssign[j][1] = newMedoid;
			}
			if(clusterAssign[j][2] == centroids[i]) {
				clusterAssign[j][2] = newMedoid;
			}
		}*/
	}

	cout << endl;
	clusterTable->setArray(fullPAMclusterTable->getArray());
	for (int i = 0; i < myMetric->point_number; ++i)
	{
		if(!Exists(centroids, myConf->number_of_clusters, CLARAclusterAssign[i][0]) || !Exists(centroids, myConf->number_of_clusters, CLARAclusterAssign[i][1]) || !Exists(centroids, myConf->number_of_clusters, CLARAclusterAssign[i][2])) 
		{
/*			cout << "YHUUUGE PROBLLEM ----" <<endl;
			cout << CLARAclusterAssign[i][0] << " " << CLARAclusterAssign[i][1] << " " << CLARAclusterAssign[i][2] <<endl;
			cout << "---------------------" <<endl;*/
		}
	}
	for (int j = 0; j < myMetric->point_number; ++j)
	{
		cout << "point : " << j <<endl;
		clusterAssign[j][0] = minfullPAMclusterAssign[j][0];		
		clusterAssign[j][1] = minfullPAMclusterAssign[j][1];
		clusterAssign[j][2] = minfullPAMclusterAssign[j][2];
		cout << "clusterAssign[j][0] " << clusterAssign[j][0] << " clusterAssign[j][1] " << clusterAssign[j][1] << " clusterAssign[j][2] " << clusterAssign[j][2] <<endl;
	}
	/*for (int w = 0; w < myConf->number_of_clusters; ++w)
	{
		//centroids[w] = min_centroids[w];
		//cout << min_centroids[w] << " " ;
		for (int j = 0; j < myMetric->point_number; ++j)		//updating clusterAssign
		{
			if(clusterAssign[j][0] == centroids[w]) {
				clusterAssign[j][0] = centroids[w];
			}
			if(clusterAssign[j][1] == centroids[w]) {
				clusterAssign[j][1] = centroids[w];
			}
			if(clusterAssign[j][2] == centroids[w]) {
				clusterAssign[j][2] = centroids[w];
			}
		}
	}*/


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
