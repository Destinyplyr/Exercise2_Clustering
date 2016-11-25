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
        cout << "IN Remove " << cluster_no<< endl;
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
        //cout << "we have a friend here - 907" <<endl;
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
    //cout << "in ClusterDistanceFromCentroid" << endl;
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
   //cout << "before whiel - " << endl;
    //cout << "ginetai auto? " << currentNode->getItemNo() << endl;
    while (currentNode != NULL) {
        //cout << "in while" << endl;
        clusterDistance += DistanceMatrixDistance(distanceMatrix, centroid, currentNode->getItemNo());
        //cout << "curr dis: " << clusterDistance <<endl;
        currentNode = currentNode->getNext();
    }
    return clusterDistance;
}

void ClusterTable::Init_Tables(double*** distance_matrix, Metrics* myMetric, Conf* myConf, int** centroids, ClusterTable** clusterTable, int*** clusterAssign)
{
    cout << "in Init_Tables" << endl;
    (*distance_matrix) = new double*[myMetric->point_number];       //distance matrix creation
    cout << "before fore" <<endl;
    for (int i = 0; i < myMetric->point_number; i++) {
        (*distance_matrix)[i] = new double[myMetric->point_number];
    }
    cout << "ekana to distance" << endl;
    (*centroids) = new int[myMetric->point_number];
    cout << "ekana to insertion" << endl;

    (*clusterTable) = new ClusterTable(myConf->number_of_clusters);
    cout << "list: " << (*clusterTable)->getArray() <<endl;
    (*clusterAssign)= new int*[myMetric->point_number];
    for (int i = 0; i < myMetric->point_number; ++i)
    {
        (*clusterAssign)[i] = new int[3];
        (*clusterAssign)[i][0] = -1;
        (*clusterAssign)[i][1] = -1;
        (*clusterAssign)[i][2] = -1;
    }
}

int ClusterTable::ReturnClusterSize(int cluster_no)
{
    ClusterNode* currentNode;
    currentNode = clusterTable[cluster_no];
        
    if (currentNode == NULL)
    {
        cout << "einAI NULL o currentNode in ReturnClusterSize " << endl;
        cout << "exiting..." << endl;
        exit(1);
    }

    int count_items = 0;
    while(currentNode != NULL)
    {
        count_items++;
        currentNode = currentNode->getNext();
    }
    return count_items;
}


void ClusterTable::PrintCluster(int cluster_no)
{
    ClusterNode* currentNode = clusterTable[cluster_no];
        
    if (currentNode == NULL)
    {
        cout << "einAI NULL o currentNode in PrintCluster " << endl;
        cout << "exiting..." << endl;
        exit(1);
    }

    while(currentNode != NULL)
    {
        cout << "Printing Cluster : " << currentNode->getItemNo() << endl;
        //count_items++;
        currentNode = currentNode->getNext();
    }
}


double ClusterTable::ClusterSilhouette(Conf* myConf, double** distanceMatrix, int* centroids,  int cluster_no, int** clusterAssign)
{
    double avg_silh = 0;
    int number_in_cluster = 0;          //number of items in cluster
    int number_in_scnd_cluster = 0;     //number of items in second best cluster
    double b_i, a_i;
    int number_of_scnd_cluster;         //index for second best cluster in clusterTable
    ClusterNode* currentNode = clusterTable[cluster_no];
    int times = 0;

    if (currentNode == NULL)
    {
        cout << "einAI NULL o currentNode ston silhouette ypologismo " << endl;
        cout << "exiting..." << endl;
    }

    ClusterNode* secondNode = NULL;
    //cout << "PRINTIG CLUSTER NUMBER " << cluster_no << endl;
    number_in_cluster = ReturnClusterSize(cluster_no);
    cout << "current cluster size: " << number_in_cluster <<endl;
    currentNode = clusterTable[cluster_no];
    while (currentNode != NULL) {
        ++times;
        // cout << "THIS TIME : " << times << endl;
        number_of_scnd_cluster = ReturnCluster(myConf, centroids, clusterAssign[currentNode->getItemNo()][1]);
        //cout << "THIS CENTROID : " << clusterAssign[currentNode->getItemNo()][1] << endl;
        //cout << "number_of_scnd_cluster : " << number_of_scnd_cluster << endl;
        // if (number_of_scnd_cluster == cluster_no)
        // {
        //     cout << "WE HAVE THE SAME FUCKING CLUSTERS" << endl;
        //     break;
        //     //exit(7);
        // }
        secondNode = clusterTable[number_of_scnd_cluster];
        number_in_scnd_cluster = ReturnClusterSize(number_of_scnd_cluster);
        a_i = (double)ClusterDistanceFromCentroid(distanceMatrix, cluster_no, currentNode->getItemNo()) / (double) number_in_cluster;
        cout << "Silhouette: a_i of " << currentNode->getItemNo() << " : " << a_i <<endl;
        b_i = (double) ClusterDistanceFromCentroid(distanceMatrix, number_of_scnd_cluster, currentNode->getItemNo()) / (double)number_in_scnd_cluster;
        cout << "Silhouette: b_i of " << currentNode->getItemNo() << " : " << b_i <<endl;
        if (a_i >= b_i) 
        {
            cout << "Silhouette: adding in avg: " << (double)(b_i - a_i) / (double) a_i <<endl;
            avg_silh += (double)(b_i - a_i) / (double) a_i;
            cout << "Silhouette: current avg_silh : " <<avg_silh <<endl;
        }
        else
        {
            cout << "Silhouette: adding in avg: " << (double)(b_i - a_i) / (double) b_i <<endl;
            avg_silh += (double)(b_i - a_i) / (double) b_i;
            cout << "Silhouette: current avg_silh " << currentNode->getItemNo() << " : " << avg_silh <<endl;
        }
        currentNode = currentNode->getNext();
    }
    cout << "Silhouette: return silhouette :" << ((double)avg_silh/(double) number_in_cluster) << endl;
    return ((double)avg_silh/(double) number_in_cluster);
}


double ClusterTable::PrintingSilhouette(Conf* myConf, double** distanceMatrix, int* centroids, int** clusterAssign)
{
    double* s_i = new double[myConf->number_of_clusters];
    double s_total = 0;
    cout << "Silhouette: [";
    for (int i = 0; i < myConf->number_of_clusters; ++i)
    {
        s_i[i] = this->ClusterSilhouette(myConf, distanceMatrix, centroids,  i, clusterAssign);
        cout << s_i[i] << ", ";
        s_total += s_i[i];
    }
    cout << "after for loop in PrintingSilhouette " << endl;
    cout << s_total / myConf->number_of_clusters << "]" <<endl;
}


