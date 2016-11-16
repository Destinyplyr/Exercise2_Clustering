#ifndef TRICK_LIST
#define TRICK_LIST

#include "Node.h"
#include <math.h>
#include <fstream>


template <typename T>
class TrickList		//The first of every tricklist is considered an info head
{
	public:
		TrickList();
		~TrickList();
		TrickList<T>* getNext();
		void setNext(TrickList<T>* next);
		void Insert(Node<T>* newItem, int L);
		void setG(Node<T>* gCode);
		void setL(int table);
		Node<T>* getGNode();
		Node<double*>* NNTrickList(double* thePoint, int size, std::ofstream &outputFile, int Radius, double* minOutsideDistance);
		int getL();
		static double Distance(double p1[], double p2[], int size);
	
	private:
		int table;
		Node<T>* gCode;
		TrickList<T>* next;
};


#endif