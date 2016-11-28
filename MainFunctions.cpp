#include "mainSample.h"

/*void CLI(ifstream& inputFile, ofstream& outputFile, Conf* myConf, Metrics* myMetric)
{

	int initChoice, assignChoice, updateChoice;

	cout << "Welcome to Clustering testing simulation!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl << endl;
	cout << "Set fraction : " << myConf->clarans_set_fraction << endl;
	cout << "Metric : " << myMetric->metric_space << endl;

	//INTERFACE FOR CHOOSING FILES (?)
	do
	{
		//If input file is given from command line.
		if (inParameter) 
		{
			inParameter = false;
		}
		else 
		{
			cout << "Please give an input file: ";
			cin >> filename;
			inputFile.open(filename.c_str());
			if (inputFile == NULL)
			{
				cout << "You've given a wrong input file. " << endl;
				exit(1);
			}
			else
			{
				cout << "File : " << filename << " opened successfully!" << endl << endl;
			}
			inputFile >> metric_space;  //Read "@metric space"
			inputFile >> metric_space;	//Read etc, "hamming"

			if (strcmp(metric_space.c_str(), "euclidean") == 0)
			{
				inputFile >> metric;  	//Read "@metric space"
				inputFile >> metric;	//Read etc, "hamming"
			}
		}
		//If configuration file is given from command line.
		if (confParameter) 
		{
			confParameter = false;
		}
		else 
		{
			cout << "Please give a configuration file: ";
			cin >> filename;
			conFile.open(filename.c_str());		
			if (conFile == NULL)
			{
				cout << "You've given a wrong configuration file. " << endl;
				exit(1);
			}
			else
			{
				cout << "File : " << filename << " opened successfully!" << endl << endl;
			}
		}
		//If output file is given from command line.
		if (outParameter) 
		{
			outParameter = false;
		}
		else
		{
			cout << "Please give an output file: ";
			cin >> filename;
			outputFile.open(filename.c_str());
			if (outputFile == NULL)
			{
				cout << "You've given a wrong input file. " << endl;
				exit(1);
			}
			else
			{
				cout << "File : " << filename << " opened successfully!" << endl << endl;
			}
		}


	}while...


	cout << "Please type an algorithm for Initialization : " << endl;
	cout << "1. K-medoids++" << endl;
	cout << "2. Concentrate" << endl;
	cin >> initChoice;
	cout << endl;
	cout << "Please type an algorithm for Assignment : " << endl;
	cout << "1. PAM" << endl;
	cout << "2. LSHReverse" << endl;
	cin >> assignChoice;
	cout << endl;
	cout << "Please select an algorithm for Update : " << endl;
	cout << "1. Llyod's" << endl;
	cout << "2. CLARANS" << endl;
	cin >> updateChoice;
	cout << endl;

	if (strcmp(myMetric->metric_space.c_str(), "hamming") == 0)
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

	}
}*/


template <typename T>
ListData<T>* ReadFiles(ifstream& inputFile, Metrics* myMetric, int* N, double** distanceMatrix)
{ 

	
	
	
	if (strcmp(myMetric->metric_space.c_str(), "hamming") == 0)
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

	}
}