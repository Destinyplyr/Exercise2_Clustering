#include "Headers.h"
#include "UtilsH.h"
#include "Algorithms.h"

void Concentrate(Conf* myConf, Metrics* myMetric, double** distanceMatrix, int* centroids)
{
	double Sum = 0;
	double* divisor;
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

	divisor = new double [myMetric->point_number];
	for (int i = 0; i < myMetric->point_number; ++i)
	{
		divisor[i] = 0;
		for (int j = 0; j < myMetric->point_number; ++j)
		{
			divisor[i] += DistanceMatrixDistance(distanceMatrix, i, j);
		}
	}

	//cout << "before for" <<endl;


	for (int i =0; i <myMetric->point_number; ++i ) {
		for (int j = 0; j < myMetric->point_number; ++j)
		{
			if ( i != j) {
				//divisor = 0;
				// for (int t = 0; t < myMetric->point_number; ++t)
				// {
				// 	divisor += DistanceMatrixDistance(distanceMatrix, j, t);
				// }
				V_s[i][0] += DistanceMatrixDistance(distanceMatrix, i, j) / divisor[j];
				//cout << "v is " << V_s[i][0] <<endl;
			}
		}
		V_s[i][1] = i;
	}
	/*double** newh = new double*[4];
	for (int i = 0; i < 4; ++i)
	{
		newh[i] = new double[2];
	}
	newh[0][0] = 4; newh[0][1] = 5;
	newh[1][0] = 1; newh[1][1] = 3;
	newh[2][0] = 3; newh[2][1] = 2;
	newh[3][0] = 57; newh[3][1] = 9;*/

	quickSort_twolist(V_s, 0, myMetric->point_number-1);
	//quickSort_twolist(newh, 0, 3);
/*	for (int i = 0; i < 4; ++i)
	{
		cout << newh[i][0] <<newh[i][1] <<endl;
	}*/
	
/*    for (int i = 0; i < myMetric->point_number ; ++i)
    {
    	cout << "V_s " << i << " - " << V_s[i][0] << " - " << V_s[i][1] <<endl;
    }*/
    for (int i = 0; i < myConf->number_of_clusters; i ++) {
        centroids[i] = V_s[i][1];
        //cout << "centroid " << i << " - " << centroids[i] << endl;
    }
}

void swap_twolist(double& a, double& b){
    double temp = a;
    a = b;
    b = temp;
}

void quickSort_twolist(double** myArray, int first, int last ){ //appied QS for twolist
    int pivot;
    if(first < last){
        pivot = parition_twolist(myArray, first, last);
/*        cout << "printarr" <<endl;
            for (int i = first; i <=last; ++i)
		    {
		    	cout << myArray[i][0] <<endl;
		    }
		    cout << "(((((((" <<endl;*/
        quickSort_twolist(myArray, first, pivot-1);
        quickSort_twolist(myArray, pivot+1, last);
    }
}


int parition_twolist(double** myArray, int first, int last){        //appied QS for twolist
    /*for (int i = first; i <= last; ++i)
    {
    	
    	cout << myArray[i][0] <<endl;
    }
    cout << "(((((((" <<endl;
	cout << "================partition" <<endl;*/
    int  piv = first;
    //cout << "piv starting: " << piv <<endl;
    double pivot = myArray[first][0];
    //cout << "pivot: " <<pivot<<endl;
    for(int i = first+1 ; i <= last ; i++){
        if(myArray[i][0] <= pivot)
        {
        	piv++;
        	//cout << "-------" <<endl;
        	//cout << "changing" <<endl;
        	//cout <<myArray[i][0] <<endl;
            swap_twolist(myArray[i][0], myArray[piv][0]);
            // cout << "with" <<endl;
            // cout <<myArray[i][0] <<endl;
            // cout << "-------" <<endl;
            swap_twolist(myArray[i][1], myArray[piv][1]);
           
            //cout << "piv: " << piv <<endl;
        }
    }
    swap_twolist(myArray[piv][0], myArray[first][0]);
    swap_twolist(myArray[piv][1], myArray[first][1]);
/*    cout << "returning piv: " <<piv <<endl;
    cout << "==================" <<endl;
    cout << "printarr" <<endl;
    for (int i = first; i <= last; ++i)
    {
    	
    	cout << myArray[i][0] <<endl;
    }
    cout << "(((((((" <<endl;*/
    return piv;
}