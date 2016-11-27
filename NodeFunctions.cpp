#include "Headers.h"
#include "Node.h"


template <typename T>
Node<T>::Node()
{
	this->flagged_for_assignment = -1;
	this->flagged_as_assigned = -1;
	this->distance_from_centroid = INT_MAX;
	this->centroid = -1;
	this->itemno = -1;
    this->next = NULL;
	//cout << "Node created successfully!" << endl;
}


template <typename T>
Node<T>::Node(T key)
{
	this->flagged_for_assignment = -1;
	this->flagged_as_assigned = -1;
	this->distance_from_centroid = INT_MAX;
	this->centroid = -1;
	this->itemno = -1;
	this->key = key;		//Works for both Hamming (T = string) and Vector (T = double*)
	this->next = NULL;
	//cout << "Node created successfully!" << endl;
}


template <typename T>
Node<T>::Node(T key, int g, int itemno, string itemName)
{
	this->flagged_for_assignment = -1;
	this->flagged_as_assigned = -1;
	this->distance_from_centroid = INT_MAX;
	this->centroid = -1;
    this->itemno = itemno;
	this->key = key;			//Works for both Hamming (T = string) and Vector (T = double*)
	this->next = NULL;
	this->g = g;
	this->itemName = itemName;
	//cout << "Node created successfully!" << endl;
}


template <typename T>
Node<T>::~Node()
{
	if (next != NULL)
	{
		delete next;
		next = NULL;
		//cout << "------->  Node deleted." << endl;
	}
	else
	{
		//cout << "------->  Node deleted." << endl;
	}
}


template <typename T>
Node<T>* Node<T>::getNext()
{
	return next;
}


template <typename T>
void Node<T>::setNext(Node<T>* next)
{
	this->next = next;
}


template <typename T>
T Node<T>::getKey()
{
	return key;
}


template <typename T>
void Node<T>::setKey(T key)
{
	this->key = key;
}


template <typename T>
int Node<T>::getG()
{
	return g;
}


template <typename T>
void Node<T>::setG(int g)
{
	this->g = g;
}


template <typename T>
int Node<T>::getItemNo()
{
	return itemno;
}


template <typename T>
void Node<T>::setItemName(std::string itemName)
{
	this->itemName = itemName;
}
	

template <typename T>
string Node<T>::getItemName()
{
	return itemName;
}

template <typename T>
int Node<T>::getFlagForAssignment()
{
	return flagged_for_assignment;
}


template <typename T>
void Node<T>::setFlagForAssignment(int flagged_for_assignment)
{
	this->flagged_for_assignment = flagged_for_assignment;
}

template <typename T>
int Node<T>::getFlagAsAssigned()
{
	return flagged_as_assigned;
}


template <typename T>
void Node<T>::setFlagAsAssigned(int flagged_as_assigned)
{
	this->flagged_as_assigned = flagged_as_assigned;
}


template <typename T>
double Node<T>::getDistanceFromCentroid()
{
	return distance_from_centroid;
}


template <typename T>
void Node<T>::setDistanceFromCentroid(double distance_from_centroid)
{
	this->distance_from_centroid = distance_from_centroid;
}

template <typename T>
int Node<T>::getCentroid()
{
	return centroid;
}


template <typename T>
void Node<T>::setCentroid(int centroid)
{
	this->centroid = centroid;
}

template <typename T>
void Node<T>::setSecondBestCentroid(int second_best_centroid)
{
	this->second_best_centroid = second_best_centroid;
}


template <typename T>
int Node<T>::getSecondBestCentroid()
{
	return second_best_centroid;
}


template <typename T>
void Node<T>::setSecondBestDistance(int second_best_distance)
{
	this->second_best_distance = second_best_distance;
}


template <typename T>
int Node<T>::getSecondBestDistance()
{
	return second_best_distance;
}

