#include <sstream>
#include <time.h>
#include <cstdlib>
#include "ListData.h"
#include "Hash.h"
#include <limits>
#include "MathFunctions.h"
#include "DistanceMatrixFunctions.h"

using namespace std;


template <typename T>
void ListData<T>::initDBHManagement(ifstream& inputFile, ifstream& queryFile, int k, int L, ofstream& outputFile, int* dataLength) {
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
        double** distanceMatrix;
        double* h_x1_x2;
        double* point;
		double cdis;
        double Radius = 0;
        double elapsed_secs_lshc;
        double elapsed_secs_brutec;
        double d_x1_x2, h_x1_x2_x;
        double minCBruteDistance= 99999;
        double minLSHDistance = 999999;
		int lshCNN = 0;
		int realCNN = 0;
        int ind = 0;
		int hashResult = 0;
		int index = 0;
		int queryCounter = 1;
		clock_t begin, begin_brute, end_brute, end_Matrix_insert, end_h_creation;
		clock_t begin_lsh_hashing, end_lsh_hashing, begin_h_creation;
		clock_t begin_lsh_query, end_lsh_query;

		std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
		std::cout.precision(20);

        inputFile.clear();              //Restart
        inputFile.seekg(0, ios::beg);   //Data file back from start
        inputFile.clear();              //Restart
        inputFile.seekg(0, ios::beg);   //Data file back from start
        begin = clock();

   		inputFile >> metric_space;      //Read "@metric space"    
   		inputFile >> metric_space;      //Read "matrix"
   		inputFile >> genericStr;        //Read items

   		getline(inputFile, genericStr);
   		stringstream linestream(genericStr);
   		while (getline(linestream, pointStr, ',')) {			//calculate dimension of points
   			(*dataLength)++;
   		}

   		//cout << "The number of points is: " << *dataLength <<  endl;
   		inputFile.clear();              //Restart
   		inputFile.seekg(0, ios::beg);   //Data file back from start

        itemName = new string[*dataLength];
        inputFile >> metric_space;      //Read "@metric space"     
        inputFile >> metric_space;      //Read "matrix"
        inputFile >> genericStr;        //Read items
        getline(inputFile, genericStr);
        stringstream linestream2(genericStr);
        while (getline(linestream2, pointStr, ',')) {       //Calculate dimension of points
            itemName[ind] = pointStr;
            ind++;
        }


        distanceMatrix = new double*[*dataLength];
        for (int i= 0; i <*dataLength; i++) {
            distanceMatrix[i] = new double[*dataLength];
        }

        //INSERT MATRIX
        inputFile >> GARBAGE;       //Read "@metric space"      
        inputFile >> GARBAGE;       //Read "matrix"
        inputFile >> GARBAGE;	    //Read @item

        getline(inputFile, GARBAGE);
        for (int i = 0; i < *dataLength; i++) {
            getline(inputFile, line);
            stringstream linestream(line);
            for (int j= 0 ; j< *dataLength; j++ ) {
                    getline(linestream, pointStr, '\t');
                    distanceMatrix[i][j] = strtod(pointStr.c_str(), NULL);
            }
        }
        end_Matrix_insert = clock();

        begin_h_creation = clock();

   		h = new double**[L];
   		h_x1_x2 = new double[*dataLength];
   		for (int o = 0; o < L; ++o)
   		{
   			h[o] = new double*[k];
   			for (int j = 0; j < k; j++) {
   				h[o][j] = new double[4];
   			}
   		}

   		for (int o = 0; o < L; o++)         //for every hash table
        {		
	   		for (int j = 0; j < k; j++) {	//for every h
                h[o][j][0] = floor(((double)rand() / (double)RAND_MAX)*((double)(*dataLength))); //x_1
                h[o][j][1] = floor(((double)rand() / (double)RAND_MAX)*((double)(*dataLength))); //x_2
                d_x1_x2 = pow(DistanceMatrixDistance(distanceMatrix, h[o][j][0], h[o][j][1]), 2);
                for (int u = 0; u < *dataLength; u++) {
                    h_x1_x2[u] = (pow(DistanceMatrixDistance(distanceMatrix, u, h[o][j][0]),2) + pow(DistanceMatrixDistance(distanceMatrix, u, h[o][j][1]),2) - d_x1_x2)/(2*d_x1_x2);
                }
                quickSort(h_x1_x2, 0, (*dataLength)-1);
                if ((*dataLength) %2 == 0) {
                    h[o][j][2] = h_x1_x2[(*dataLength) / 2];
                }
                else {
                    h[o][j][2] = 0.5* (h_x1_x2[(*dataLength) / 2] + h_x1_x2[((*dataLength) / 2)-1]) ;
                }
                h[o][j][3] = numeric_limits<double>::max() ; //t_2
	   		}
   		}


   		if (k > *dataLength) {
   		    cout << "Warning: LSH does not support so many mini-hashing functions. Switching to highest number available" << endl;
   		    k = *dataLength;
   		}

   		//cout << "The size of each hamming code is: " << *dataLength <<endl;
   		inputFile.clear();              //Restart
   		inputFile.seekg(0, ios::beg);   //Data file back from start

        end_h_creation = clock();
   		begin_lsh_hashing = clock();
   		Hash<double>* hashTableList = new Hash<double>[L];
   		for (int o = 0; o < L; ++o)
   		{
   			hashTableList[o].initHash(k, metric_space);
   		}
   		for (int u = 0; u <*dataLength; u++) {	//For every point
    		for (int o = 0; o < L; ++o){		//For every hashtable
    			hashResult = 0;
			    for (int i=0; i < k; i++) {
			        d_x1_x2 = pow(DistanceMatrixDistance(distanceMatrix, h[o][i][0], h[o][i][1]), 2);
			        h_x1_x2_x = (pow(DistanceMatrixDistance(distanceMatrix, u, h[o][i][0]),2) + pow(DistanceMatrixDistance(distanceMatrix, u, h[o][i][1]),2) - d_x1_x2)/(2*d_x1_x2);
			        if ((h_x1_x2_x >= h[o][i][2])&& (h_x1_x2_x <= h[o][i][3]) ) {
			        	hashResult += pow (2, i);
			        }
			    }
				hashTableList[o].Insert(hashResult, u, hashResult, u, itemName[u]);
   			}
   		}
   		end_lsh_hashing = clock();

        do {
            queryCounter = 1;
       		begin_lsh_query = clock();
            queryFile.clear();              //Restart
            queryFile.seekg(0, ios::beg);   //Data file back from start
       		queryFile >> genericQuery;	    //@Radius
       		queryFile >> Radius;	        //Radius_value
       		queryFile >> genericStr;	    //Read itemno
            outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  QUERY NUMBER " << queryCounter << " - " << genericStr << " $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl << endl;
       		while(getline(queryFile, genericStr)) {					//for every point
       			index = 0;
    	   		begin_lsh_query = clock();
    	   		stringstream linestream(genericStr);
    	   		getline(linestream, pointStr, '\t');
    	   		point = new double[*dataLength];
    	   		while (getline(linestream, pointStr, '\t')){			//Calculate dimension of points
    	   			point[index] = strtod(pointStr.c_str(), NULL);
    	   			index++;
    	   		}
    	   		for (int o = 0; o < L; ++o){      //For every hashtable
                    hashResult = 0;
    			    for (int i=0; i < k; i++) {
    			        d_x1_x2 = pow(DistanceMatrixDistance(distanceMatrix, h[o][i][0], h[o][i][1]), 2);
    			        h_x1_x2_x = (pow(point[(int)h[o][i][0]],2) + pow(point[(int)h[o][i][0]],2) - d_x1_x2)/(2*d_x1_x2);
    			        if ((h_x1_x2_x >= h[o][i][2])&& (h_x1_x2_x <= h[o][i][3]) ) {
    			        	hashResult += pow (2, i);
    			        }
    			    }
       			}

       			Node<double>* nodePtr = NULL;
       			Node<double>* minimumNode = NULL;
                if (Radius > 0) 
                {
                    outputFile << "R NNs: "<<endl;
                }
       			for (int i = 0; i < L; ++i)
       			{
                    if (Radius > 0) 
                    {
       			      outputFile <<"Table " << i << ":" <<endl;
                    }
       				nodePtr = hashTableList[i].getHashTable()[hashResult].getBucket();		//We take the bucket
       				while (nodePtr != NULL)
       				{
       					cdis =  point[nodePtr->getItemNo()];       
                        if ((cdis <= Radius) && (Radius > 0 )) {
                            outputFile << "--"<<nodePtr->getItemName() <<endl;
       					}
       					if ((cdis < minLSHDistance) && (cdis != 0))
       					{
       						minLSHDistance = cdis;
       						minimumNode = nodePtr;
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

    			minCBruteDistance = 9999;			//Resetting the minimum distance
    			minLSHDistance = 9999;
    	    	realCNN = 0;
    	    	lshCNN = 0;
    	    	++queryCounter;
    	    	if (queryFile >> genericStr) {	   //Read itemno
                    outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  QUERY NUMBER " << queryCounter << " - " << genericStr << " $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl << endl;
                }
                delete[] point;
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

        for (int i= 0; i <*dataLength; i++) {
            delete[] distanceMatrix[i];
        }
        delete[] distanceMatrix;
        delete[] itemName;

        for (int o = 0; o < L; ++o)
        {
            for (int j = 0; j < k; j++) {
                delete[] h[o][j];
            }
            delete[] h[o];
        }
        delete[] h;
        delete[] h_x1_x2;
        delete[] hashTableList;
        exit(1);
}