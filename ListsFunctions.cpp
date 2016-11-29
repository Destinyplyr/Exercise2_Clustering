#include "Headers.h"
#include "ListData.h"

template <typename T>
ListData<T>::ListData()
{
	header = NULL;
	//cout << "------->  ListData initialized successfully!" << endl << endl;
}


template <typename T>
ListData<T>::~ListData()
{
	if (header != NULL)
	{
		delete header;
		header = NULL;
		//cout << "------->  Finished processing the ListData." << endl;
	}
	else
	{
		//cout << "------->  Finished processing the ListData." << endl;
	}
}


template <typename T, size_t N>
inline
size_t sizeOfArray( const T(&)[ N ] )
{
	return N;
}


template <typename T>
Node<T>* ListData<T>::getNode()
{
	return header;
}


template <typename T>
void ListData<T>::PrintData()
{
	Node<T>* node;
	node = header;
	int counter = 1;
	while (node->getNext() != NULL)
	{
		cout << "Item " << counter << " in list : " << node->getKey()[0] << endl;
		node = node->getNext();
		++counter;
	}

	cout << "Item " << counter << " in list : " << node->getKey()[0] << endl;
}


template <typename T>
void ListData<T>::Insert(T newItem, int itemno, string itemName)
{
 	Node<T>* node = new Node<T>(newItem, 0, itemno, itemName);
	if (header == NULL)
    {
		header = node;
    }
	else
	{
		Node<T>* tail = header;
		while (tail->getNext() != NULL)
		{
			tail = tail->getNext();
		}
		tail->setNext(node);
	}

	//cout << "Item inserted" << endl;
}

template <typename T>
int ListData<T>::Distance(T item1, T item2)
{
	int distance = 0;
	int i = 0, j = 0;

	while ((i < item1.size()) && (j < item2.size()))
	{
		if (item1[i] == item2[j])
		{
			//cout << "Same bit" << endl;
			++i;
			++j;
		}
		else
		{
			//cout << "Different bit" << endl;
			++distance;
			++i;
			++j;
		}
	}

	return distance;
}


template <typename T>
double ListData<T>::DistanceB2BHamming(T item1, T item2)
{
	return (item1 ^= item2).count();
}


template <typename T>
double ListData<T>::CosineDistance(double item1[], double item2[], int size)      //Cosine
{
	double norm1, norm2;
	double cosine;

	norm1 = euclid_norm(item1, size);
	norm2 = euclid_norm(item2, size);
    cosine = dot_product(item1, item2, size) / (norm1 * norm2);

    return (1 - cosine);
}


template <typename T>
Node<T>* ListData<T>::ReturnHead() {
    return header;
}


template <typename T>
bool ListData<T>::HammingDuplicate(T item) {
	Node<T>* currentNode = header;
	while(currentNode != NULL) {
		if (item.compare(currentNode->getKey()) == 0) {
			return true;
		}
		currentNode = currentNode->getNext();
	}
	return false;
}

template <typename T>
bool ListData<T>::HammingB2BDuplicate(T item) {
	Node<T>* currentNode = header;
	while(currentNode != NULL) {
		if ((item ^= currentNode->getKey()) == 0) {
			return true;
		}
		currentNode = currentNode->getNext();
	}
	return false;
}


template <typename T>
bool ListData<T>::EuclideanDuplicate(T item, int size) {
	Node<T>* currentNode = header;
	while(currentNode != NULL) {
		if (SameArray(currentNode->getKey(), item, size)) {
			return true;
		}
		currentNode = currentNode->getNext();
	}
	return false;
}

template <typename T>
bool ListData<T>::ExistsOnce(int itemno, Node<T>* header_out)
{
	Node<T>* currentNode = header_out;
	//cout << endl;
	while (currentNode != NULL)
	{
		// cout << "once - current node key: " << currentNode->getKey() << endl;
		// cout << "once -current node itemno: " << currentNode->getItemNo() << endl;
		if (currentNode->getItemNo() == itemno) 
		{
			if (Exists(itemno, currentNode->getNext()) == false) 
			{
				return true;
			}
			else 
			{
				return false;
			}
		}
		currentNode = currentNode->getNext();
	}
	return false;
}

