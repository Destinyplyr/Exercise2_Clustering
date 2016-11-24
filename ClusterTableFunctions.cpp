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
        cout << "I have not yet been added -909" <<endl;
		return;
	}
    if (clusterTable[cluster_no] != NULL) 
    {
        cout << "IN Remove " << endl;
    	ClusterNode *prev = NULL;
        ClusterNode *list = clusterTable[cluster_no];
        cout << "rem 1" <<endl;
        while ((list->getNext() != NULL) && (list->getItemNo() != item_no)) 
        {
        	prev = list;
            list = list->getNext();
        }
        cout << "rem 2" <<endl;
        if (list->getItemNo() == item_no) 
        {
            cout << "rem 3" <<endl;
        	if (prev == NULL) 
            {
                cout << "rem 4.1" <<endl;
            	ClusterNode *next= list->getNext();
                delete list;
                cout << "rem 4.2" <<endl;
                clusterTable[cluster_no] = next;
            } 
            else 
            {
                cout << "rem 5.1" <<endl;
            	ClusterNode *_next = list->getNext();
                delete list;
                cout << "rem 5.2" <<endl;
            	prev->setNext(_next);
            }
        }
    }
}





void ClusterTable::InsertAtCluster(int item_no, int cluster_no) 
{
    if (cluster_no == -1) {
        cout << "This should not happen - 908" <<endl;
        return;
    }
	ClusterNode* prev = NULL;
    ClusterNode* list = this->clusterTable[cluster_no];
    ClusterNode* newNode;
    while (list != NULL)
    {
        cout << "we have a friend here - 907" <<endl;
        prev = list;
        list = list->getNext();
    }
    newNode = new ClusterNode(item_no, NULL);
    if (prev == NULL)
    {
        clusterTable[cluster_no] = newNode;
        cout << "sett prev first" <<endl;
    }
    else
    {
        prev->setNext(newNode);
        cout << "sett prev" <<endl;
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
    cout << "in ClusterDistanceFromCentroid" << endl;
    double minDistance = INT_MAX;
    double clusterDistance = 0;
    int minDistanceMedoid = -1;
    ClusterNode* currentNode;
    currentNode = this->clusterTable[cluster_no];
    // if (currentNode == NULL)
    // {
    //     cout << "einAI NULL" << endl;
    //     exit(1);
    // }
   cout << "before whiel - " << endl;
    //cout << "ginetai auto? " << currentNode->getItemNo() << endl;
    while (currentNode != NULL) {
        //cout << "in while" << endl;
        clusterDistance += DistanceMatrixDistance(distanceMatrix, centroid, currentNode->getItemNo());
        //cout << "curr dis: " << clusterDistance <<endl;
        currentNode = currentNode->getNext();
    }
    return clusterDistance;
}




