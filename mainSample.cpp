#include "mainSample.h"

int main(int argc, char **argv)
{
	int initChoice;
	int assignChoice;
	int updateChoice;
	int* centroids;
	ClusterTable* clusterTable;
	int** clusterAssign;
	double** distance_matrix;
	string GARBAGE;
	string choice;
	string filename;
	ifstream inputFile;
	ifstream conFile;
	ofstream outputFile;
	Conf* myConf = new Conf();
	Metrics* myMetric = new Metrics();
	bool completeFlag = false;
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
			else if (strcmp(argv[i], "-complete") == 0)
			{
				completeFlag = true;
			}
			else
			{
				cout << "You've given wrong input" <<endl;
				return -1;
			}
		}
	}


	//bitset<64> thanasis;
	//cout << "geia soy thanasis : " << thanasis << endl;
	// cout << "AAAAAANTE : " << myMetric->point_number <<endl;
	// cout << "paw gia to distance" << endl;
	// distance_matrix = new double*[myMetric->point_number];		//distance matrix creation
	// for (int i = 0; i < myMetric->point_number; i++) {
	// 	distance_matrix[i] = new double[myMetric->point_number];
	// }
	// cout << "ekana to distance" << endl;
	// centroids = new int[myMetric->point_number];
	// cout << "ekana to centroids" << endl;
	// cout << "oeoeoeoeo" <<endl;

	if (strcmp(myMetric->metric_space.c_str(), "hamming") == 0)
	{
		ListData<bitset<64> >* hammingList = new ListData<bitset<64> >();
		hammingList->ListInsertionHamming(inputFile, myMetric);

		cout << "********************************************************" << endl;
		Init_Tables(&distance_matrix, myMetric, myConf, &centroids, &clusterTable, &clusterAssign);
		cout << "********************************************************" << endl;

		hammingList->DistanceMatrixComputationHamming(myMetric, distance_matrix);
		//KMedoidsPP(myConf, myMetric, distance_matrix, centroids);
		Concentrate(myConf, myMetric, distance_matrix, centroids);
		cout << clusterAssign[0][0] <<endl;
		PAM(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign);
		if (!ALaLoyds(myConf, distance_matrix, centroids, clusterTable)) {
			cout << "done!" << endl;
		}


	}

	if (strcmp(myMetric->metric_space.c_str(), "vector") == 0)
	{
		if (strcmp(myMetric->metric.c_str(), "euclidean") == 0)
		{
			ListData<double*>* euclideanList = new ListData<double*>();
			//cout << "tralalo" <<endl;
			euclideanList->ListInsertionVector(inputFile, myMetric);

			//cout << "********************************************************" << endl;
			Init_Tables(&distance_matrix, myMetric, myConf, &centroids, &clusterTable, &clusterAssign);
			//cout << "********************************************************" << endl;
			//cout << "bururur" << euclideanList->getNode()->getKey()[0] <<endl;
			euclideanList->DistanceMatrixComputationVector(myMetric, distance_matrix);
			cout << "ekana kai to DistanceMatrixComputation" << endl;
			//KMedoidsPP(myConf, myMetric, distance_matrix, centroids);
			Concentrate(myConf, myMetric, distance_matrix, centroids);
			cout << clusterAssign[0][0] <<endl;
			PAM(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign);
			if (!ALaLoyds(myConf, distance_matrix, centroids, clusterTable)) {
				cout << "done!" << endl;
			}
		}
		
		if (strcmp(myMetric->metric.c_str(), "cosine") == 0)
		{
			ListData<double*>* cosineList = new ListData<double*>();
			cosineList->ListInsertionVector(inputFile, myMetric);

			//cout << "********************************************************" << endl;
			Init_Tables(&distance_matrix, myMetric, myConf, &centroids, &clusterTable, &clusterAssign);
			//cout << "********************************************************" << endl;
			cosineList->DistanceMatrixComputationVector(myMetric, distance_matrix);
			//KMedoidsPP(myConf, myMetric, distance_matrix, centroids);
			Concentrate(myConf, myMetric, distance_matrix, centroids);
			PAM(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign);
			if (!ALaLoyds(myConf, distance_matrix, centroids, clusterTable)) {
				cout << "done!" << endl;
			}
		}
	}

	if (strcmp(myMetric->metric_space.c_str(), "matrix") == 0)
	{
		ListData<double*>* DBHList = new ListData<double*>();
		DBHList->ListInsertionDB(inputFile, myMetric);

		cout << "********************************************************" << endl;
		Init_Tables(&distance_matrix, myMetric, myConf, &centroids, &clusterTable, &clusterAssign);
		cout << "********************************************************" << endl;

		DBHList->DistanceMatrixComputationDB(inputFile, myMetric, distance_matrix);
		Concentrate(myConf, myMetric, distance_matrix, centroids);
		//KMedoidsPP(myConf, myMetric, distance_matrix, centroids);
		PAM(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign);
		if (!ALaLoyds(myConf, distance_matrix, centroids, clusterTable)) {
			cout << "done!" << endl;
		}

	}

	SetClaransFraction(myConf, myMetric);
	//CLI(inputFile, outputFile, myConf, myMetric);

	/*cout << "for the horde : " << endl;
	cout << myConf->number_of_clusters << endl;
	cout << myConf->number_of_hash_functions << endl;
	cout << myConf->number_of_hash_tables << endl;
	cout << myConf->clarans_set_fraction << endl;
	cout << myConf->clarans_iterations << endl ;*/

	return 0;
}