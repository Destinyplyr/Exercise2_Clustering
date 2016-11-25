#include "DistanceMatrixFunctions.h"
#include "ClusterNode.h"
#include "UtilsH.h"

class ClusterTable
{
	public:
		// ClusterTable();;
		// ~ClusterTable();;
		// ClusterTable(int number_of_clusters);;
		// ClusterTable* getNext();;
		// void setNext(ClusterTable* next);;
		// void setItemNo(int item_no);;
		// int getItemNo();;
		ClusterTable();
		ClusterTable(int number_of_clusters);
		~ClusterTable();
		ClusterNode** getArray();
		void setArray(ClusterNode** clusterTable);
		ClusterNode* getList();
		void setList(ClusterNode* table);
		int getClusterNumber();
		void setClusterNumber(int number_of_clusters);
		void Remove(int item_no, int cluster_no); 
		void InsertAtCluster(int item_no, int cluster_no); 
		int ClusterDistance(double** distanceMatrix, int cluster_no);
		double ClusterDistanceFromCentroid(double** distanceMatrix, int cluster_no, int centroid);
		double ClusterSilhouette(Conf* myConf, double** distanceMatrix, int* centroids,  int cluster_no, int** clusterAssign);
		void Init_Tables(double*** distanceMatrix, Metrics* myMetric, Conf* myConf, int** centroids, ClusterTable** clusterTable, int*** clusterAssign);
		double PrintingSilhouette(Conf* myConf, double** distanceMatrix, int* centroids, int** clusterAssign);
		int ReturnClusterSize(int cluster_no);
		void PrintCluster(int cluster_no);
		// void PrintData();;
		// void Insert(T item, int itemno, std::string itemName);;
		// void initEuclideanList(std::ifstream& inputFile, std::ifstream& queryFile, int k, int L, std::ofstream& outputfile, int* dataLength);;
		// void initCosineList(std::ifstream& inputFile, std::ifstream& queryFile, int k, int L, std::ofstream& outputfile,  int* dataLength);;
		// void initDBHManagement(std::ifstream& inputFile, std::ifstream& queryFile, int k, int L, std::ofstream& outputfile, int* dataLength);;
		// int Distance(T item1, T item2);;
		// double CosineDistance(double p1[], double p2[], int size);;
		// bool HammingDuplicate(T item);;
		// bool EuclideanDuplicate(T item, int size);;
		// void ListInsertionVector(std::ifstream& inputFile, Metrics* myMetric);;
		// void DistanceMatrixComputationVector(Metrics* myMetric, double** distance_matrix);;
		// void ListInsertionDB(std::ifstream& inputFile, Metrics* myMetric);;
		// void DistanceMatrixComputationDB(std::ifstream& inputFile, Metrics* myMetric, double** distance_matrix);;
		
	private:
		int number_of_clusters;
		ClusterNode** clusterTable;
};