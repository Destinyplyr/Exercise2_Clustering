#include "mainSample.h"

void CLI(ifstream& inputFile, ofstream& outputFile, Conf* myConf, Metrics* myMetric, ClusterTable* clusterTable, double** distance_matrix, int* centroids, int** clusterAssign, int L, int k, bool complete_printing) 
{
	string GARBAGE;
	int point_number, size_of_cluster;
	int* items_in_cluster_itemNo;
	string*	items_in_cluster_itemName;
	bool first_time_lsh = 1; 	
	int hashCreationDone = 0;

	if (strcmp(myMetric->metric_space.c_str(), "hamming") == 0)
	{
		ListData<bitset<64> >* hammingList = new ListData<bitset<64> >();
		hammingList->ListInsertionHamming(inputFile, myMetric);

		//cout << "********************************************************" << endl;
		clusterTable->Init_Tables(&distance_matrix, myMetric, myConf, &centroids, &clusterTable, &clusterAssign);
		SetClaransFraction(myConf, myMetric);
		//cout << "********************************************************" << endl;

		hammingList->DistanceMatrixComputationHamming(myMetric, distance_matrix);
		for(int init_iter = 0; init_iter < 2; init_iter++)
		{
			if (init_iter == 0) //case KMedoids++
			{
				KMedoidsPP(myConf, myMetric, distance_matrix, centroids);
			}
			else if (init_iter == 1)//case Concentrate
			{
				Concentrate(myConf, myMetric, distance_matrix, centroids);
			}
			/*cout << "==================" << endl << "PRINTING CLUSTERS IN mainSample BEFORE CLARANS : " <<endl;
			for (int w = 0; w <myConf->number_of_clusters; w++) {
				cout << centroids[w] << " ";
			}*/

			//exit(1);
			//cout << clusterAssign[0][0] <<endl;
			for (int assign_iter = 0; assign_iter < 2; assign_iter++)
			{
				if (assign_iter == 0)		//case PAM
				{
					delete clusterTable;
					clusterTable = new ClusterTable(myConf->number_of_clusters);
					cout << "starting pam - alaloyds" <<endl;
					for (int assign_update_times =0; assign_update_times < 5; assign_update_times++)
					{
						PAM(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign);		//assignment
						if (!ALaLoyds(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign)) {		//update
						 	//cout << "done!" << endl;
						}	
					}
					/*for (int cluster_iter = 0; cluster_iter < myConf->number_of_clusters; cluster_iter++)
					{
						clusterTable->PrintClusterNo(cluster_iter);
					}*/

					//PRINTING SEGMENT
					outputFile << "Algorithm: I" << init_iter+1 << "x" << assign_iter+1 << "x" << 1 <<endl;
					for (int cluster_iter = 0; cluster_iter < myConf->number_of_clusters; cluster_iter++)
					{
						clusterTable->PrintClusterDataForList(cluster_iter, &size_of_cluster);		//used to get size
						outputFile << "CLUSTER-" << cluster_iter << " {"<<size_of_cluster << ", " << clusterTable->ClusterDistance( myMetric, distance_matrix, cluster_iter, clusterAssign) <<"}" <<endl;
					}
					clusterTable->PrintingSilhouette(outputFile, myConf, distance_matrix, centroids, clusterAssign);		//printing Silhouette
					//cin >> GARBAGE;
					if (complete_printing == 1)
					{
						for (int cluster_iter = 0; cluster_iter < myConf->number_of_clusters; cluster_iter++)
						{
							cout << "PrintClusterDataForList" << endl;
							//ClusterTable::PrintClusterDataForList(int cluster_no int* size_of_cluster)
							items_in_cluster_itemNo = clusterTable->PrintClusterDataForList(cluster_iter, &size_of_cluster);
							if (items_in_cluster_itemNo == NULL)
							{
								continue;
							}
							cout << "ItemNamesFromItemNos" << endl;
							items_in_cluster_itemName = hammingList->ItemNamesFromItemNos(items_in_cluster_itemNo, size_of_cluster);
							cout << "PrintClusterUsingNames" << endl;
							clusterTable->PrintClusterUsingNames(outputFile, items_in_cluster_itemName, size_of_cluster, cluster_iter);
							delete[] items_in_cluster_itemNo;		//initialized inside PrintClusterDataForList
							delete[] items_in_cluster_itemName;		//initilaized inside ItemNamesFromItemNos
						}
					}
					cout << "finished pam - alaloyds" <<endl;

				}
				else if (assign_iter == 1)	//case reverse LSH
				{
					cout << "starting lsh - alaloyds" <<endl;
					for (int assign_update_times =0; assign_update_times < 5; assign_update_times++)
					{
						Hash<bitset<64> >* hashTableList = new Hash<bitset<64> >[L]();      //Na min orizetai se kathe iteration tou update, giati xanaorizetai
						if (first_time_lsh == true) 
						{
							first_time_lsh = false;
							hashCreationDone = 0;
							point_number = myMetric->point_number;							//assignment
							hammingList->initHammingLSHManagement(myConf, inputFile, distance_matrix, k , L, &(point_number), &hashCreationDone, hashTableList, centroids, clusterAssign);	
						}
						delete clusterTable;
						clusterTable = new ClusterTable(myConf->number_of_clusters);
						clusterTable->CreateClusterTableFromClusterAssign(myConf, myMetric,clusterAssign, centroids);
						if (!ALaLoyds(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign)) {		//update
						 	//cout << "done!" << endl;
						}
						//delete clusterTable; //DELETE CLUSTER TABLE (case lsh/dbh)
						//clusterTable->PrintingSilhouette(outputFile, myConf, distance_matrix, centroids, clusterAssign);
					}

					//PRINTING SEGMENT
					outputFile << "Algorithm: I" << init_iter+1 << "x" << assign_iter+1 << "x" << 1 <<endl;
					for (int cluster_iter = 0; cluster_iter < myConf->number_of_clusters; cluster_iter++)
					{
						clusterTable->PrintClusterDataForList(cluster_iter, &size_of_cluster);		//used to get size
						outputFile << "CLUSTER-" << cluster_iter << " {"<<size_of_cluster << ", " << clusterTable->ClusterDistance( myMetric, distance_matrix, cluster_iter, clusterAssign) <<"}" <<endl;
					}
					clusterTable->PrintingSilhouette(outputFile, myConf, distance_matrix, centroids, clusterAssign);		//printing Silhouette
					//cin >> GARBAGE;
					if (complete_printing == 1)
					{
						for (int cluster_iter = 0; cluster_iter < myConf->number_of_clusters; cluster_iter++)
						{
							cout << "PrintClusterDataForList" << endl;
							//ClusterTable::PrintClusterDataForList(int cluster_no int* size_of_cluster)
							items_in_cluster_itemNo = clusterTable->PrintClusterDataForList(cluster_iter, &size_of_cluster);
							if (items_in_cluster_itemNo == NULL)
							{
								continue;
							}
							cout << "ItemNamesFromItemNos" << endl;
							items_in_cluster_itemName = hammingList->ItemNamesFromItemNos(items_in_cluster_itemNo, size_of_cluster);
							cout << "PrintClusterUsingNames" << endl;
							clusterTable->PrintClusterUsingNames(outputFile, items_in_cluster_itemName, size_of_cluster, cluster_iter);
							delete[] items_in_cluster_itemNo;		//initialized inside PrintClusterDataForList
							delete[] items_in_cluster_itemName;		//initilaized inside ItemNamesFromItemNos
						}
					}
					cout << "finished lsh - alaloyds" <<endl;
				}
				
				/*cout << "==================" << endl << "PRINTING CLUSTERS IN mainSample Before PrintingSilhouette : " <<endl;
				for (int w = 0; w <myConf->number_of_clusters; w++) {
					cout << centroids[w] << " ";
				}
				cout <<endl;*/
				
			}
			delete clusterAssign;
			clusterAssign= new int*[myMetric->point_number];
			for (int i = 0; i < myMetric->point_number; ++i)
			{
			    clusterAssign[i] = new int[3];
			    clusterAssign[i][0] = -1;
			    clusterAssign[i][1] = -1;
			    clusterAssign[i][2] = -1;
			}
			//cin >> GARBAGE;
			delete clusterTable;
			clusterTable = new ClusterTable(myConf->number_of_clusters);
			cout << "starting CLARANS" << endl;
			CLARANS(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign);		//full CLARANS algorithm uses only PAM
			outputFile << "Algorithm: I" << init_iter+1 << "x" << 1 << "x" << 2 <<endl;
			for (int cluster_iter = 0; cluster_iter < myConf->number_of_clusters; cluster_iter++)
			{
				clusterTable->PrintClusterDataForList(cluster_iter, &size_of_cluster);		//used to get size
				outputFile << "CLUSTER-" << cluster_iter << " {"<<size_of_cluster << ", " << clusterTable->ClusterDistance( myMetric, distance_matrix, cluster_iter, clusterAssign) <<"}" <<endl;
			}
			clusterTable->PrintingSilhouette(outputFile, myConf, distance_matrix, centroids, clusterAssign);		//printing Silhouette
			//cin >> GARBAGE;
			if (complete_printing == 1)
			{
				for (int cluster_iter = 0; cluster_iter < myConf->number_of_clusters; cluster_iter++)
				{
					cout << "PrintClusterDataForList" << endl;
					//ClusterTable::PrintClusterDataForList(int cluster_no int* size_of_cluster)
					items_in_cluster_itemNo = clusterTable->PrintClusterDataForList(cluster_iter, &size_of_cluster);
					if (items_in_cluster_itemNo == NULL)
					{
						continue;
					}
					cout << "ItemNamesFromItemNos" << endl;
					items_in_cluster_itemName = hammingList->ItemNamesFromItemNos(items_in_cluster_itemNo, size_of_cluster);
					cout << "PrintClusterUsingNames" << endl;
					clusterTable->PrintClusterUsingNames(outputFile, items_in_cluster_itemName, size_of_cluster, cluster_iter);
					delete[] items_in_cluster_itemNo;		//initialized inside PrintClusterDataForList
					delete[] items_in_cluster_itemName;		//initilaized inside ItemNamesFromItemNos
				}
			}
			//clusterTable->PrintingSilhouette(outputFile, myConf, distance_matrix, centroids, clusterAssign);
			cout << "finished CLARANS" <<endl;
		}
		delete clusterAssign;
		clusterAssign= new int*[myMetric->point_number];
		for (int i = 0; i < myMetric->point_number; ++i)
		{
		    clusterAssign[i] = new int[3];
		    clusterAssign[i][0] = -1;
		    clusterAssign[i][1] = -1;
		    clusterAssign[i][2] = -1;
		}
		delete clusterTable;
		clusterTable = new ClusterTable(myConf->number_of_clusters);
		cout << "starting CLARA" <<endl;
		CLARA( myConf,  myMetric, distance_matrix, centroids, clusterTable, clusterAssign);

		//PRINTING SEGMENT
		//outputFile << "Algorithm: I" << init_iter+1 << "x" << assign_iter+1 << "x" << 1 <<endl;
		outputFile << "CLARA" <<endl;
		outputFile << "test" <<endl;
		for (int cluster_iter = 0; cluster_iter < myConf->number_of_clusters; cluster_iter++)
		{
			clusterTable->PrintClusterDataForList(cluster_iter, &size_of_cluster);		//used to get size
			outputFile << "CLUSTER-" << cluster_iter << " {" << size_of_cluster << ", " << clusterTable->ClusterDistance( myMetric, distance_matrix, cluster_iter, clusterAssign) <<"}" <<endl;
		}
		clusterTable->PrintingSilhouette(outputFile, myConf, distance_matrix, centroids, clusterAssign);		//printing Silhouette
		//cin >> GARBAGE;
		if (complete_printing == 1)
		{
			for (int cluster_iter = 0; cluster_iter < myConf->number_of_clusters; cluster_iter++)
			{
				cout << "PrintClusterDataForList" << endl;
				//ClusterTable::PrintClusterDataForList(int cluster_no int* size_of_cluster)
				items_in_cluster_itemNo = clusterTable->PrintClusterDataForList(cluster_iter, &size_of_cluster);
				if (items_in_cluster_itemNo == NULL)
				{
					continue;
				}
				cout << "ItemNamesFromItemNos" << endl;
				items_in_cluster_itemName = hammingList->ItemNamesFromItemNos(items_in_cluster_itemNo, size_of_cluster);
				cout << "PrintClusterUsingNames" << endl;
				clusterTable->PrintClusterUsingNames(outputFile, items_in_cluster_itemName, size_of_cluster, cluster_iter);
				delete[] items_in_cluster_itemNo;		//initialized inside PrintClusterDataForList
				delete[] items_in_cluster_itemName;		//initilaized inside ItemNamesFromItemNos
			}
		}
		cout << "finished CLARA" <<endl;
		outputFile.close();

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
			clusterTable->PrintingSilhouette(outputFile, myConf, distance_matrix, centroids, clusterAssign);
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
			clusterTable->PrintingSilhouette(outputFile, myConf, distance_matrix, centroids, clusterAssign);
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
		clusterTable->PrintingSilhouette(outputFile, myConf, distance_matrix, centroids, clusterAssign);
		delete clusterTable; //DELETE CLUSTER TABLE (case lsh/dbh)
		

		
		//delete DBHList;
		//continue;

	}

}