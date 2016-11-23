#include "Headers.h"
#include "ListData.h"

template <typename T>
void ListData<T>::ListInsertionHamming(std::ifstream& inputFile, Metrics* myMetric)
{
	string GARBAGE;
	string genericStr;
	string pointStr;
	string itemNos;
	bitset<64> currentPoint;
	int point_number = 0;
	int index;
	double* point;

	inputFile >> GARBAGE;  					//Read "@metric space"
	inputFile >> GARBAGE;					//Read etc, "hamming"

	if (strcmp(GARBAGE.c_str(), "hamming") == 0)
	{
		inputFile >> itemNos;  				//Read "item1"
		// if (strcmp(itemNos.c_str(), "@metric") == 0) {
		// 	inputFile >> GARBAGE;		//Read etc, "hamming"
		// 	inputFile >> itemNos;
		// }
		// else {
		// 	//myMetric->metric = "euclidean";
		// 	//point_number++;
		// }
		getline(inputFile, genericStr);
		do {
			index = 0;
			point_number++;
			//cout << "apo th getline katw " << genericStr << endl;
	   		stringstream linestream(genericStr);
	   		getline(linestream, pointStr, '\t');
	   		getline(linestream, pointStr, '\t');
	   		//cout << "ptsrt:" << pointStr <<endl;
	   		currentPoint = bitset<64>(string(pointStr));
    		if (!this->HammingB2BDuplicate(currentPoint)) {
    			cout << "point inserted: " << currentPoint << " - " << point_number << " - " << itemNos <<endl;
    			this->Insert(currentPoint, point_number, itemNos);
    		}
    		inputFile >> itemNos;		//next itemno
	   		//cout << "item NOs : " << itemNos << endl;
	   // 		point = new double[myMetric->point_dimension];
	   // 		while (getline(linestream, pointStr, '\t'))    //Calculate dimension of points
	   //      {			
	   //      	point[index] = strtod(pointStr.c_str(), NULL);
	   //      	//cout << " point ha : " << point[index] << endl;
				// index++;
	   // 		}
	   // 		if (!this->EuclideanDuplicate(point, myMetric->point_dimension)) {
	   // 			//cout << "point inserted: " << point[0] << " - " << point_number << " - " << itemNos <<endl;
	   // 			this->Insert(point, point_number, itemNos);
	   // 		}
	   // 		inputFile >> itemNos;		//next itemno
	   		//cout << "item NOs : " << itemNos << endl;
   		}while(getline(inputFile, genericStr));
   		//cout << "point number : " << point_number << endl;
   		myMetric->point_number = point_number;
	}

}

template <typename T>
void ListData<T>::DistanceMatrixComputationHamming(Metrics* myMetric, double** distance_matrix) {
	Node<T>* driver_node;
	Node<T>* current_node;
	// distance_matrix = new double*[myMetric->point_number];		//distance matrix creation
	// for (int i = 0; i < myMetric->point_number; i++) {
	// 	distance_matrix[i] = new double[myMetric->point_number];
	// }

	driver_node = this->header;
	//cout << myMetric->point_number <<endl;

	for (int i = 0; i < myMetric->point_number; i++) {
		current_node = driver_node->getNext();
		//cout << "item " << i << "\t";
		for (int j = 0; j < myMetric->point_number; j++) {
			if (j <= i) {
				distance_matrix[i][j] = 0;
			}
			else {
				if (strcmp(myMetric->metric_space.c_str(), "hamming") == 0)
				{
					distance_matrix[i][j] = this->DistanceB2BHamming(current_node->getKey(), driver_node->getKey());
					//cout << distance_matrix[i][j] << "\t";
					current_node = current_node->getNext();
				}
			}
		}
		driver_node = driver_node->getNext();
		//cout <<endl;
	}
}