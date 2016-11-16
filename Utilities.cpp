#include "Headers.h"
#include "UtilsH.h"


void Init_Conf(Conf* myConf, ifstream& conFile)
{
	string GARBAGE;
	for (int i =0; i < 5; i ++) {
		if (conFile >> GARBAGE) {
			if (strcmp(GARBAGE.c_str(), "number_of_clusters:") == 0) {
				conFile >> myConf->number_of_clusters;
			}
			else if (strcmp(GARBAGE.c_str(), "number_of_hash_functions:") == 0) {
				conFile >> myConf->number_of_hash_functions;
			}
			else if (strcmp(GARBAGE.c_str(), "number_of_hash_tables:") == 0) {
				conFile >> myConf->number_of_hash_tables;
			}
			else if (strcmp(GARBAGE.c_str(), "clarans_set_fraction:") == 0) {
				conFile >> myConf->clarans_set_fraction;
			}
			else if (strcmp(GARBAGE.c_str(), "clarans_iterations:") == 0) {
				conFile >> myConf->clarans_iterations;
			}
		}
		else {
			break;
		}

		// conFile >> GARBAGE;
		// conFile >> myConf->number_of_hash_functions;
		// conFile >> GARBAGE;
		// conFile >> myConf->number_of_hash_tables;
		// conFile >> GARBAGE;
		// conFile >> myConf->clarans_set_fraction;
		// conFile >> GARBAGE;
		// conFile >> myConf->clarans_iterations;
	}
	//cout << "Information read from configuration file." << endl;
}


void Init_Metrics(Metrics* myMetric, std::ifstream& inputFile)
{
	string GARBAGE;
	string genericStr;
	string pointStr;
	int point_dimension = 0;
	int point_number = 0;
	//int point_number = 0;

	inputFile >> GARBAGE;  					//Read "@metric space"
	inputFile >> myMetric->metric_space;	//Read etc, "hamming"

	if (strcmp(myMetric->metric_space.c_str(), "vector") == 0)
	{
		inputFile >> GARBAGE;  				//Read "@metric space"
		if (strcmp(GARBAGE.c_str(), "@metric") == 0) {
			inputFile >> myMetric->metric;		//Read etc, "hamming"
			inputFile >> GARBAGE;				//read itemno to coordinate with else
		}
		else {
			myMetric->metric = "euclidean";
			//point_number++;
		}
		getline(inputFile, genericStr);
		//cout << "apo th getline katw " << genericStr << endl;
   		stringstream linestream(genericStr);
   		getline(linestream, pointStr, '\t');
   		while (getline(linestream, pointStr, '\t'))    //Calculate dimension of points
        {			
   			point_dimension++;
   		}

   		myMetric->point_dimension = point_dimension;

	}

	if (strcmp(myMetric->metric_space.c_str(), "hamming") == 0) {
		inputFile >> GARBAGE;		//read itemno
		inputFile >> genericStr;	//read an item
		myMetric->point_dimension = genericStr.length();
	}

	if (strcmp(myMetric->metric_space.c_str(), "matrix") == 0) {
		inputFile >> GARBAGE;		//read itemno
        getline(inputFile, genericStr);
        stringstream linestream2(genericStr);
        while (getline(linestream2, pointStr, ',')) {       //Calculate dimension of points
            ++point_number;
        }
        myMetric->point_number = point_number;
	}	

 	inputFile.clear();      		//Restart
 	inputFile.seekg(0, ios::beg);   //Data file back from start
 	

 	//cout << "Pount dum L : " << myMetric->point_dimension << endl;
}



