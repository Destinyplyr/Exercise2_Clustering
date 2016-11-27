#ifndef LIST_DATA
#define LIST_DATA

#include "Node.h"
#include "MathFunctions.h"
#include "Returns.h"
#include "Hash.h"

template <typename T>
class ListData
{
	public:
		ListData();
		~ListData();
        Node<T>* ReturnHead();
        Node<T>* getNode();
		void PrintData();
		void Insert(T item, int itemno, std::string itemName);
		void initEuclideanList(std::ifstream& inputFile, std::ifstream& queryFile, int k, int L, std::ofstream& outputfile, int* dataLength);
		void initCosineList(std::ifstream& inputFile, std::ifstream& queryFile, int k, int L, std::ofstream& outputfile,  int* dataLength);
		void initDBHManagement(Conf* myConf, ifstream& inputFile, double** distanceMatrix, int k, int L, int* dataLength, int* hashCreationDone, Hash<double>* hashTableList, int* centroids);
		int Distance(T item1, T item2);
		double CosineDistance(double p1[], double p2[], int size);
		bool HammingDuplicate(T item);
		bool HammingB2BDuplicate(T item);
		bool EuclideanDuplicate(T item, int size);
		void ListInsertionVector(std::ifstream& inputFile, Metrics* myMetric);
		void DistanceMatrixComputationVector(Metrics* myMetric, double** distance_matrix);
		void ListInsertionDB(std::ifstream& inputFile, Metrics* myMetric);
		void DistanceMatrixComputationDB(std::ifstream& inputFile, Metrics* myMetric, double** distance_matrix);
		void ListInsertionHamming(std::ifstream& inputFile, Metrics* myMetric);
		double DistanceB2BHamming(T item1, T item2);
		void DistanceMatrixComputationHamming(Metrics* myMetric, double** distance_matrix);
		
	private:
		Node<T>* header;
};


#endif // !LIST_DATA_HAMMING