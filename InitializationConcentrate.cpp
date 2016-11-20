#include "Headers.h"
#include "UtilsH.h"
#include "Algorithms.h"

template <typename T>
void Concentrate(Conf* myConf, Metrics* myMetric, double** distanceMatrix, ListData<T>* myList, int* centroids)
{
	double Sum = 0;
	double divisor;
	double maxProb = 0;
	double** V_s = new double*[myMetric->point_number];     //V_s[i][0] -> holds V for i centroid [1] holds which point is this centroid
	for (int i = 0; i < myMetric->point_number; ++i)		//init
	{
	    V_s[i] = new double[2];
		V_s[i][0] = 0;
	}
	//double* minDistances = new double[myMetric->point_number];
	int chosenCentroid;
	int column, row;
	string GARBAGE;

	for (int i =0; i <myMetric->point_number; ++i ) {
		for (int j = 0; j < myMetric->point_number; ++j)
		{
			divisor = 0;
			for (int t = 0; t < myMetric->point_number; ++t)
			{
				divisor += DistanceMatrixDistance(distanceMatrix, j, t);
			}
			V_s[i][0] += DistanceMatrixDistance(distanceMatrix, i, j) / divisor;
		}
		V_s[i][1] = i;
	}
	quickSort_twolist(V_s, 0, myMetric->point_number-1);
    for (int i = 0; i < myConf->number_of_clusters; i ++) {
        centroids[i] = V_s[i][1];
    }


	/*

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
	cout << "First chosen : " << chosenCentroid << endl;
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

		cout << "in for " << endl;
		centroids[i] = chosenCentroid;
		Sum = 0;
		maxProb = 0;
		cout << "889" <<endl;
		for (int v = 0; v < myMetric->point_number; ++v)		//for every point
		{
			cout << "new point" <<endl;
			//cin >> GARBAGE;
			for (int j = 0; j <= i; ++j)			//for every centroid up until now
			{
				//cout << "dm - md:" << minDistances[v] <<endl;
				//cout << "dm - md: " << distanceMatrix[v][centroids[j]] << " - " << minDistances[v] <<endl;
				cout << v << " - " << centroids[j] << endl;
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
					cout << "Min distance : " << minDistances[v] << endl;
					if (minDistances[v] == 0) {
						cin >> GARBAGE;
					}
				}
			}
		}
		cout << "ok" <<endl;
		cin >> GARBAGE;
		for (int v = 0; v < myMetric->point_number; ++v)
		{
			if (!Exists(centroids, i, v))
			{
				Sum += pow(minDistances[v], 2);
				cout << "Sum : " << Sum << endl;
				//cin >> GARBAGE;
			}
		}
		cin >> GARBAGE;
		for (int v = 0; v <  myMetric->point_number; ++v)
		{
			if (!Exists(centroids, i, v))
			{
				probabilities[v] = (pow(minDistances[v], 2) / Sum) * ((double)rand() / (double)RAND_MAX);
				cout << "Probability : " << probabilities[v] << endl;
			}
			else
			{
				probabilities[v] = -1;
			}
		}
cin >> GARBAGE;

		for (int v = 0; v < myMetric->point_number; ++v)
		{
			if (probabilities[v] != -1)
			{
				if (probabilities[v] > maxProb)
				{
					chosenCentroid = v;
					maxProb = probabilities[v];
				}
			}
		}
		cout << "Next chosen : " << chosenCentroid << endl;
		cin >> GARBAGE;
	}*/
}

void quickSort_twolist(double** myArray, int first, int last ){ //appied QS for twolist
    int pivot;
    if(first < last){
        pivot = parition_twolist(myArray, first, last);
        quickSort_twolist(myArray, first, pivot-1);
        quickSort_twolist(myArray, pivot+1, last);
    }
}


int parition_twolist(double** myArray, int first, int last){        //appied QS for twolist
    int  piv = first;
    int pivot = myArray[first][0];

    for(int i = first+1 ; i <= last ; i++){
        if(myArray[i][0] <= pivot)
        {
            swap(myArray[i][0], myArray[piv][0]);
            swap(myArray[i][1], myArray[piv][1]);
            piv++;
        }
    }
    swap(myArray[piv][0], myArray[first][0]);
    swap(myArray[piv][1], myArray[first][1]);
    return piv;
}