template <typename T>
bool ListData<T>::Exists(int itemno, Node<T>* header_out)
{
	Node<T>* currentNode = header_out;
	while (currentNode != NULL)
	{
		// cout << "simple - current node key: " << currentNode->getKey() << endl;
		// cout << "simple -current node itemno: " << currentNode->getItemNo() << endl;
		// cout << "simple: " << currentNode->getItemNo() << " " << itemno <<endl;
		if (currentNode->getItemNo() == itemno) 
		{
			return true;
		}
		currentNode = currentNode->getNext();
	}
	return false;
}

template <typename T>
string* ListData<T>::ItemNamesFromItemNos(int* items_in_cluster_itemNo, int size_of_cluster)
{
	Node<T>* currentNode;
	string* items_in_cluster_itemName = new string[size_of_cluster+1];
	for (int items_in_cluster_iter = 0; items_in_cluster_iter <= size_of_cluster; items_in_cluster_iter++)
	{
		currentNode = this->ReturnHead();
		while (currentNode != NULL) 
		{
			//cout << "currentNode->getItemNo()" << currentNode->getItemNo() << " items_in_cluster_itemNo[items_in_cluster_iter] " <<items_in_cluster_itemNo[items_in_cluster_iter] <<endl; 
			if (currentNode->getItemNo() == items_in_cluster_itemNo[items_in_cluster_iter])
			{
				//cout << "problem in if" <<endl;
				//cout << "currentNode->getItemName() " << currentNode->getItemName() <<endl;
				items_in_cluster_itemName[items_in_cluster_iter] = currentNode->getItemName();
			}
			currentNode = currentNode->getNext();
			//cout << "stuck on you" <<endl;
		}
		//cout << "and managed to get out" <<endl;
	}
	return items_in_cluster_itemName;
}

