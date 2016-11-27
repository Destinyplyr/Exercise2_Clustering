#include "mainSample.h"

int main(int argc, char **argv)
{
	int initChoice;
	int assignChoice;
	int updateChoice;
	int* centroids;
	int point_number;
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
	bool first_time_lsh;
	int L, k;
	L = 5;
	k = 4;
	int hashCreationDone;
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

		//cout << "********************************************************" << endl;
		clusterTable->Init_Tables(&distance_matrix, myMetric, myConf, &centroids, &clusterTable, &clusterAssign);
		SetClaransFraction(myConf, myMetric);
		//cout << "********************************************************" << endl;

		hammingList->DistanceMatrixComputationHamming(myMetric, distance_matrix);
		KMedoidsPP(myConf, myMetric, distance_matrix, centroids);
		//Concentrate(myConf, myMetric, distance_matrix, centroids);
		/*cout << "==================" << endl << "PRINTING CLUSTERS IN mainSample BEFORE CLARANS : " <<endl;
		for (int w = 0; w <myConf->number_of_clusters; w++) {
			cout << centroids[w] << " ";
		}*/

		//exit(1);
		//cout << clusterAssign[0][0] <<endl;
		//PAM(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign);
		Hash<bitset<64> >* hashTableList = new Hash<bitset<64> >[L]();      //Na min orizetai se kathe iteration tou update, giati xanaorizetai
		if (first_time_lsh == true) 
		{
			first_time_lsh = false;
			hashCreationDone = 0;
			point_number = myMetric->point_number;
			hammingList->initHammingLSHManagement(myConf, inputFile, distance_matrix, k , L, &(point_number), &hashCreationDone, hashTableList, centroids, clusterAssign);
		}
		delete clusterTable;
		clusterTable = new ClusterTable(myConf->number_of_clusters);
		clusterTable->CreateClusterTableFromClusterAssign(myConf, myMetric,clusterAssign, centroids);
		if (!ALaLoyds(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign)) {
		 	cout << "done!" << endl;
		}
		//CLARANS(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign);
		//CLARA( myConf,  myMetric, distance_matrix, centroids, clusterTable, clusterAssign);
		cout << "==================" << endl << "PRINTING CLUSTERS IN mainSample Before PrintingSilhouette : " <<endl;
		for (int w = 0; w <myConf->number_of_clusters; w++) {
			cout << centroids[w] << " ";
		}
		cout <<endl;
		clusterTable->PrintingSilhouette(myConf, distance_matrix, centroids, clusterAssign);
		delete clusterTable; //DELETE CLUSTER TABLE (case lsh/dbh)
	}


	if (strcmp(myMetric->metric_space.c_str(), "vector") == 0)
	{
		if (strcmp(myMetric->metric.c_str(), "euclidean") == 0)
		{
			ListData<double*>* euclideanList = new ListData<double*>();
			//cout << "tralalo" <<endl;
			euclideanList->ListInsertionVector(inputFile, myMetric);

			//cout << "********************************************************" << endl;
			clusterTable->Init_Tables(&distance_matrix, myMetric, myConf, &centroids, &clusterTable, &clusterAssign);
			SetClaransFraction(myConf, myMetric);
			//cout << "********************************************************" << endl;
			//cout << "bururur" << euclideanList->getNode()->getKey()[0] <<endl;
			euclideanList->DistanceMatrixComputationVector(myMetric, distance_matrix);
			//cout << "ekana kai to DistanceMatrixComputation" << endl;
			KMedoidsPP(myConf, myMetric, distance_matrix, centroids);
			//Concentrate(myConf, myMetric, distance_matrix, centroids);
			//cout << clusterAssign[0][0] <<endl;
			// PAM(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign);
			Hash<double*>* hashTableList = new Hash<double*>[L]();      //Na min orizetai se kathe iteration tou update, giati xanaorizetai
			if (first_time_lsh == true) 
			{
				first_time_lsh = false;
				hashCreationDone = 0;
				point_number = myMetric->point_number;
				euclideanList->initEuclideanList(myConf, inputFile, distance_matrix, k , L, &(point_number), &hashCreationDone, hashTableList, centroids, clusterAssign);
			}
			delete clusterTable;
			clusterTable = new ClusterTable(myConf->number_of_clusters);
			clusterTable->CreateClusterTableFromClusterAssign(myConf, myMetric,clusterAssign, centroids);
			if (!ALaLoyds(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign)) {
			 	cout << "done!" << endl;
			}
			//CLARANS(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign);
			//CLARA( myConf,  myMetric, distance_matrix, centroids, clusterTable, clusterAssign);
			cout << "==================" << endl << "PRINTING CLUSTERS IN mainSample Before PrintingSilhouette : " <<endl;
			for (int w = 0; w <myConf->number_of_clusters; w++) {
				cout << centroids[w] << " ";
			}
			cout <<endl;
			clusterTable->PrintingSilhouette(myConf, distance_matrix, centroids, clusterAssign);
			delete clusterTable; //DELETE CLUSTER TABLE (case lsh/dbh)
		}
		
		if (strcmp(myMetric->metric.c_str(), "cosine") == 0)
		{
			ListData<double*>* cosineList = new ListData<double*>();
			cosineList->ListInsertionVector(inputFile, myMetric);
			//cout << "********************************************************" << endl;
			clusterTable->Init_Tables(&distance_matrix, myMetric, myConf, &centroids, &clusterTable, &clusterAssign);
			SetClaransFraction(myConf, myMetric);
			//cout << "********************************************************" << endl;
			cosineList->DistanceMatrixComputationVector(myMetric, distance_matrix);
			KMedoidsPP(myConf, myMetric, distance_matrix, centroids);
			//Concentrate(myConf, myMetric, distance_matrix, centroids);
			Hash<double*>* hashTableList = new Hash<double*>[L]();      //Na min orizetai se kathe iteration tou update, giati xanaorizetai
			if (first_time_lsh == true) 
			{
				first_time_lsh = false;
				hashCreationDone = 0;
				point_number = myMetric->point_number;
				cosineList->initCosineList(myConf, inputFile, distance_matrix, k , L, &(point_number), &hashCreationDone, hashTableList, centroids, clusterAssign);
			}
			delete clusterTable;
			clusterTable = new ClusterTable(myConf->number_of_clusters);
			clusterTable->CreateClusterTableFromClusterAssign(myConf, myMetric,clusterAssign, centroids);
			// PAM(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign);
			if (!ALaLoyds(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign)) {
			 	cout << "done!" << endl;
			}
			//CLARANS(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign);
			//CLARA( myConf,  myMetric, distance_matrix, centroids, clusterTable, clusterAssign);
			clusterTable->PrintingSilhouette(myConf, distance_matrix, centroids, clusterAssign);
			delete clusterTable; //DELETE CLUSTER TABLE (case lsh/dbh)
		}
	}

	if (strcmp(myMetric->metric_space.c_str(), "matrix") == 0)
	{
		ListData<double>* DBHList = new ListData<double>();
		DBHList->ListInsertionDB(inputFile, myMetric);

		cout << "********************************************************" << endl;
		clusterTable->Init_Tables(&distance_matrix, myMetric, myConf, &centroids, &clusterTable, &clusterAssign);
		SetClaransFraction(myConf, myMetric);
		cout << "********************************************************" << endl;

		DBHList->DistanceMatrixComputationDB(inputFile, myMetric, distance_matrix);
		Concentrate(myConf, myMetric, distance_matrix, centroids);
		//KMedoidsPP(myConf, myMetric, distance_matrix, centroids);
		// PAM(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign);
		Hash<double>* hashTableList = new Hash<double>[L]();      //Na min orizetai se kathe iteration tou update, giati xanaorizetai
		if (first_time_lsh == true) 
		{
			first_time_lsh = false;
			hashCreationDone = 0;
			point_number = myMetric->point_number;
			DBHList->initDBHManagement(myConf, inputFile, distance_matrix, k , L, &(point_number), &hashCreationDone, hashTableList, centroids, clusterAssign);
		}
		delete clusterTable;
		clusterTable = new ClusterTable(myConf->number_of_clusters);
		clusterTable->CreateClusterTableFromClusterAssign(myConf, myMetric,clusterAssign, centroids);
		if (!ALaLoyds(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign)) {
		 	cout << "done!" << endl;
		}
		//CLARANS(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign);
		//CLARA( myConf,  myMetric, distance_matrix, centroids, clusterTable, clusterAssign);
		//cout << "paei na kanei to print" << endl;
		//clusterTable->PrintCluster(0);
		//cout << "EKANE TO PRINT" << endl;
		clusterTable->PrintingSilhouette(myConf, distance_matrix, centroids, clusterAssign);
		delete clusterTable; //DELETE CLUSTER TABLE (case lsh/dbh)
		

		
		//delete DBHList;
		//continue;

	}

	
	//CLI(inputFile, outputFile, myConf, myMetric);

	/*cout << "for the horde : " << endl;
	cout << myConf->number_of_clusters << endl;
	cout << myConf->number_of_hash_functions << endl;
	cout << myConf->number_of_hash_tables << endl;
	cout << myConf->clarans_set_fraction << endl;
	cout << myConf->clarans_iterations << endl ;*/

	return 0;
}