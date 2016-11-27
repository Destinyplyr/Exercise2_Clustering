#include "ListData.h"
#include "MathFunctions.h"
#include "DistanceMatrixFunctions.h"

using namespace std;


template <typename T>                                                                                           //dataLength is number of points
void ListData<T>::initDBHManagement(Conf* myConf, ifstream& inputFile, double** distanceMatrix, int k, int L, int* dataLength, int* hashCreationDone, Hash<double>* hashTableList, int* centroids, int** clusterAssign) 
{
	string genericStr;
	string line;
	string genericQuery;
	string pointStr;
	string metric;
	string GARBAGE;
	string metric_space;   
	string* itemName;
	string filename;
	string choice;
	double*** h;
	double* h_x1_x2;
	double* point;
	double cdis;
	double Radius = 0;
	double elapsed_secs_lshc;
	double elapsed_secs_brutec;
	double d_x1_x2, h_x1_x2_x;
	double minCBruteDistance= 99999;
	double minLSHDistance = 999999;
	double minDistance;
	double minimumDistance;
	double secondBestDistance;
	double distance_bucketpoint_from_centroid = 0;
	int lshCNN = 0;
	int realCNN = 0;
	int ind = 0;
	int hashResult = 0;
	int index = 0;
	int queryCounter = 1;
	int tableSize;
	int minimumCentroid;
	int secondBestCentroid;
	Node<double>* nodePtr;
	Node<double>* minimumNode = NULL;

	bool assigned_in_this_radius = false;

	clock_t begin, begin_brute, end_brute, end_Matrix_insert, end_h_creation;
	clock_t begin_lsh_hashing, end_lsh_hashing, begin_h_creation;
	clock_t begin_lsh_query, end_lsh_query;

	double** point_to_centroid_assignment = new double*[*dataLength];           //[0] holds current centroid  [1] holds distance from it [2] holds second best centroid [3]  holds distance from it
	for (int i = 0; i < *dataLength; ++i)
	{
		point_to_centroid_assignment[i] = new double[4];
		point_to_centroid_assignment[i][0] = -1;            //init   
		point_to_centroid_assignment[i][1] = INT_MAX;
		point_to_centroid_assignment[i][2] = -1;
		point_to_centroid_assignment[i][3] = INT_MAX;
	}

	std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	std::cout.precision(20);
/*	inputFile.clear();              //Restart
	inputFile.seekg(0, ios::beg);   //Data file back from start
	begin = clock();
	inputFile >> metric_space;      //Read "@metric space"    
	inputFile >> metric_space;      //Read "matrix"
	inputFile >> genericStr;        //Read items
	getline(inputFile, genericStr);
	stringstream linestream(genericStr);
	while (getline(linestream, pointStr, ',')) 
	{      //calculate dimension of points
		(*dataLength)++;
	}*/
	

	//cout << "The number of points is: " << *dataLength <<  endl;
	inputFile.clear();              //Restart
	inputFile.seekg(0, ios::beg);   //Data file back from start
	itemName = new string[*dataLength];
	inputFile >> metric_space;      //Read "@metric space"     
	inputFile >> metric_space;      //Read "matrix"
	inputFile >> genericStr;        //Read items
	getline(inputFile, genericStr);
	stringstream linestream2(genericStr);
	while (getline(linestream2, pointStr, ',')) //Calculate dimension of points
	{       
		itemName[ind] = pointStr;
		ind++;
	}

	tableSize = (*dataLength) / 8;
	//!!!!!!!!GIVE DISTANCE MATRIX
	// distanceMatrix = new double*[*dataLength];
	// for (int i= 0; i <*dataLength; i++) {
	//     distanceMatrix[i] = new double[*dataLength];
	// }

	// //INSERT MATRIX
	// inputFile >> GARBAGE;       //Read "@metric space"      
	// inputFile >> GARBAGE;       //Read "matrix"
	// inputFile >> GARBAGE;      //Read @item

	// getline(inputFile, GARBAGE);
	// for (int i = 0; i < *dataLength; i++) {
	//     getline(inputFile, line);
	//     stringstream linestream(line);
	//     for (int j= 0 ; j< *dataLength; j++ ) {
	//             getline(linestream, pointStr, '\t');
	//             distanceMatrix[i][j] = strtod(pointStr.c_str(), NULL);
	//     }
	// }
	end_Matrix_insert = clock();
	begin_h_creation = clock();

	h = new double**[L];
	h_x1_x2 = new double[*dataLength];
	for (int o = 0; o < L; ++o)
	{
		h[o] = new double*[k];
		for (int j = 0; j < k; j++) 
		{
			h[o][j] = new double[4];             //x1,x2,t1,t2
		}
	}

	for (int o = 0; o < L; o++)         //for every hash table
	{   
		for (int j = 0; j < k; j++) 		//for every h
		{ 
			h[o][j][0] = floor(((double)rand() / (double)RAND_MAX)*((double)(*dataLength))); //x_1
			h[o][j][1] = floor(((double)rand() / (double)RAND_MAX)*((double)(*dataLength))); //x_2
			d_x1_x2 = pow(DistanceMatrixDistance(distanceMatrix, h[o][j][0], h[o][j][1]), 2);
			for (int u = 0; u < *dataLength; u++) {
				h_x1_x2[u] = (pow(DistanceMatrixDistance(distanceMatrix, u, h[o][j][0]),2) + pow(DistanceMatrixDistance(distanceMatrix, u, h[o][j][1]),2) - d_x1_x2)/(2*d_x1_x2);
			}
			quickSort(h_x1_x2, 0, (*dataLength)-1);
			if ((*dataLength) %2 == 0) {
				h[o][j][2] = h_x1_x2[(*dataLength) / 2];//t1
			}
			else {
				h[o][j][2] = 0.5* (h_x1_x2[(*dataLength) / 2] + h_x1_x2[((*dataLength) / 2)-1]) ;//t1
			}
			h[o][j][3] = numeric_limits<double>::max() ; //t_2
		}
	}

/*  	if (k > *dataLength) 
  	{
	  	cout << "Warning: LSH does not support so many mini-hashing functions. Switching to highest number available" << endl;
		k = *dataLength;
  	}*/

  	//cout << "The size of each hamming code is: " << *dataLength <<endl;
 	inputFile.clear();              //Restart
  	inputFile.seekg(0, ios::beg);   //Data file back from start

	end_h_creation = clock();
  	begin_lsh_hashing = clock();
	//PERASE HASHTABLELIST kai FLAG hashcreationdone
	if (*hashCreationDone == 0)
	{
		for (int o = 0; o < L; ++o)
		{
			//hashTableList[o].initHash(k, metric_space);
			hashTableList[o].initHash(tableSize);//, metric_space);
		}
		for (int u = 0; u <*dataLength; u++) {  //For every point
			for (int o = 0; o < L; ++o){        //For every hashtable
				hashResult = 0;
				for (int i=0; i < k; i++) {
					d_x1_x2 = pow(DistanceMatrixDistance(distanceMatrix, h[o][i][0], h[o][i][1]), 2);
					h_x1_x2_x = (pow(DistanceMatrixDistance(distanceMatrix, u, h[o][i][0]),2) + pow(DistanceMatrixDistance(distanceMatrix, u, h[o][i][1]),2) - d_x1_x2)/(2*d_x1_x2);
					if ((h_x1_x2_x >= h[o][i][2])&& (h_x1_x2_x <= h[o][i][3]) ) {
						hashResult += pow (2, i);
						if (tableSize < pow(2,k)) 		//VERY CAREFUL - REVIEW THIS!!! //pow(2, k) number of buckets on normal dbh
						{
							hashResult = hashResult % 2;
						}
					}
				}//int hashResult, T newItem, int g, int itemno, string itemName
				cout << "Point " << u << " Hashtable "<< o <<" Building hashTable: Inserting in bucket: " <<hashResult <<endl;
				hashTableList[o].Insert(hashResult, u, hashResult, u, itemName[u]);
				cout << " ----> Checking insert: " << hashTableList[o].getHashTable()[hashResult].getBucket()->getItemNo() <<endl;
			}
		}
		*hashCreationDone = 1;
	}
	for (int o = 0; o < L; ++o) //re-initialize hashTable //for every hash table
	{
		hashTableList[o].ReInitializeHashTable(L, tableSize);
	}
	  	//end_lsh_hashing = clock();

		//do {
			//queryCounter = 1;
		  	//begin_lsh_query = clock();
		 	//    queryFile.clear();              //Restart
		 	//    queryFile.seekg(0, ios::beg);   //Data file back from start
		  	// queryFile >> genericQuery;     //@Radius
		  	// queryFile >> Radius;         //Radius_value
		  	// queryFile >> genericStr;     //Read itemno
		 	//    outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  QUERY NUMBER " << queryCounter << " - " << genericStr << " $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl << endl;
		  	//while(getline(queryFile, genericStr)) {





			Radius = FindRadiusForAssignment(myConf, distanceMatrix, centroids);
			/*minDistance = INT_MAX;
			for (int centroid_iter = 0; centroid_iter < myConf->number_of_clusters; centroid_iter++)
			{
				cout << "Centroid : " << centroids[centroid_iter] << endl;
				for (int second_centroid = centroid_iter+1; second_centroid < myConf->number_of_clusters; second_centroid++)
				{
					cout << "Second centrod : " << centroids[second_centroid] << endl;
					cout << "Distace Matrix Distace : " << DistanceMatrixDistance(distanceMatrix, centroids[centroid_iter], centroids[second_centroid]) << endl;
					cout << "Min distance before calculations : " << minDistance << endl;
					if(DistanceMatrixDistance(distanceMatrix, centroids[centroid_iter], centroids[second_centroid]) < minDistance)
					{
						minDistance = DistanceMatrixDistance(distanceMatrix, centroids[centroid_iter], centroids[second_centroid]);
						cout << "New min distance : " << minDistance << endl;
					}
				}
			}
			Radius = minDistance / 2;*/
			cout << "Radius AFTER min distances : " << Radius << endl; 
			nodePtr = NULL;
			minimumNode = NULL; 	
			for (int o = 0; o < L; ++o) 	//for every hashtable
			{
				cout << "For hash table " << o << " : " << endl;
				//REMERMBER TO clear current hashtable off assignments
				//hashResult = 0;
				do
				{
					assigned_in_this_radius = false;
					for (int q = 0; q < myConf->number_of_clusters; q++) 	//for every centroid
					{
						hashResult = 0;		//was up : caution!
						cout << "For centroid : " << q << " : " << endl;
						for (int i=0; i < k; i++) 
						{      //for evry h
							d_x1_x2 = pow(DistanceMatrixDistance(distanceMatrix, h[o][i][0], h[o][i][1]), 2);        //distance between x1_x2 recalculate       //below distance between centroid and x1, x2
							h_x1_x2_x = (pow(DistanceMatrixDistance(distanceMatrix, centroids[q], h[o][i][0]),2) + pow(DistanceMatrixDistance(distanceMatrix, centroids[q], h[o][i][1]),2) - d_x1_x2)/(2*d_x1_x2);
							//h_x1_x2_x = (pow(point[(int)h[o][i][0]],2) + pow(point[(int)h[o][i][1]],2) - d_x1_x2)/(2*d_x1_x2);
							if ((h_x1_x2_x >= h[o][i][2])&& (h_x1_x2_x <= h[o][i][3]) ) 
							{
								hashResult += pow (2, i);
							}
						}
						cout << "The hash result : " << hashResult << endl;
						nodePtr = hashTableList[o].getHashTable()[hashResult].getBucket();
						if (nodePtr == NULL)
						{
							cout << "nodePtr after hashing is NULL";
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
							distance_bucketpoint_from_centroid = DistanceMatrixDistance(distanceMatrix, nodePtr->getItemNo(), centroids[q]);
							cout << "Distance bucket from centroid : " << distance_bucketpoint_from_centroid << endl;
							cout << "Radius : " << Radius << endl;
							if (distance_bucketpoint_from_centroid <= Radius)       //if inside radius
							{
								// if(point_to_centroid_assignment[nodePtr->getItemNo()] != -1)        //case that current point has been assigned on ANOTHER HASHTABLE but not yet on this one
								// {	
								cout << "It's better than Radius" << endl;
								if (distance_bucketpoint_from_centroid < nodePtr->getDistanceFromCentroid()) 		//getDistance initialized as INT_MAX
								{
									cout << "It goes in for this centroid" << endl;
									assigned_in_this_radius = true;
									nodePtr->setSecondBestCentroid(nodePtr->getCentroid());
									nodePtr->setSecondBestDistance(nodePtr->getDistanceFromCentroid());
									nodePtr->setFlagForAssignment(1);
									nodePtr->setCentroid(centroids[q]);
									nodePtr->setDistanceFromCentroid(distance_bucketpoint_from_centroid);
								}
								cout << "Updated!" << endl;
								// }
							}
							nodePtr = nodePtr->getNext();
						}

					}
					for (int hash_bucket = 0; hash_bucket < tableSize; hash_bucket++)	//from assign to legit assigned
					{
						cout << "++++++++++++++++++++++++++++++++++++++++" <<endl;
						cout << "This hash bucket : " << hash_bucket << endl;
						nodePtr = hashTableList[o].getHashTable()[hash_bucket].getBucket();
						while(nodePtr != NULL)
						{
							if (nodePtr->getFlagForAssignment() == 1) 
							{
								//cout << "will try to get past movetoback" <<endl;

								nodePtr->setFlagAsAssigned(1);
								hashTableList[o].MoveToBack(nodePtr->getItemNo(), hash_bucket);
								cout << "Moved to back successfully!" << endl;
								if(point_to_centroid_assignment[nodePtr->getItemNo()][0] == -1)
								{
									cout << "It was -1 (centroid - distance) and now updated to our local array : old :" << point_to_centroid_assignment[nodePtr->getItemNo()][0] << " : " << point_to_centroid_assignment[nodePtr->getItemNo()][1] << endl;
									point_to_centroid_assignment[nodePtr->getItemNo()][0] = nodePtr->getCentroid();
									point_to_centroid_assignment[nodePtr->getItemNo()][1] = nodePtr->getDistanceFromCentroid();
									cout << "It was -1 (centroid - distance) and now updated to our local array : new :" << point_to_centroid_assignment[nodePtr->getItemNo()][0] << " : " << point_to_centroid_assignment[nodePtr->getItemNo()][1] << endl;
								}
								else 
								{
									cout << "We have a previous assignment in our local array" <<endl;
									if(point_to_centroid_assignment[nodePtr->getItemNo()][1] > nodePtr->getDistanceFromCentroid())
									{
										cout << "It had values before (centroid - distance) and now updated to our local array : old " << point_to_centroid_assignment[nodePtr->getItemNo()][0] << " : " << point_to_centroid_assignment[nodePtr->getItemNo()][1] << endl;
										point_to_centroid_assignment[nodePtr->getItemNo()][0] = nodePtr->getCentroid();
										point_to_centroid_assignment[nodePtr->getItemNo()][1] = nodePtr->getDistanceFromCentroid();
										if (point_to_centroid_assignment[nodePtr->getItemNo()][3] > nodePtr->getSecondBestDistance())
										{
											point_to_centroid_assignment[nodePtr->getItemNo()][2] = nodePtr->getSecondBestCentroid();
											point_to_centroid_assignment[nodePtr->getItemNo()][3] = nodePtr->getSecondBestDistance();
										}
										cout << "It had values before (centroid - distance) and now updated to our local array : new " << point_to_centroid_assignment[nodePtr->getItemNo()][0] << " : " << point_to_centroid_assignment[nodePtr->getItemNo()][1] << endl;
									}
								}
								//cout << "assign out of assign ifs" <<endl;
							}
							//cout << "assign out of fat if" <<endl;
							nodePtr = nodePtr->getNext();
							//cout << "got next" <<endl;
						}
						cout << "Finished assignment on matrix for bucket" <<endl;
						cout << "++++++++++++++++++++++++++++++++++++++++" <<endl;
					}
					cout << "Multiplying Radius" <<endl;
					Radius = Radius * 2;
				}while(assigned_in_this_radius);
			}
			for (int point_iter = 0; point_iter < *dataLength; point_iter++)	//leftover assignment
			{
				cout << "Leftover : " << point_iter << endl;
				minimumDistance = numeric_limits<double>::max() ; 		//make it DOUBLE
				minimumCentroid = -1;
				if (point_to_centroid_assignment[point_iter][0] == -1 || point_to_centroid_assignment[point_iter][1] == -1)
				{
					for (int centroid_iter = 0; centroid_iter < myConf->number_of_clusters; centroid_iter++)
					{
						cout << "Centroid : " << centroid_iter << endl;
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
				cout << "Leftover updated" << endl;
			}
			cout << "Exiting..." << endl;
			for (int point_iter = 0; point_iter < *dataLength; point_iter++)		//moving changes to clusterAssign	
			{
				cout << "On point " <<point_iter <<endl;
				cout << "changing to best : " << point_to_centroid_assignment[point_iter][0] <<endl;
				clusterAssign[point_iter][2] = point_to_centroid_assignment[point_iter][0];		//give best centroid chosen
				cout << "changing to 2nd best : " << point_to_centroid_assignment[point_iter][2] <<endl;
				if (point_to_centroid_assignment[point_iter][2] == -1) 
				{
					clusterAssign[point_iter][1] = clusterAssign[point_iter][2];
				}
				else
				{
					clusterAssign[point_iter][1] = point_to_centroid_assignment[point_iter][2];		//give 2nd best centroid
				}
				
			}
			/*for (int hash_bucket = 0; hash_bucket < tableSize; hash_bucket++)		//search all the buckets the leftovers
			{
				nodePtr = hashTableList[i].getHashTable()[hashResult].getBucket();
				while(nodePtr != NULL)
				{
					if (nodePtr->getFlaggedForAssignment() != 1) 
					{
						minimumDistance = numeric_limits<double>::max() ; 		//make it DOUBLE
						minimumCentroid = -1;
						for (int centroid_iter = 0; centroid_iter < myConf->number_of_clusters; centroid_iter++)
						{
							distance_bucketpoint_from_centroid = DistanceMatrixDistance(distanceMatrix, nodePtr->getItemNo(), centroids[q]);
							if (distance_bucketpoint_from_centroid < minimumDistance)
							{
								minimumDistance = distance_bucketpoint_from_centroid;
								minimumCentroid = centroid_iter;
							}
						}
						nodePtr->setFlagForAssignment(1);		//assignment on hashtable list
						nodePtr->setCentroid(centroids[q]);		//assignment data on node
						nodePtr->setDistance(distance_bucketpoint_from_centroid);

						nodePtr->setFlaggedAsAssigned(1);
						hashTableList[i].MoveToBack(nodePtr->getItemNo(), hashResult);
						point_to_centroid_assignment[nodePtr->getItemNo()][0] = nodePtr->getCentroid();
						point_to_centroid_assignment[nodePtr->getItemNo()][1] = nodePtr->getDistance();
					}
					nodePtr->getNext();
				}
			}*/
			return;

			/*for (int q = 0; q < myConf->number_of_clusters; q++)        //for every centroid  
			{       
			// index = 0;
			// begin_lsh_query = clock();
			// stringstream linestream(genericStr);
			// getline(linestream, pointStr, '\t');
			// point = new double[*dataLength];
			// while (getline(linestream, pointStr, '\t')){     //Calculate dimension of points
			//  point[index] = strtod(pointStr.c_str(), NULL);
			//  index++;
			// }
				for (int o = 0; o < L; ++o){      //For every hashtable
					hashResult = 0;
					for (int i=0; i < k; i++) 
					{      //for evry h
						d_x1_x2 = pow(DistanceMatrixDistance(distanceMatrix, h[o][i][0], h[o][i][1]), 2);        //distance between x1_x2 recalculate       //below distance between centroid and x1, x2
						h_x1_x2_x = (pow(DistanceMatrixDistance(distanceMatrix, centroids[q], h[o][i][0]),2) + pow(DistanceMatrixDistance(distanceMatrix, centroids[q], h[o][i][1]),2) - d_x1_x2)/(2*d_x1_x2);
						//h_x1_x2_x = (pow(point[(int)h[o][i][0]],2) + pow(point[(int)h[o][i][1]],2) - d_x1_x2)/(2*d_x1_x2);
						if ((h_x1_x2_x >= h[o][i][2])&& (h_x1_x2_x <= h[o][i][3]) ) 
						{
							hashResult += pow (2, i);
						}
					}
				}

				Node<double>* nodePtr = NULL;
				Node<double>* minimumNode = NULL;
				// if (Radius > 0) 
				// {
				//     outputFile << "R NNs: "<<endl;
				// }
				for (int i = 0; i < L; ++i)
				{
					//     if (Radius > 0) 
					//     {
					  // outputFile <<"Table " << i << ":" <<endl;
					//     }
					nodePtr = hashTableList[i].getHashTable()[hashResult].getBucket();    //We take the bucket
					while (nodePtr != NULL)
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
						distance_bucketpoint_from_centroid = DistanceMatrixDistance(distanceMatrix, nodePtr->getItemNo(), centroids[q]);
						if (distance_bucketpoint_from_centroid <= Radius)       //if inside radius
						{
							if(point_to_centroid_assignment[nodePtr->getItemNo() != -1])        //case that current point has been assigned on ANOTHER HASHTABLE but not yet on this one
							{

							}
						}
						nodePtr = nodePtr->getNext();
					}
				}
				lshCNN = minimumNode->getItemNo();
				end_lsh_query = clock();

				//************************ ENDED LSH EUCLIDEAN  ************************

				// ************************ REAL NEIGHBOUR (AND TIME TAKEN) COMPUTATION WITH BRUTE FORCE ************************

				begin_brute = clock();
				for (int i = 0; i < *dataLength; i++) {
					cdis = point[i];
					if ((cdis < minCBruteDistance) && (cdis != 0))
					{
						minCBruteDistance = cdis;
						realCNN = i;
					}
				}
			   
				end_brute = clock();
				elapsed_secs_lshc = (double) (end_lsh_query - begin_lsh_query + (end_lsh_hashing - begin_lsh_hashing) + (end_h_creation - begin_h_creation) + (end_Matrix_insert - begin))  / CLOCKS_PER_SEC;
				elapsed_secs_brutec = (double) ((end_brute - begin_brute) + (end_Matrix_insert - begin)) / CLOCKS_PER_SEC;

				outputFile << "------->  LSH NN Euclidean :  " << itemName[lshCNN] << endl;
				outputFile << "------->  The real nearest neighbour for query " << queryCounter << " is within distance  : " << minLSHDistance << endl;
				outputFile << "------->  Time taken LSH Euclidean : " << elapsed_secs_lshc << endl << endl;

				outputFile << "------->  Real NN Euclidean :  " << itemName[realCNN] << endl;
				outputFile << "------->  The real nearest neighbour for query " << queryCounter << " is within distance  : " << point[realCNN] << endl;
				outputFile << "------->  Time taken brute force Euclidean : " << elapsed_secs_brutec << endl << endl;

				minCBruteDistance = 9999;     //Resetting the minimum distance
				minLSHDistance = 9999;
				realCNN = 0;
				lshCNN = 0;
				++queryCounter;
				if (queryFile >> genericStr) 
				{     //Read itemno
					outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  QUERY NUMBER " << queryCounter << " - " << genericStr << " $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl << endl;
				}
				delete[] point;
			}*/
		// 	outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  $$$$$$$$$$$$$$$$$   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
		// 	outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  END OF QUERY FILE   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
		// 	outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  $$$$$$$$$$$$$$$$$   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;

		// 	cout << " Press:" <<endl << "'a' - change all files (Rebuild LSH Tables)" <<endl << "'i' - change input(dataset) file (Rebuild LSH Tables)" <<endl << "'o' - change output file" <<endl << "'q' - change query file" << endl << "If you want to exit please type 'exit'" << endl;
		// 	cin >> choice;
		// 	if (choice.compare("a") == 0 || choice.compare("'a'") == 0) {
		// 		break;
		// 	}
		// 	else if (choice.compare("i") == 0 || choice.compare("'i'") == 0) {
		// 		break;
		// 	}
		// 	else if (choice.compare("o") == 0 || choice.compare("'o'") == 0) {
		// 		cout << "Please give output file name: ";
		// 		cin >> filename;
		// 		outputFile.close();
		// 		outputFile.open(filename.c_str());      
		// 		if (outputFile == NULL)
		// 		{
		// 			cout << "You've given a wrong input file. " << endl;
		// 			return;
		// 		}
		// 		else
		// 		{
		// 			cout << "File : " << filename << " opened successfully!" << endl << endl;
		// 		}
		// 	}
		// 	else if (choice.compare("q") == 0 || choice.compare("'q'") == 0) {
		// 		cout << "Please give output file name: ";
		// 		cin >> filename;
		// 		queryFile.close();
		// 		queryFile.open(filename.c_str());     
		// 		if (queryFile == NULL)
		// 		{
		// 			cout << "You've given a wrong input file. " << endl;
		// 			return;
		// 		}
		// 		else
		// 		{
		// 			cout << "File : " << filename << " opened successfully!" << endl << endl;
		// 		}
		// 	}
		// 	else if ((choice.compare("exit") != 0) && (choice.compare("'exit'") != 0)) {
		// 		cout << "Command not recognised. Exiting... You lost your chance..." <<endl;
		// 		exit(-1);
		// 	}
		// }while((choice.compare("exit") != 0) && (choice.compare("'exit'") != 0)); 

		// for (int i= 0; i <*dataLength; i++) {
		// 	delete[] distanceMatrix[i];
		// }
		// delete[] distanceMatrix;
		// delete[] itemName;

		// for (int o = 0; o < L; ++o)
		// {
		// 	for (int j = 0; j < k; j++) {
		// 		delete[] h[o][j];
		// 	}
		// 	delete[] h[o];
		// }
		// delete[] h;
		// delete[] h_x1_x2;
		// delete[] hashTableList;
		// exit(1);
}