template <typename T>
void ListData<T>::Printer(ifstream& inputFile, ofstream& outputFile, Conf* myConf, Metrics* myMetric, ClusterTable* clusterTable, double** distance_matrix, int* centroids, int** clusterAssign, int L, int k, bool complete_printing)
{
	int total;
	string GARBAGE;
	int point_number, size_of_cluster;
	int* items_in_cluster_itemNo;
	string*	items_in_cluster_itemName;
	bool first_time_lsh = 1; 	
	int hashCreationDone = 0;
	clock_t KMPP_start, KMPP_finish;
	clock_t Concentrate_start, Concentrate_finish;
	double Initialization_elapsed;
	clock_t Assign_Update_start, Assign_Update_finish;
	double Assign_Update_elapsed;
	clock_t CLARA_start, CLARA_finish;
	double CLARA_elapsed;

	for(int init_iter = 0; init_iter < 2; init_iter++)
	{
		if (init_iter == 0) //case KMedoids++
		{
			KMPP_start = clock();
			KMedoidsPP(myConf, myMetric, distance_matrix, centroids);
			KMPP_finish = clock();
			Initialization_elapsed = (double)(KMPP_finish - KMPP_start)/CLOCKS_PER_SEC;
		}
		else if (init_iter == 1)//case Concentrate
		{
			Concentrate_start = clock();
			Concentrate(myConf, myMetric, distance_matrix, centroids);
			Concentrate_finish = clock();
			Initialization_elapsed = (double)(Concentrate_finish - Concentrate_start)/CLOCKS_PER_SEC;
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
				Assign_Update_start = clock();
				for (int assign_update_times =0; assign_update_times < 5; assign_update_times++)
				{
					PAM(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign);		//assignment
					if (!ALaLoyds(myConf, myMetric, distance_matrix, centroids, clusterTable, clusterAssign)) {		//update
					 	//cout << "done!" << endl;
					}	
				}
				Assign_Update_finish = clock();
				Assign_Update_elapsed = (double)(Assign_Update_finish - Assign_Update_start)/CLOCKS_PER_SEC;
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
				outputFile << "Clustering Time: " << Assign_Update_elapsed + Initialization_elapsed <<endl;
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
						items_in_cluster_itemName = ItemNamesFromItemNos(items_in_cluster_itemNo, size_of_cluster);
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
				Hash<T>* hashTableList = new Hash<T>[L]();      //Na min orizetai se kathe iteration tou update, giati xanaorizetai
				Assign_Update_start = clock();
				for (int assign_update_times =0; assign_update_times < 5; assign_update_times++)
				{
					if (first_time_lsh == true) 
					{
						first_time_lsh = false;
						hashCreationDone = 0;
						point_number = myMetric->point_number;							//assignment
						if (strcmp(myMetric->metric_space.c_str(), "hamming") == 0)
						{
							initHammingLSHManagement(myConf, inputFile, distance_matrix, k , L, &(point_number), &hashCreationDone, hashTableList, centroids, clusterAssign);
						}
						if (strcmp(myMetric->metric_space.c_str(), "vector") == 0)
						{
							if (strcmp(myMetric->metric.c_str(), "euclidean") == 0)
							{
								initEuclideanList(myConf, inputFile, distance_matrix, k , L, &(point_number), &hashCreationDone, hashTableList, centroids, clusterAssign);
							}
							
							if (strcmp(myMetric->metric.c_str(), "cosine") == 0)
							{
								initCosineList(myConf, inputFile, distance_matrix, k , L, &(point_number), &hashCreationDone, hashTableList, centroids, clusterAssign);
							}
						}
						if (strcmp(myMetric->metric_space.c_str(), "matrix") == 0)
						{
							initDBHManagement(myConf, inputFile, distance_matrix, k , L, &(point_number), &hashCreationDone, hashTableList, centroids, clusterAssign);
						}
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
				Assign_Update_finish = clock();
				Assign_Update_elapsed = (double)(Assign_Update_finish - Assign_Update_start)/CLOCKS_PER_SEC;

				//PRINTING SEGMENT
				outputFile << "Algorithm: I" << init_iter+1 << "x" << assign_iter+1 << "x" << 1 <<endl;
				for (int cluster_iter = 0; cluster_iter < myConf->number_of_clusters; cluster_iter++)
				{
					clusterTable->PrintClusterDataForList(cluster_iter, &size_of_cluster);		//used to get size
					outputFile << "CLUSTER-" << cluster_iter << " {"<<size_of_cluster << ", " << clusterTable->ClusterDistance( myMetric, distance_matrix, cluster_iter, clusterAssign) <<"}" <<endl;
				}
				outputFile << "Clustering Time: " << Assign_Update_elapsed + Initialization_elapsed <<endl;
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
						items_in_cluster_itemName = ItemNamesFromItemNos(items_in_cluster_itemNo, size_of_cluster);
						cout << "PrintClusterUsingNames" << endl;
						clusterTable->PrintClusterUsingNames(outputFile, items_in_cluster_itemName, size_of_cluster, cluster_iter);
						delete[] items_in_cluster_itemNo;		//initialized inside PrintClusterDataForList
						delete[] items_in_cluster_itemName;		//initilaized inside ItemNamesFromItemNos
					}
				}
/*				for (int delete_iter = 0; delete_iter < L; delete_iter++)
				{
					delete hashTableList[delete_iter];
				}*/
				delete[] hashTableList;
				cout << "finished lsh - alaloyds" <<endl;
			}
			
			/*cout << "==================" << endl << "PRINTING CLUSTERS IN mainSample Before PrintingSilhouette : " <<endl;
			for (int w = 0; w <myConf->number_of_clusters; w++) {
				cout << centroids[w] << " ";
			}
			cout <<endl;*/
			
		}
		Assign_Update_start = clock();
		for (int i = 0; i < myMetric->point_number; ++i)
		{
			delete clusterAssign[i];
		}
		delete[] clusterAssign;
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
		Assign_Update_finish = clock();
		Assign_Update_elapsed = (double)(Assign_Update_finish - Assign_Update_start)/CLOCKS_PER_SEC;

		outputFile << "Algorithm: I" << init_iter+1 << "x" << 1 << "x" << 2 <<endl;
		for (int cluster_iter = 0; cluster_iter < myConf->number_of_clusters; cluster_iter++)
		{
			clusterTable->PrintClusterDataForList(cluster_iter, &size_of_cluster);		//used to get size
			outputFile << "CLUSTER-" << cluster_iter << " {"<<size_of_cluster << ", " << clusterTable->ClusterDistance( myMetric, distance_matrix, cluster_iter, clusterAssign) <<"}" <<endl;
		}
		outputFile << "Clustering Time: " << Assign_Update_elapsed + Initialization_elapsed <<endl;
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
				items_in_cluster_itemName = ItemNamesFromItemNos(items_in_cluster_itemNo, size_of_cluster);
				cout << "PrintClusterUsingNames" << endl;
				clusterTable->PrintClusterUsingNames(outputFile, items_in_cluster_itemName, size_of_cluster, cluster_iter);
				delete[] items_in_cluster_itemNo;		//initialized inside PrintClusterDataForList
				delete[] items_in_cluster_itemName;		//initilaized inside ItemNamesFromItemNos
			}
		}
		for (int i = 0; i < myMetric->point_number; ++i)
		{
		    //clusterAssign[i] = new int[3];
		    clusterAssign[i][0] = -1;
		    clusterAssign[i][1] = -1;
		    clusterAssign[i][2] = -1;
		}
		//clusterTable->PrintingSilhouette(outputFile, myConf, distance_matrix, centroids, clusterAssign);
		cout << "finished CLARANS" <<endl;
	}
	CLARA_start = clock();
	for (int i = 0; i < myMetric->point_number; ++i)
	{
		delete clusterAssign[i];
	}
	delete[] clusterAssign;
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
	CLARA_finish = clock();
	CLARA_elapsed = (double)(CLARA_finish - CLARA_start)/CLOCKS_PER_SEC;
	//PRINTING SEGMENT
	//outputFile << "Algorithm: I" << init_iter+1 << "x" << assign_iter+1 << "x" << 1 <<endl;
	outputFile << "CLARA" <<endl;
	total = 0;
	for (int cluster_iter = 0; cluster_iter < myConf->number_of_clusters; cluster_iter++)
	{
		clusterTable->PrintClusterDataForList(cluster_iter, &size_of_cluster);		//used to get size
		outputFile << "CLUSTER-" << cluster_iter << " {" << size_of_cluster << ", " << clusterTable->ClusterDistance( myMetric, distance_matrix, cluster_iter, clusterAssign) <<"}" <<endl;
		total += size_of_cluster;
	}
	outputFile << "total on clusters: " <<total<<endl;
	outputFile << "Clustering Time: " << CLARA_elapsed <<endl;
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
			items_in_cluster_itemName = ItemNamesFromItemNos(items_in_cluster_itemNo, size_of_cluster);
			cout << "PrintClusterUsingNames" << endl;
			clusterTable->PrintClusterUsingNames(outputFile, items_in_cluster_itemName, size_of_cluster, cluster_iter);
			delete[] items_in_cluster_itemNo;		//initialized inside PrintClusterDataForList
			delete[] items_in_cluster_itemName;		//initilaized inside ItemNamesFromItemNos
		}
	}
	cout << "finished CLARA" <<endl;
	delete clusterTable;
	for (int i = 0; i < myMetric->point_number; ++i)
	{
		delete clusterAssign[i];
	}
	delete[] clusterAssign;
}

