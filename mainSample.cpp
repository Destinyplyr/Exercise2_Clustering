#include "mainSample.h"

int main(int argc, char **argv)
{

	int number_of_clusters;
	int number_of_hash_functions = 4;
	int number_of_hash_tables = 5;
	int clarans_set_fraction = 0;
	int clarans_iterations = 2;
	int initChoice;
	int assignChoice;
	int updateChoice;
	double** distance_matrix;
	string GARBAGE;
	string choice;
	string filename;
	ifstream inputFile;
	ifstream conFile;
	ofstream outputFile;
	Conf* myConf = new Conf();
	Metrics* myMetric = new Metrics();

	//bool outParameter = false, inParameter = false, confParameter = false;

	std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	std::cout.precision(20);
	srand (time(NULL));

	if (argc > 1)
	{
		if (argc % 2 == 0)
		{
			cout << "Missing the correct number of parameters" << endl;
			cout << "Suggested use: $./medoids –d <input file> –c <configuration file> -ο <output file>" << endl;
			return -1;
		}
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-d") == 0)
			{
				inputFile.open(argv[i+1]);	//Input file comes next on argv
				if (inputFile == NULL)
				{
					cout << "You've given a wrong input file. " << endl;
					exit(1);
				}
				else
				{
					cout << "File : " << argv[i+1] << " opened successfully!" << endl << endl;
					//inParameter = true;
				}
				
				Init_Metrics(myMetric, inputFile);
				i++;
			}
			else if (strcmp(argv[i], "-c") == 0)
			{
				conFile.open(argv[i+1]);	//Configuration file comes next on argv
				if (conFile == NULL)
				{
					cout << "You've given a wrong configuration file. " << endl;
					exit(1);
				}
				else
				{
					cout << "File : " << argv[i+1] << " opened successfully!" << endl << endl;
					//confParameter = true;
				}
				Init_Conf(myConf, conFile);
				i++;
			}
			else if (strcmp(argv[i], "-o") == 0)
			{
				outputFile.open(argv[i+1]);		//Output file comes next on argv
				if (outputFile == NULL)
				{
					cout << "You've given a wrong output file. " << endl;
					exit(1);
				}
				else
				{
					cout << "File : " << argv[i+1] << " opened successfully!" << endl << endl;
					//outParameter = true;
				}

				i++;
			}
			else
			{
				cout << "You've given wrong input" <<endl;
				return -1;
			}
		}
	}


	bitset<64> thanasis;
	cout << "geia soy thanasis : " << thanasis << endl;

	if (strcmp(myMetric->metric_space.c_str(), "hamming") == 0)
	{
		ListData<string>* hammingList = new ListData<string>();
		//hammingList->ListInsertionHamming(inputFile, myMetric);
		//hammingList->DistanceMatrixComputation(myMetric, distance_matrix);
	}

	if (strcmp(myMetric->metric_space.c_str(), "vector") == 0)
	{
		if (strcmp(myMetric->metric.c_str(), "euclidean") == 0)
		{
			ListData<double*>* euclideanList = new ListData<double*>();
			euclideanList->ListInsertionVector(inputFile, myMetric);
			euclideanList->DistanceMatrixComputationVector(myMetric, distance_matrix);

		}
		
		if (strcmp(myMetric->metric.c_str(), "cosine") == 0)
		{
			ListData<double*>* cosineList = new ListData<double*>();
			cosineList->ListInsertionVector(inputFile, myMetric);
			cosineList->DistanceMatrixComputationVector(myMetric, distance_matrix);
		}
	}

	if (strcmp(myMetric->metric_space.c_str(), "matrix") == 0)
	{
		ListData<double*>* DBHList = new ListData<double*>();
		DBHList->ListInsertionDB(inputFile, myMetric);
		DBHList->DistanceMatrixComputationDB(inputFile, myMetric, distance_matrix);
	}


	//CLI(inputFile, outputFile, myConf, myMetric);

	return 0;
}