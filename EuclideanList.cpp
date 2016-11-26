#include <sstream>
#include <time.h>
#include <cstdlib>
#include <time.h>
#include "ListData.h"
#include "Hash.h"
#include "MathFunctions.h"

using namespace std;


template <typename T>
void ListData<T>::initEuclideanList(ifstream& inputFile, ifstream& queryFile, int k, int L, ofstream& outputFile, int* dataLength) {
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
		int** r_k;
		int itemNumber = 0;
		int h;
		int w = 4;
		int inputFileSize = 0;
		int queryCounter = 1;
		clock_t begin, begin_brute, end_ebrute, begin_euclidList;
		clock_t begin_lshe_query, end_lshe_query;
		clock_t end_euclidList, begin_lsh_hashing, end_lsh_hashing;

		std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
		std::cout.precision(20);

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
   		inputFile.clear();     			 //Restart
   		inputFile.seekg(0, ios::beg);    //Data file back from start

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
		   			y_2 = sqrt(abs(r - pow(y_1, 2)));			// r = y_1^2 + y_2^2
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

   		if (k > *dataLength) {
   		    cout << "Warning: LSH does not support so many mini-hashing functions. Switching to highest number available" << endl;
   		    k = *dataLength;
   		}

        begin_euclidList = clock();
   		inputFile.clear();      		//Restart
   		inputFile.seekg(0, ios::beg);   //Data file back from start

   		inputFile >> metric_space;    	//Read "@metric space"      
   		inputFile >> metric_space;    	//Read "euclidean"
   		inputFile >> metric;			//Read etc, "@metric"       
   		inputFile >> metric;			//Read euclidean
		int index = 0;
		ListData<double*>* euclidList = new ListData<double*>(); 
		double* point;					//New point
		getline(inputFile, genericStr);
		itemNumber = 0;
   		while(getline(inputFile, genericStr)) {					//For every point
            itemNumber += 1;
   			index = 0;
	   		stringstream linestream(genericStr);
	   		getline(linestream, itemNos, '\t');        			//ITEMNO
	   		point = new double[*dataLength];
	   		while (getline(linestream, pointStr, '\t')){		//Calculate dimension of points
	   			point[index] = strtod(pointStr.c_str(), NULL);
	   			//cout << "pointstr:" <<point[index] << " index: " << index <<endl;
	   			index++;
	   		}
	   		if (!euclidList->EuclideanDuplicate(point, *dataLength)) {
	   			euclidList->Insert(point, itemNumber, itemNos);
	   		}
	   		inputFileSize++;
   		}
   		//euclidList->PrintData();
   		end_euclidList = clock();
   		elapsed_secs_euclidList = (double) (end_euclidList - begin_euclidList) / CLOCKS_PER_SEC;

   		begin_lsh_hashing = clock();
   		long long  tableSize = inputFileSize / 4;
   		//cout << "tableSize :" << tableSize << endl;
   		long long M = pow(2, 32) - 5;
   		//cout << "M :" << M << endl;
   		Hash<double*>* hashTableList = new Hash<double*>[L];
   		for (int o = 0; o < L; ++o)
   		{
   			hashTableList[o].initHash(tableSize, metric);
   		}
  
   		Node<double*>* nodePtr = euclidList->getNode();
   
   		while (nodePtr != NULL) {				//For every node in the euclidList
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
   		}
   		//hashTableList[0].printHash();
   		end_lsh_hashing = clock();
   		elapsed_secs_hashing = (double) (end_lsh_hashing - begin_lsh_hashing) / CLOCKS_PER_SEC;

   		TrickList<double*>* trickList = new TrickList<double*>();		//The first item of the TrickList is the info head
   		do {
	   		queryCounter = 1;
			queryFile.clear();      		//Restart
			queryFile.seekg(0, ios::beg);   //Data file back from start
	   		queryFile >> genericQuery;		//@Radius
	   		queryFile >> Radius;			//Radius_value
	   		outputFile << "Radius : " << Radius << endl;
	   		getline(queryFile, genericStr);
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
		exit(1);
}