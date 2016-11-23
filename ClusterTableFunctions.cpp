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