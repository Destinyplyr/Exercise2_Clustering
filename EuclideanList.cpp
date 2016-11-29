#include "ListData.h"
#include "DistanceMatrixFunctions.h"
#include "TrickFunctions.cpp"

using namespace std;


template <typename T>
void ListData<T>::initEuclideanList(Conf* myConf, ifstream& inputFile, double** distanceMatrix, int k, int L, int* dataLengthPointNumber, int* hashCreationDone, Hash<T>* hashTableList, int* centroids, int** clusterAssign) 
{
	string genericStr;
	string itemNos;
	string genericQuery;
	string pointStr;
	string metric;
	string GARBAGE;
	string metric_space; 
	string filename;
	string choice;
	Node<double*>* lshENN;
	Node<double*>* realENN;
	double*** v;
	double** t;
	double minOutsideDistance;
	double edis;
	double y_1, y_2, r, ID, phi;
	double Radius = 0;
	double minEBruteDistance= 99999;
	double elapsed_secs_lshe, elapsed_secs_euclidList, elapsed_secs_hashing, end_h_creation;
	double elapsed_secs_ebrute, elapsed_secs_query;
	double distance_bucketpoint_from_centroid;
	double minimumDistance = INT_MAX;
	double minDistance = INT_MAX;
	double secondBestDistance = INT_MAX;
	int** r_k;
	int* dataLength;					//dataLength is point dimension here
	int itemNumber = 0;
	int h;
	int w = 4;
	int inputFileSize = 0;
	int queryCounter = 1;
	int hashResult;
	int assigned_in_this_radius = 0;
	int minimumCentroid = -1;
	int secondBestCentroid = -1;
	clock_t begin, begin_brute, end_ebrute, begin_euclidList;
	clock_t begin_lshe_query, end_lshe_query;
	clock_t end_euclidList, begin_lsh_hashing, end_lsh_hashing;

	Node<T>* nodePtr;
	Node<T>* centroidPtr;

	std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	std::cout.precision(20);

	dataLength = new int;
	*dataLength = 0;

	double** point_to_centroid_assignment = new double*[*dataLengthPointNumber];           //[0] holds current centroid  [1] holds distance from it [2] holds second best centroid [3]  holds distance from it
	for (int i = 0; i < *dataLengthPointNumber; ++i)
	{
		point_to_centroid_assignment[i] = new double[4];
		point_to_centroid_assignment[i][0] = -1;            //init   
		point_to_centroid_assignment[i][1] = INT_MAX;
		point_to_centroid_assignment[i][2] = -1;
		point_to_centroid_assignment[i][3] = INT_MAX;
	}

	inputFile.clear();      		//Restart
	inputFile.seekg(0, ios::beg);   //Data file back from start
	begin = clock();

	inputFile >> metric_space;    	//Read "@metric space"      
	inputFile >> metric_space;    	//Read "euclidean"
	inputFile >> metric;			//Read etc, "@metric"       
	inputFile >> metric;			//Read euclidean
	inputFile >> itemNos;			//Read itemno

	getline(inputFile, genericStr);
	stringstream linestream(genericStr);
	getline(linestream, pointStr, '\t');
	while (getline(linestream, pointStr, '\t')) {			//Calculate dimension of points
		(*dataLength)++;
	}
	
	//cout << "The size of each euclidean point is: " << *dataLength << endl;
	//inputFile.clear();     			 //Restart
	//inputFile.seekg(0, ios::beg);    //Data file back from start

	v = new double**[L];
	t = new double*[L];
	r_k = new int*[L];
	for (int o = 0; o < L; ++o)
	{
		v[o] = new double*[k];
		t[o] = new double[k];
		r_k[o] = new int[k];
		for (int j = 0; j < k; j++) {
			v[o][j] = new double[*dataLength];
		}
	}

	for (int o = 0; o < L; o++) {		//For every hash table
		for (int j = 0; j < k; j++) {	//For every h
   		for (int i = 0; i < *dataLength; i++) {		//[-1,1]
   			//int r = M + (rand() / RAND_MAX + 1.0)*(N - M+1);        //generate uniform  [M, N]: we want v numbers from -1 to 1
   			r = ((double)rand() / (double)RAND_MAX);		//Radius smaller than 1
   			//cout <<  " R  : " << r << endl;
   			y_1 = -1 + ((double)rand() / (double)RAND_MAX)*(2);
   			//cout <<  " y_1  : " << y_1 << endl;
   			y_2 = sqrt(abs((int)(r - pow(y_1, 2))));			// r = y_1^2 + y_2^2
   			//cout <<  " y_2  : " << y_2 << endl;
   			v[o][j][i] = y_1 * sqrt((-2 * log(r))/r);	//Every coordinate follows a N(0,1) distribution
   			//cout << "voji = " << v[o][j][i] <<endl;
   		}
   		t[o][j] = 0 + ((double)rand() / (double)RAND_MAX)*(w);	//[0,w)
   		r_k[o][j]  = rand();
   		//cout << "r_k : " << r_k[o][j] << endl;
		}
	}

    end_h_creation = clock();

	if (k > *dataLength) 
	{
		cout << "Warning: LSH does not support so many mini-hashing functions. Switching to highest number available" << endl;
		k = *dataLength;
	}
/*
    begin_euclidList = clock();
	inputFile.clear();      		//Restart
	inputFile.seekg(0, ios::beg);   //Data file back from start

	inputFile >> metric_space;    	//Read "@metric space"      
	inputFile >> metric_space;    	//Read "euclidean"
	inputFile >> metric;			//Read etc, "@metric"       
	inputFile >> metric;			//Read euclidean
	int index = 0;
	//ListData<double*>* euclidList = new ListData<double*>(); 
	double* point;					//New point
	/*getline(inputFile, genericStr);
	itemNumber = 0;
	while(getline(inputFile, genericStr)) {					//For every point
        itemNumber += 1;
			index = 0;
   		stringstream linestream(genericStr);
   		getline(linestream, itemNos, '\t');        			//ITEMNO
   		point = new double[*dataLength];
   		while (getline(linestream, pointStr, '\t'))
   		{		//Calculate dimension of points
   			point[index] = strtod(pointStr.c_str(), NULL);
   			//cout << "pointstr:" <<point[index] << " index: " << index <<endl;
   			index++;
   		}
   		if (!euclidList->EuclideanDuplicate(point, *dataLength)) {
   			euclidList->Insert(point, itemNumber, itemNos);
   		}
   		inputFileSize++;
	}*/
		//euclidList->PrintData();
	end_euclidList = clock();
	elapsed_secs_euclidList = (double) (end_euclidList - begin_euclidList) / CLOCKS_PER_SEC;

	begin_lsh_hashing = clock();
	long long  tableSize = (*dataLengthPointNumber) / 8;		//n/8 for LSH
	//cout << "tableSize :" << tableSize << endl;
	long long M = pow(2, 32) - 5;
	//cout << "M :" << M << endl;
	//Hash<double*>* hashTableList = new Hash<double*>[L];

	if (*hashCreationDone == 0)		//create the
	{
		for (int o = 0; o < L; ++o)
		{
			hashTableList[o].initHash(tableSize);
		}
		nodePtr = this->getNode();
		while (nodePtr != NULL) {				//For every node in the euclidList
			for (int o = 0; o < L; ++o){		//For every hashtable
				ID = 0;
				for (int j = 0; j < k; ++j)		//For every h
				{
					//cout << "dot product :key:" << nodePtr->getKey()[0] << " voj: " << v[o][j][0] <<endl;
					//cout << "toj: " << t[o][j] <<endl;
 					h =  (int)floor((dot_product(nodePtr->getKey(), v[o][j], *dataLength) + t[o][j]) / w);
					//cout << "h :" << h << endl;
					ID += (r_k[o][j] * h) % M;
					//cout << "ID :" << ID << endl;
				}
				phi = abs((long)ID % tableSize);
				//cout << "phi :" << phi << endl;
				hashTableList[o].Insert(phi, nodePtr->getKey(), ID, nodePtr->getItemNo(), nodePtr->getItemName());
			}
				nodePtr = nodePtr->getNext();
		}
	}

	nodePtr = this->getNode();

/*	while (nodePtr != NULL) {				//For every node in the euclidList
		for (int o = 0; o < L; ++o){		//For every hashtable
			ID = 0;
			for (int j = 0; j < k; ++j)		//For every h
			{
				h =  (int)floor((dot_product(nodePtr->getKey(), v[o][j], *dataLength) + t[o][j]) / w);
				//cout << "h :" << h << endl;
				ID += (r_k[o][j] * h) % M;
				//cout << "ID :" << ID << endl;
			}
			phi = abs((long)ID % tableSize);
			//cout << "phi :" << phi << endl;
			hashTableList[o].Insert(phi, nodePtr->getKey(), ID, nodePtr->getItemNo(), nodePtr->getItemName());
		}
			nodePtr = nodePtr->getNext();
	}*/
		//hashTableList[0].printHash();
	end_lsh_hashing = clock();
	elapsed_secs_hashing = (double) (end_lsh_hashing - begin_lsh_hashing) / CLOCKS_PER_SEC;


	for (int o = 0; o < L; ++o) //re-initialize hashTable //for every hash table
    {
    	hashTableList[o].ReInitializeHashTable(L, tableSize);
    }

    Radius = FindRadiusForAssignment(myConf, distanceMatrix, centroids);


	TrickList<double*>* trickList = new TrickList<double*>();		//The first item of the TrickList is the info head

	for (int o = 0; o < L; ++o) 	//for every hashtable
	{
		//cout << "For hash table " << o << " : " << endl;
		//REMERMBER TO clear current hashtable off assignments
		hashResult = 0;
		do
		{
			assigned_in_this_radius = false;
			for (int q = 0; q < myConf->number_of_clusters; q++) 	//for every centroid 
			{
				//cout << "For centroid : " << q << " : " << endl;
				hashResult = 0;

				nodePtr = this->getNode();		//nodePtr holds current centroid
				while(nodePtr->getItemNo() != centroids[q])
				{
					nodePtr = nodePtr->getNext();
				}
				//euclidean hashing for centroid
				ID = 0;
				for (int j = 0; j < k; ++j)		//For every h
				{
					h =  (int)floor((dot_product(nodePtr->getKey(), v[o][j], *dataLength) + t[o][j]) / w);
					ID += (r_k[o][j] * h) % M;
				}
				phi = abs((long)ID % tableSize);	//hashResult

				//hashTableList[o].getHashTable()[(int)phi].InsertTrick((int)ID, trickList, L);	//creates TrickList from current bucket
				//^^^
				//tricklist is not necessary (is generally obsolete) in this implementation

				/*for (int i=0; i < k; i++)
				{
					//Current index regarding the Hamming string - using the miniHash that was used before
					currentIndex = miniHashIndexList[o][i];
					nodePtr = this->getNode();
					while (nodePtr->getItemNo() != centroids[q])
					{
						nodePtr = nodePtr->getNext();
					}   
					hashResult += pow (2, i) * (nodePtr->getKey()[currentIndex] != 0);    //Creates the binary as an int
					cout << "Inserting in hamming hashtable: curr Hash result: " << hashResult <<endl;
				}*/
				//cout << "------->  Hash result : " << hashResult <<endl;]

				//listNode = hashTableList[l].getHashTable()[hashResult].getBucket();
				//listBucketTable[l] = listNode;


				//cout << "The hash result : " << phi << endl;

				centroidPtr = nodePtr;		//centroidPtr now holds the centroid
				nodePtr = hashTableList[o].getHashTable()[(int)phi].getBucket();		//nodePtr holds bucket items now
				if (nodePtr == NULL)
				{
					//cout << "nodePtr after hashing centroid is NULL";
					//exit(15);
				}
				while (nodePtr != NULL && nodePtr->getFlagAsAssigned() != 1)
				{
					// cdis =  point[nodePtr->getItemNo()];       
					//             if ((cdis <= Radius) && (Radius > 0 )) {
					//                 outputFile << "--"<<nodePtr->getItemName() <<endl;
					// }
					// if ((cdis < minLSHDistance) && (cdis != 0))
					// {
					//  minLSHDistance = cdis;
					//  minimumNode = nodePtr;
					// }
					if (nodePtr->getG() == phi) 		//g is ID - use points only with the same ID
					{
						distance_bucketpoint_from_centroid = DistanceMatrixDistance(distanceMatrix, nodePtr->getItemNo(), centroids[q]);
						//cout << "Distance bucket from centroid : " << distance_bucketpoint_from_centroid << endl;
						//cout << "Radius : " << Radius << endl;
						if (distance_bucketpoint_from_centroid <= Radius)       //if inside radius
						{
							// if(point_to_centroid_assignment[nodePtr->getItemNo()] != -1)        //case that current point has been assigned on ANOTHER HASHTABLE but not yet on this one
							// {	
							//cout << "It's better than Radius" << endl;
							if (distance_bucketpoint_from_centroid < nodePtr->getDistanceFromCentroid()) 		//getDistance initialized as INT_MAX
							{
								//cout << "It goes in for this centroid" << endl;
								assigned_in_this_radius = true;
								nodePtr->setSecondBestCentroid(nodePtr->getCentroid());
								nodePtr->setSecondBestDistance(nodePtr->getDistanceFromCentroid());
								nodePtr->setFlagForAssignment(1);
								nodePtr->setCentroid(centroids[q]);
								nodePtr->setDistanceFromCentroid(distance_bucketpoint_from_centroid);
							}
							//cout << "Updated!" << endl;
							// }
						}
					}
					nodePtr = nodePtr->getNext();
				}

			}
			for (int hash_bucket = 0; hash_bucket < tableSize; hash_bucket++)	//from assign in hashtable to legit assigned
			{
				//cout << "++++++++++++++++++++++++++++++++++++++++" <<endl;
				//cout << "This hash bucket : " << hash_bucket << endl;
				nodePtr = hashTableList[o].getHashTable()[hash_bucket].getBucket();		//nodePtr now holds current bucket
				while(nodePtr != NULL)
				{
					if (nodePtr->getFlagForAssignment() == 1) 
					{
						//cout << "will try to get past movetoback" <<endl;

						nodePtr->setFlagAsAssigned(1);
						hashTableList[o].MoveToBack(nodePtr->getItemNo(), hash_bucket);
						//cout << "Moved to back successfully!" << endl;
						//cout << "nodePtr->getItemNo() : " << nodePtr->getItemNo() << endl;
						if(point_to_centroid_assignment[nodePtr->getItemNo()][0] == -1)
						{
							//cout << "It was -1 (centroid - distance) and now updated to our local array : old :" << point_to_centroid_assignment[nodePtr->getItemNo()][0] << " : " << point_to_centroid_assignment[nodePtr->getItemNo()][1] << endl;
							point_to_centroid_assignment[nodePtr->getItemNo()][0] = nodePtr->getCentroid();
							point_to_centroid_assignment[nodePtr->getItemNo()][1] = nodePtr->getDistanceFromCentroid();
							//cout << "It was -1 (centroid - distance) and now updated to our local array : new :" << point_to_centroid_assignment[nodePtr->getItemNo()][0] << " : " << point_to_centroid_assignment[nodePtr->getItemNo()][1] << endl;
						}
						else 
						{
							//cout << "We have a previous assignment in our local array" <<endl;
							if(point_to_centroid_assignment[nodePtr->getItemNo()][1] > nodePtr->getDistanceFromCentroid())
							{
								//cout << "It had values before (centroid - distance) and now updated to our local array : old " << point_to_centroid_assignment[nodePtr->getItemNo()][0] << " : " << point_to_centroid_assignment[nodePtr->getItemNo()][1] << endl;
								point_to_centroid_assignment[nodePtr->getItemNo()][0] = nodePtr->getCentroid();
								point_to_centroid_assignment[nodePtr->getItemNo()][1] = nodePtr->getDistanceFromCentroid();
								if (point_to_centroid_assignment[nodePtr->getItemNo()][3] > nodePtr->getSecondBestDistance())
								{
									point_to_centroid_assignment[nodePtr->getItemNo()][2] = nodePtr->getSecondBestCentroid();
									point_to_centroid_assignment[nodePtr->getItemNo()][3] = nodePtr->getSecondBestDistance();
								}
								//cout << "It had values before (centroid - distance) and now updated to our local array : new " << point_to_centroid_assignment[nodePtr->getItemNo()][0] << " : " << point_to_centroid_assignment[nodePtr->getItemNo()][1] << endl;
							}
						}
						//cout << "assign out of assign ifs" <<endl;
					}
					//cout << "assign out of fat if" <<endl;
					nodePtr = nodePtr->getNext();
					//cout << "got next" <<endl;
				}
				//cout << "Finished assignment on matrix for bucket" <<endl;
				//cout << "++++++++++++++++++++++++++++++++++++++++" <<endl;
			}
			//cout << "Multiplying Radius" <<endl;
			Radius = Radius * 2;
		}while(assigned_in_this_radius);
	}
	for (int point_iter = 0; point_iter < *dataLengthPointNumber; point_iter++)	//leftover assignment
	{
		//cout << "Leftover : " << point_iter << endl;
		minimumDistance = numeric_limits<double>::max() ; 		//make it DOUBLE
		minimumCentroid = -1;
		if (point_to_centroid_assignment[point_iter][0] == -1 || point_to_centroid_assignment[point_iter][1] == -1)
		{
			for (int centroid_iter = 0; centroid_iter < myConf->number_of_clusters; centroid_iter++)
			{
				//cout << "Centroid : " << centroid_iter << endl;
				// distance_bucketpoint_from_centroid = DistanceMatrixDistance(distanceMatrix, nodePtr->getItemNo(), centroids[centroid_iter]);
				distance_bucketpoint_from_centroid = DistanceMatrixDistance(distanceMatrix, point_iter, centroids[centroid_iter]);
				if (distance_bucketpoint_from_centroid < minimumDistance)
				{
					secondBestCentroid = minimumCentroid;
					secondBestDistance = minimumDistance;
					minimumDistance = distance_bucketpoint_from_centroid;
					minimumCentroid = centroids[centroid_iter];
				}
			}
/*					nodePtr->setFlagForAssignment(1);		//assignment on hashtable list
			nodePtr->setCentroid(minimumCentroid);		//assignment data on node
			nodePtr->setDistanceFromCentroid(minimumDistance);

			nodePtr->setFlagAsAssigned(1);*/
			//hashTableList[o].MoveToBack(nodePtr->getItemNo(), hashResult);    SHOULD BE DONE WITH HASHING
			// point_to_centroid_assignment[nodePtr->getItemNo()][0] = nodePtr->getCentroid();
			// point_to_centroid_assignment[nodePtr->getItemNo()][1] = nodePtr->getDistanceFromCentroid();
			point_to_centroid_assignment[point_iter][0] = minimumCentroid;
			point_to_centroid_assignment[point_iter][1] = minDistance;
			point_to_centroid_assignment[point_iter][2] = secondBestCentroid;
			point_to_centroid_assignment[point_iter][3] = secondBestDistance;
		}
		//cout << "Leftover updated" << endl;
	}
	//cout << "Exiting..." << endl;
	for (int point_iter = 0; point_iter < *dataLengthPointNumber; point_iter++)	
	{
		//cout << "On point " <<point_iter <<endl;
		//cout << "changing to best : " << point_to_centroid_assignment[point_iter][0] <<endl;
		clusterAssign[point_iter][2] = point_to_centroid_assignment[point_iter][0];		//give best centroid chosen
		//cout << "changing to 2nd best : " << point_to_centroid_assignment[point_iter][2] <<endl;
		if (point_to_centroid_assignment[point_iter][2] == -1) 
		{
			clusterAssign[point_iter][1] = clusterAssign[point_iter][2];
		}
		else
		{
			clusterAssign[point_iter][1] = point_to_centroid_assignment[point_iter][2];		//give 2nd best centroid
		}
		
	}
	return;

	/*do {
   		queryCounter = 1;
		queryFile.clear();      		//Restart
		queryFile.seekg(0, ios::beg);   //Data file back from start
   		queryFile >> genericQuery;		//@Radius
   		queryFile >> Radius;			//Radius_value
   		outputFile << "Radius : " << Radius << endl;
   		//getline(queryFile, genericStr);
   		while(getline(queryFile, genericStr)) {					//For every point
   			index = 0;
	   		begin_lshe_query = clock();
	   		stringstream linestream(genericStr);
	   		getline(linestream, itemNos, '\t');       			//get item no
	   		outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  QUERY NUMBER " << queryCounter << " - " << itemNos <<" $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl << endl;
	   		point = new double[*dataLength];
	   		while (getline(linestream, pointStr, '\t')){		//Calculate dimension of points
	   			point[index] = strtod(pointStr.c_str(), NULL);
	   			//cout << "pointstr: " <<point[index] << " index: " << index <<endl;
	   			index++;
	   		}
	   		for (int o = 0; o < L; ++o){		//For every hashtable
				ID = 0;
				for (int j = 0; j < k; ++j)		//For every h
				{
					h =  (int)floor((dot_product(point, v[o][j], *dataLength) + t[o][j]) / w);
					ID += (r_k[o][j] * h) % M;
				}
				phi = abs((long)ID % tableSize);
				hashTableList[o].getHashTable()[(int)phi].InsertTrick((int)ID, trickList, L);
   			}
   			if (Radius > 0) 
            {
   				outputFile << "R NNs : " << endl;
   			}
   			lshENN = trickList->NNTrickList(point, *dataLength, outputFile, Radius, &minOutsideDistance);
   			end_lshe_query = clock();
   			elapsed_secs_query = (double) (end_lshe_query - begin_lshe_query) / CLOCKS_PER_SEC;

   			//************************ ENDED LSH EUCLIDEAN  ************************

   			// ************************ REAL NEIGHBOUR (AND TIME TAKEN) COMPUTATION WITH BRUTE FORCE ************************
   			Node<double*>* newNode = euclidList->getNode();
   			begin_brute = clock();
   			while(newNode != NULL)
   			{
   				edis = TrickList<T>::Distance(newNode->getKey(), point, *dataLength);
   				//cout << "-------> Euclidean Distance " << edis <<endl;
   				//cout << "-------> Radius  " << Radius <<endl;
   				if ((edis < minEBruteDistance) && (edis != 0))
   				{
   					minEBruteDistance = edis;
   					realENN = newNode;
   				}
   				newNode = newNode->getNext();
   				if (newNode == NULL)
   				{
   					break;
   				}
   			}

   			end_ebrute = clock();

   			//cout << "Time query : " << elapsed_secs_query << endl;
   			//cout << "Time hashing : " << elapsed_secs_hashing << endl;
   			//cout << "Time euclidList : " << elapsed_secs_euclidList << endl;

   			elapsed_secs_lshe = double (elapsed_secs_query + elapsed_secs_hashing + elapsed_secs_euclidList + end_h_creation - begin) / CLOCKS_PER_SEC;
   			elapsed_secs_ebrute = double (end_ebrute - begin_brute + elapsed_secs_euclidList + end_h_creation - begin ) / CLOCKS_PER_SEC;

   			if (lshENN != NULL){
   				outputFile << "------->  LSH NN Euclidean :  " << lshENN->getItemName() << endl;
   				outputFile << "------->  The lsh nearest neighbour for query " << queryCounter << " is within distance  : " << minOutsideDistance << endl;
   				outputFile << "------->  Time taken LSH Euclidean : " << elapsed_secs_lshe << endl << endl;
   			}
   			else {
   				outputFile << "------->  LSH NN Euclidean could not return results" << endl;
   				outputFile << "------->  Time taken LSH Euclidean : " << elapsed_secs_lshe << endl << endl;
   			}
   			outputFile << "------->  Real NN Euclidean :  " << realENN->getItemName() << endl;
   			outputFile << "------->  The real nearest neighbour for query " << queryCounter << " is within distance  : " << minEBruteDistance << endl;
   			outputFile << "------->  Time taken brute force Euclidean : " << elapsed_secs_ebrute << endl << endl;

   			outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  END OF QUERY NUMBER " << queryCounter << "  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl << endl << endl << endl;

			minEBruteDistance = 9999;			//Resetting the minimum distance
	    	realENN = NULL;
	    	lshENN = NULL;
	    	elapsed_secs_lshe = 0.0f;
	    	elapsed_secs_ebrute = 0.0f;
	    	++queryCounter;
	    	delete trickList->getNext();
	    	trickList->setNext(NULL);
   		}
		outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  $$$$$$$$$$$$$$$$$   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
		outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  END OF QUERY FILE   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
		outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  $$$$$$$$$$$$$$$$$   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;

        cout << " Press:" <<endl << "'a' - change all files (Rebuild LSH Tables)" <<endl << "'i' - change input(dataset) file (Rebuild LSH Tables)" <<endl << "'o' - change output file" <<endl << "'q' - change query file" << endl << "If you want to exit please type 'exit'" << endl;
        cin >> choice;
        if (choice.compare("a") == 0 || choice.compare("'a'") == 0) {
            break;
        }
        else if (choice.compare("i") == 0 || choice.compare("'i'") == 0) {
            break;
        }
        else if (choice.compare("o") == 0 || choice.compare("'o'") == 0) {
            cout << "Please give output file name: ";
            cin >> filename;
            outputFile.close();
            outputFile.open(filename.c_str());      
            if (outputFile == NULL)
            {
                cout << "You've given a wrong input file. " << endl;
                return;
            }
            else
            {
                cout << "File : " << filename << " opened successfully!" << endl << endl;
            }
        }
        else if (choice.compare("q") == 0 || choice.compare("'q'") == 0) {
            cout << "Please give output file name: ";
            cin >> filename;
            queryFile.close();
            queryFile.open(filename.c_str());       
            if (queryFile == NULL)
            {
                cout << "You've given a wrong input file. " << endl;
                return;
            }
            else
            {
                cout << "File : " << filename << " opened successfully!" << endl << endl;
            }
        }
        else if ((choice.compare("exit") != 0) && (choice.compare("'exit'") != 0)) {
            cout << "Command not recognised. Exiting... You lost your chance..." <<endl;
            exit(-1);
        }
	}while((choice.compare("exit") != 0) && (choice.compare("'exit'") != 0));

	for (int o = 0; o < L; ++o)
	{
		for (int j = 0; j < k; j++) {
			delete[] v[o][j];
		}

		delete v[o];
		delete t[o];
		delete r_k[o];
	}

		nodePtr = euclidList->getNode();
		while (nodePtr != NULL)
		{
			delete nodePtr->getKey();
			nodePtr = nodePtr->getNext();
		}
	delete euclidList;
	delete[] hashTableList;
	delete trickList;
	exit(1);*/
}