#include "Headers.h"
#include "ListData.h"

template <typename T>
void ListData<T>::ListInsertion(std::ifstream& inputFile, Metrics* myMetric)
{
	string GARBAGE;
	string genericStr;
	string pointStr;
	string itemNos;
	int point_number = 0;
	int index;
	double* point;

	inputFile >> GARBAGE;  					//Read "@metric space"
	inputFile >> GARBAGE;					//Read etc, "hamming"

	if (strcmp(GARBAGE.c_str(), "vector") == 0)
	{
		inputFile >> itemNos;  				//Read "@metric space"
		if (strcmp(itemNos.c_str(), "@metric") == 0) {
			inputFile >> GARBAGE;		//Read etc, "hamming"
			inputFile >> itemNos;
		}
		else {
			//myMetric->metric = "euclidean";
			//point_number++;
		}
		getline(inputFile, genericStr);
		do {
			index = 0;
			point_number++;
			//cout << "apo th getline katw " << genericStr << endl;
	   		stringstream linestream(genericStr);
	   		getline(linestream, pointStr, '\t');
	   		point = new double[myMetric->point_dimension];
	   		while (getline(linestream, pointStr, '\t'))    //Calculate dimension of points
	        {			
	        	point[index] = strtod(pointStr.c_str(), NULL);
	        	cout << " point ha : " << point[index] << endl;
				index++;
	   		}
	   		if (!this->EuclideanDuplicate(point, myMetric->point_dimension)) {
	   			this->Insert(point, point_number, itemNos);
	   		}
	   		inputFile >> itemNos;		//next itemno
	   		cout << "item NOs : " << itemNos << endl;
   		}while(getline(inputFile, genericStr));
   		cout << "point number : " << point_number << endl;
	}
}