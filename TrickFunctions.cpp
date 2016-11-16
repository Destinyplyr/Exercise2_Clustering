#include <iostream>
#include "TrickList.h"

using namespace std;


template <typename T>
TrickList<T>::TrickList()
{
    gCode = NULL;
    this->next = NULL;
    table = 0;
	//cout << "TrickList initialized successfully!" << endl;
}


template <typename T>
TrickList<T>::~TrickList()
{
	if (next != NULL)
	{
		delete next;
		//cout << "TrickList node deleted." << endl;
	}
	else
	{
		//cout << "TrickList node deleted." << endl;
	}
}


template <typename T>
TrickList<T>* TrickList<T>::getNext()
{
	return next;
}


template <typename T>
void TrickList<T>::setNext(TrickList<T>* next)
{
	this->next = next;
}


template <typename T>
Node<T>* TrickList<T>::getGNode()
{
	return gCode;
}


template <typename T>
void TrickList<T>::setG(Node<T>* gCode)
{
	this->gCode = gCode;
}


template <typename T>
int TrickList<T>::getL()
{
	return table;
}


template <typename T>
void TrickList<T>::setL(int table)
{
	this->table = table;
}


template <typename T>
void TrickList<T>::Insert(Node<T>* newItem, int L)
{
    string GARBAGE;
	TrickList<T>* node = new TrickList<T>();
	node->setG(newItem);
	node->setNext(NULL);
	node->setL(L);

	if (this->next == NULL)
    {
		this->next = node;
    }
	else
	{
		TrickList<T>* tail = this->next;
		while (tail->getNext() != NULL)
		{
			tail = tail->getNext();
		}
		tail->setNext(node);
	}
}


template <typename T>
double TrickList<T>::Distance(double item1[], double item2[], int size)
{
	double sum = 0.0f, square;
	double x, y;
	int i = 0, j = 0;

	while ((i < size) && (j < size))
	{

		x = item1[i];
		y = item2[j];
		square = pow((x - y), 2);
		sum += square;
		++i;
		++j;
	}
	return sqrt(sum);
}


template <typename T>
Node<double*>* TrickList<T>::NNTrickList(double* thePoint, int size, ofstream &outputFile, int Radius, double* minOutsideDistance)
{
	double minDistance = 999999;
	TrickList<T>* currentNode = this->next;
	double euclDis;
	TrickList<double*>* minNode = NULL;
	while (currentNode != NULL)
	{
		
		euclDis = Distance(currentNode->getGNode()->getKey(), thePoint, size);
		if ((euclDis <= Radius) && (Radius > 0))
		{
			outputFile << "Table " << currentNode->getL() <<  "--" << currentNode->getGNode()->getItemName() << endl;
		}
		else if (Radius > 0){
			outputFile << "Table " << currentNode->getL() <<  "--" << currentNode->getGNode()->getItemName() << " (distance greater than Radius)" << endl;
		}

		if (euclDis < minDistance)
		{
			minDistance = euclDis;
			minNode = currentNode;
		}

		currentNode = currentNode->getNext();
	}
	*minOutsideDistance = minDistance;
	if (minNode != NULL)
	{
		return minNode->getGNode();
	}
	else
	{
		return NULL;
	}
}