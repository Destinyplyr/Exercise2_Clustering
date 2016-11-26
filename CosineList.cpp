#include <sstream>
#include <time.h>
#include <cstdlib>
#include "ListData.h"
#include "Hash.h"
#include "MathFunctions.h"

using namespace std;


template <typename T>
void ListData<T>::initCosineList(ifstream& inputFile, ifstream& queryFile, int k, int L, ofstream& outputFile, int* dataLength) {
		string genericStr;
		string itemName;
		string genericQuery;
		string pointStr;
		string metric;
		string GARBAGE;
        string filename;
        string choice;
		string metric_space; 
		Node<double*>* lshCNN;
		Node<double*>* realCNN;
        double Radius = 0;
        double cdis;
		double y_1, y_2, r;
		double minCBruteDistance= 99999;
		double minLSHDistance = 999999;
        double elapsed_secs_lshc, elapsed_secs_hashing;
        double elapsed_secs_brutec, elapsed_secs_query;
        double elapsed_secs_cosineList;
        double*** h;
		int hashResult = 0;
        int itemNo = 0;
		int inputFileSize = 0;
		int queryCounter = 1;
		clock_t begin, begin_brute, end_brute;
		clock_t begin_lsh_hashing, end_lsh_hashing;
		clock_t end_cosineList, begin_lsh_query, end_lsh_query;
		
		std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
		std::cout.precision(20);
        begin = clock();
        inputFile.clear();                  //Restart
        inputFile.seekg(0, ios::beg);       //Data file back from start
   		
        inputFile >> metric_space;          //Read "@metric space"     
   		inputFile >> metric_space;          //Read "euclidean"
   		inputFile >> metric;	            //Read etc, "@metric"       
   		inputFile >> metric;	            //Read cosine
   		inputFile >> genericStr;	        //Read itemno
   		
        getline(inputFile, genericStr);
   		stringstream linestream(genericStr);
   		getline(linestream, pointStr, '\t');
   		while (getline(linestream, pointStr, '\t'))    //Calculate dimension of points
        {			
   			(*dataLength)++;
   		}

   		inputFile.clear();                  //Restart
   		inputFile.seekg(0, ios::beg);       //Data file back from start

   		h = new double**[L];
   		for (int o = 0; o < L; ++o)
   		{
   			h[o] = new double*[k];
   			for (int j = 0; j < k; j++) {
   				h[o][j] = new double[*dataLength];
   			}
   		}

   		for (int o = 0; o < L; o++) {		    //for every hash table
	   		for (int j = 0; j < k; j++) {	    //for every h
		   		for (int i = 0; i < *dataLength; i++) {		//[-1,1]
		   		    //generate uniform  [M, N]: we want v numbers from -1 to 1
		   			r = ((double)rand() / (double)RAND_MAX);		//radius smaller than 1
		   			//cout <<  " R  : " << r << endl;
		   			y_1 = -1 + ((double)rand() / (double)RAND_MAX)*(2);
		   			//cout <<  " y_1  : " << y_1 << endl;
		   			y_2 = sqrt(abs(r - pow(y_1, 2)));			    // r = y_1^2 + y_2^2
		   			//cout <<  " y_2  : " << y_2 << endl;
		   			h[o][j][i] = y_1 * sqrt((-2 * log(r))/r);       //every coordinate follows a N(0,1) distribution
		   			//cout << "voji = " << v[o][j][i] <<endl;
		   		}
		   		//t[o][j] = 0 + ((double)rand() / (double)RAND_MAX)*(w);	//[0,w)
		   		//r_k[o][j]  = rand();
		   		//cout << "r_k : " << r_k[o][j] << endl;
	   		}
   		}

   		if (k > *dataLength) {
   		    cout << "Warning: LSH does not support so many mini-hashing functions. Switching to highest number available" << endl;
   		    k = *dataLength;
   		}

   		inputFile.clear();               //Restart
   		inputFile.seekg(0, ios::beg);    //Data file back from start
   		inputFile >> metric_space;       //Read "@metric space"      
   		inputFile >> metric_space;       //Read "euclidean"
   		inputFile >> metric;	         //Read etc, "@metric"       
   		inputFile >> metric;	         //Read euclidean
		int index = 0;
		ListData<double*>* cosineList = new ListData<double*>(); 
		double* point;
		inputFile >> itemName;	         //Read itemno
        itemNo = 0;
   		while(getline(inputFile, genericStr)) {		                //For every point
            ++itemNo;
   			index = 0;
	   		stringstream linestream(genericStr);
	   		getline(linestream, pointStr, '\t');
	   		point = new double[*dataLength];
	   		while (getline(linestream, pointStr, '\t')){			//Calculate dimension of points
	   			point[index] = strtod(pointStr.c_str(), NULL);
	   			//outputFile << "pointstr: " <<point[index] << " index: " << index <<endl;
                index++;
	   		}
            if (!cosineList->EuclideanDuplicate(point, *dataLength)) {
	   	        cosineList->Insert(point, itemNo, itemName);
            }
	   		inputFileSize++;
            inputFile >> itemName;   //Read itemno
   		}
   		end_cosineList = clock();
   		elapsed_secs_cosineList = (double) (end_cosineList - begin) / CLOCKS_PER_SEC;
   		//cosineList->PrintData();

   		begin_lsh_hashing = clock();
   		Hash<double*>* hashTableList = new Hash<double*>[L];
   		for (int o = 0; o < L; ++o)
   		{
   			hashTableList[o].initHash(k, metric);
   		}
   		Node<double*>* nodePtr = cosineList->getNode();
   
   		while (nodePtr != NULL) {				//For every node in the euclidList
    		for (int o = 0; o < L; ++o){		//For every hashtable
    			hashResult = 0;
			    for (int i=0; i < k; i++) {
			        if (dot_product(nodePtr->getKey(), h[o][i], *dataLength) >= 0) {
			        	hashResult += pow (2, i);
			        }
			    }
				hashTableList[o].Insert(hashResult, nodePtr->getKey(), hashResult, nodePtr->getItemNo(), nodePtr->getItemName());
   			}
   			nodePtr = nodePtr->getNext();
   		}
   		//hashTableList[0].printHash();
   		end_lsh_hashing = clock();
   		elapsed_secs_hashing = (double) (end_lsh_hashing - begin_lsh_hashing) / CLOCKS_PER_SEC;

        do 
        {
            queryCounter = 1;
            queryFile.clear();              //Restart
            queryFile.seekg(0, ios::beg);   //Data file back from start
       		queryFile >> genericQuery;	    //@Radius
       		queryFile >> Radius;	        //Radius_value
       		outputFile << "Radius : " << Radius << endl;
       		Node<double*>** listBucketTable = new Node<double*>*[L];
       		queryFile >> itemName;	        //Read itemno
            outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  QUERY NUMBER " << queryCounter << " - " << itemName <<" $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl << endl;
       		while(getline(queryFile, genericStr)) {					//For every point
       			index = 0;
    	   		begin_lsh_query = clock();
    	   		stringstream linestream(genericStr);
    	   		getline(linestream, itemName, '\t');
    	   		point = new double[*dataLength];
    	   		while (getline(linestream, pointStr, '\t'))   //Calculate dimension of points
                {			
    	   			point[index] = strtod(pointStr.c_str(), NULL);
    	   			//cout << "pointstr: " <<point[index] << " index: " << index <<endl;
    	   			index++;
    	   		}
    	   		for (int o = 0; o < L; ++o){		          //For every hashtable
                    hashResult = 0;
    			    for (int i=0; i < k; i++) {
    			        if (dot_product(point, h[o][i], *dataLength) >= 0) {
    			        	hashResult += pow (2, i);
    			        }
    			    }
                    nodePtr = hashTableList[o].getHashTable()[hashResult].getBucket();
                    listBucketTable[o] = nodePtr;
       			}
       			
       			Node<double*>* minimumNode = NULL;
                if (Radius > 0) 
                {
                    outputFile << "R NNs : " << endl;
                }
       			for (int i = 0; i < L; ++i)
       			{
                    if (Radius > 0) 
                    {
                        outputFile << "Table " << i << " : " << endl;
                    }
       				nodePtr = listBucketTable[i];		//We take the bucket
       				while (nodePtr != NULL)
       				{
       					cdis = cosineList->CosineDistance(point, nodePtr->getKey(), *dataLength);
                        if ((cdis <= Radius) && (Radius > 0))
                        {
                            outputFile << "--" << nodePtr->getItemName() << endl;
                        }
       					if ((cdis < minLSHDistance) && (cdis != 0))
       					{
       						minLSHDistance = cdis;
       						minimumNode = nodePtr;
       					}
       					nodePtr = nodePtr->getNext();
       				}
       			}
       			lshCNN = minimumNode;
       			end_lsh_query = clock();
       			elapsed_secs_query = (double) (end_lsh_query - begin_lsh_query) / CLOCKS_PER_SEC;


       			//************************ ENDED LSH EUCLIDEAN  ************************

       			// ************************ REAL NEIGHBOUR (AND TIME TAKEN) COMPUTATION WITH BRUTE FORCE ************************

       			Node<double*>* newNode = cosineList->getNode();
                begin_brute = clock();
       			while(newNode->getNext() != NULL)
       			{
       				cdis = cosineList->CosineDistance(newNode->getKey(), point, *dataLength);
       				//cout << "-------> Cosine Distance " << edis <<endl;
       				//cout << "-------> Radius  " << Radius <<endl;
       				if ( (cdis < minCBruteDistance) && (cdis != 0))
       				{
       					minCBruteDistance = cdis;
       					realCNN = newNode;
       				}
       				newNode = newNode->getNext();
       				if (newNode == NULL)
       				{
       					break;
       				}
       			}
       			end_brute = clock();
       			//cout << "Time query : " << elapsed_secs_query << endl;
       			//cout << "Time hashing : " << elapsed_secs_hashing << endl;
       			//cout << "Time cosineList : " << elapsed_secs_cosineList << endl;

       			elapsed_secs_lshc = (double) (elapsed_secs_query + elapsed_secs_hashing + elapsed_secs_cosineList)  / CLOCKS_PER_SEC;
       			elapsed_secs_brutec = (double) (end_brute - begin_brute + elapsed_secs_cosineList) / CLOCKS_PER_SEC;

       			outputFile << "------->  LSH NN Cosine :  " << lshCNN->getItemName() << endl;
       			outputFile << "------->  The lsh nearest neighbour for query " << queryCounter  << " is within distance  : " << minLSHDistance  << endl;
       			outputFile << "------->  Time taken LSH Cosine : " << elapsed_secs_lshc << endl << endl;

       			outputFile << "------->  Real NN Cosine :  " << realCNN->getItemName() << endl;
       			outputFile << "------->  The real nearest neighbour for query " << queryCounter << " is within distance  : " << minCBruteDistance << endl;
       			outputFile << "------->  Time taken brute force Cosine : " << elapsed_secs_brutec << endl << endl;

       			outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  END OF QUERY NUMBER " << queryCounter << "  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl << endl << endl << endl;

    			minCBruteDistance = 9999;			//Resetting the minimum distance
    			minLSHDistance = 9999;
    	    	realCNN = NULL;
    	    	lshCNN = NULL;
    	    	elapsed_secs_lshc = 0.0f;
    	    	elapsed_secs_brutec = 0.0f;
    	    	++queryCounter;
    	    	queryFile >> itemName;	//Read itemno
                if (itemName.empty())
                {
                    break;
                }
                outputFile << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  QUERY NUMBER " << queryCounter << " - " << itemName <<" $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl << endl;
       		}

            delete listBucketTable;
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
                delete[] h[o][j];
            }
            delete[] h[o];
        }
        delete h;
        nodePtr = cosineList->getNode();
        while (nodePtr != NULL)
        {
            delete nodePtr->getKey();
            nodePtr = nodePtr->getNext();
        }
        delete cosineList;
        delete[] hashTableList;
        exit(1);
}