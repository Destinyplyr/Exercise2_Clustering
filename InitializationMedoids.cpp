#include "Headers.h"
#include "UtilsH.h"
#include "Algorithms.h"

void KMedoidsPP(Conf* myConf, Metrics* myMetric, double** distanceMatrix, int* centroids)
{
	cout << "dist" << distanceMatrix[0][0] <<endl;
	double Sum = 0;
	double maxProb = 0;
	double* probabilities = new double[myMetric->point_number];
	double* minDistances = new double[myMetric->point_number];
	int chosenCentroid;
	int column, row;
	string GARBAGE;


	//Initialize centroids
	for (int i = 0; i < myConf->number_of_clusters; ++i)
	{
		centroids[i] = -1;	
	}

	//Initialize minDistances
	for (int i = 0; i < myMetric->point_number; ++i)
	{
		minDistances[i] = INT_MAX;	
	}

	chosenCentroid =  (int)(((double)rand() / (double)RAND_MAX)*((double)myMetric->point_number));
	//cout << "First chosen : " << chosenCentroid << endl;
	for (int i = 0; i < myConf->number_of_clusters; ++i)
	{
		for (int u = i; u < myConf->number_of_clusters; ++u)
		{
			centroids[u] = -1;	
		}
		for (int u = 0; u < myMetric->point_number; ++u)
		{
			minDistances[u] = INT_MAX;	
		}

		//cout << "in for " << endl;
		centroids[i] = chosenCentroid;
		Sum = 0;
		maxProb = 0;
		//cout << "889" <<endl;
		for (int v = 0; v < myMetric->point_number; ++v)		//for every point
		{
			//cout << "new point" <<endl;
			//cin >> GARBAGE;
			for (int j = 0; j <= i; ++j)			//for every centroid up until now
			{
				//cout << "dm - md:" << minDistances[v] <<endl;
				//cout << "dm - md: " << distanceMatrix[v][centroids[j]] << " - " << minDistances[v] <<endl;
				//cout << v << " - " << centroids[j] << endl;
				if ( v > centroids[j]) {
					column = v;
					row = centroids[j];
				}
				else {
					row = v;
					column = centroids[j];
				}
				if (distanceMatrix[row][column] < minDistances[v] && v != centroids[j])
				{
					minDistances[v] = distanceMatrix[row][column];
					//cout << "Min distance : " << minDistances[v] << endl;
					if (minDistances[v] == 0) {
						cin >> GARBAGE;
					}
				}
			}
		}
		//cout << "ok" <<endl;
		//cin >> GARBAGE;
		for (int v = 0; v < myMetric->point_number; ++v)
		{
			if (!Exists(centroids, i, v))
			{
				Sum += pow(minDistances[v], 2);
				//cout << "Sum : " << Sum << endl;
				//cin >> GARBAGE;
			}
		}
		//cin >> GARBAGE;
		for (int v = 0; v <  myMetric->point_number; ++v)
		{
			if (!Exists(centroids, i+1, v))
			{
				probabilities[v] = (pow(minDistances[v], 2) / Sum) * ((double)rand() / (double)RAND_MAX);
				//cout << "Probability : " << probabilities[v] << endl;
			}
			else
			{
				probabilities[v] = -1;
			}
		}

		for (int v = 0; v < myMetric->point_number; ++v)
		{
			if (probabilities[v] != -1)
			{
				if (probabilities[v] > maxProb)
				{
					chosenCentroid = v;
					maxProb = probabilities[v];
					//cout << "chosenCentroid: " << chosenCentroid << " - " << "maxprob: " << maxProb <<endl;
				}
			}
		}
		//cout << "Next chosen : " << chosenCentroid << endl;
		//cin >> GARBAGE;
	}
}