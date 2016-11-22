#include "Headers.h"
#include "UtilsH.h"
#include "Algorithms.h"

template <typename T>
void PAM(Conf* myConf, Metrics* myMetric, double** distanceMatrix, ListData<T>* myList, int* centroids)
{
    int* new_centroids;
    int* best_centroids;
	cout << "IN PAM" << endl;
	//struct with distance?
	for (int i = 0; i < myConf->number_of_clusters; ++i)
	{
		cout << "centroid : " << i << " is " << centroids[i] << endl;
	}

	for (int i = 0; i < myMetric->point_number; ++i)
	{
		
	}

	/*for (int i= 0; i < myMetric->point_number; ++i)
	{
		for (int j = 0; j < myMetric->point_number; ++j)
		{
			cout << "distance : " << distanceMatrix[i][centroids[i]] << endl;
		}
	}*/

}
