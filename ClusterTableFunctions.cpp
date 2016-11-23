#include "Headers.h"
#include "ClusterTable.h"

ClusterTable::ClusterTable()
{
	number_of_clusters = -1;
	clusterTable = NULL;
	//cout << "------->  ClusterTable initialized successfully!" << endl << endl;
}

ClusterTable::ClusterTable(int number_of_clusters)
{
	this->number_of_clusters = number_of_clusters;
	this->clusterTable = new ClusterNode*[number_of_clusters];
    cout << "list actuel: " << clusterTable << endl;
	for (int i = 0; i < number_of_clusters; ++i)
	{
		this->clusterTable[i] = NULL;
	}
	//cout << "------->  ClusterTable initialized successfully!" << endl << endl;
}


ClusterTable::~ClusterTable()
{
	for (int i = 0; i < number_of_clusters; i++)
   	{
	    if (clusterTable[i] != NULL) 
		{
	   		ClusterNode *prev = NULL;
	      	ClusterNode *list = clusterTable[i];
	      	while (list != NULL) 
	      	{
	        	prev = list;
	           	list = list->getNext();
	           	delete prev;
	      	}
		}
	}
}



ClusterNode** ClusterTable::getArray()
{
    return clusterTable;
}


void ClusterTable::setArray(ClusterNode** clusterTable)
{
    this->clusterTable = clusterTable;
}


ClusterNode* ClusterTable::getList()
{
    return *clusterTable;
}


void ClusterTable::setList(ClusterNode* table)
{
    *clusterTable = table;
}


int ClusterTable::getClusterNumber()
{
	return number_of_clusters;
}


void ClusterTable::setClusterNumber(int number_of_clusters)
{
	this->number_of_clusters = number_of_clusters;
}




void ClusterTable::Remove(int item_no, int cluster_no) 
{

	if (cluster_no == -1)
	{
		return;
	}

    if (clusterTable[cluster_no] != NULL) 
    {
    	ClusterNode *prev = NULL;
        ClusterNode *list = clusterTable[cluster_no];
        while ((list->getNext() != NULL) && (list->getItemNo() != item_no)) 
        {
        	prev = list;
            list = list->getNext();
        }
        if (list->getItemNo() == item_no) 
        {
        	if (prev == NULL) 
            {
            	ClusterNode *next= list->getNext();
                delete list;
                clusterTable[cluster_no] = next;
            } 
            else 
            {
            	ClusterNode *_next = list->getNext();
                delete list;
            	prev->setNext(_next);
            }
        }
    }
}





void ClusterTable::InsertAtCluster(int item_no, int cluster_no) 
{
    if (cluster_no == -1) {
        return;
    }
	ClusterNode* prev = NULL;
    ClusterNode* list = clusterTable[cluster_no];
    while (list != NULL)
    {
        prev = list;
        list = list->getNext();
    }
    list = new ClusterNode(item_no, NULL);
    if (prev == NULL)
    {
        clusterTable[cluster_no] = list;
    }
    else
    {
        prev->setNext(list);
    }

    //cout << "Item inserted in hash table with hash : " << cluster_no <<endl;
}


int ClusterTable::ClusterDistance(double** distanceMatrix, int cluster_no)      //return medoid
{
    double minDistance = INT_MAX;
    double clusterDistance;
    int minDistanceMedoid = -1;
    ClusterNode* driverNode = this->clusterTable[cluster_no];
    ClusterNode* currentNode;
    while (driverNode != NULL) 
    {
        cout << "#############new driver " <<endl;
        clusterDistance = 0;
        currentNode = this->clusterTable[cluster_no];
        while (currentNode != NULL) {
            clusterDistance += DistanceMatrixDistance(distanceMatrix, driverNode->getItemNo(), currentNode->getItemNo());
            //  cout << "curr dis: " << clusterDistance <<endl;
            currentNode = currentNode->getNext();
        }
        if (clusterDistance < minDistance) {
            minDistance = clusterDistance;
            cout << "curr dis is min dis" <<endl;
            minDistanceMedoid = driverNode->getItemNo();
        }
        driverNode = driverNode->getNext();
        cout << "#############" <<endl;
    }
    cout << "giving " << minDistanceMedoid <<" back" <<endl;
    return minDistanceMedoid;
}


double ClusterTable::ClusterDistanceFromCentroid(double** distanceMatrix, int cluster_no, int centroid)      //return distance of cluster from point
{
    double minDistance = INT_MAX;
    double clusterDistance = 0;
    int minDistanceMedoid = -1;
    ClusterNode* currentNode;
    currentNode = this->clusterTable[cluster_no];
    while (currentNode != NULL) {
        clusterDistance += DistanceMatrixDistance(distanceMatrix, centroid, currentNode->getItemNo());
        //  cout << "curr dis: " << clusterDistance <<endl;
        currentNode = currentNode->getNext();
    }
    return clusterDistance;
}




