#ifndef NODE_H
#define NODE_H

#include <string>

#include "Headers.h"

template <typename T>
class Node
{
	public:
		Node();
		Node(T key);
		Node(T key, int g, int itemno, std::string itemName);
		~Node();
		Node<T>* getNext();
		void setNext(Node<T>* next);
		void setKey(T key);
		void setG(int g);
		void setItemName(std::string itemName);
		int getG();
		int getItemNo();
		T getKey();
		std::string getItemName();
		int getFlagForAssignment();
		void setFlagForAssignment(int flagged_for_assignment);
		int getFlagAsAssigned();
		void setFlagAsAssigned(int flagged_as_assigned);
		double getDistanceFromCentroid();
		void setDistanceFromCentroid(double distance_from_centroid);
		int getCentroid();
		void setCentroid(int centroid);
		void setSecondBestCentroid(int second_best_centroid);
		int getSecondBestCentroid();
		void setSecondBestDistance(int second_best_distance);
		int getSecondBestDistance();



	private:
		int flagged_for_assignment;
		int flagged_as_assigned;
		double distance_from_centroid;
		int centroid;
		int second_best_centroid;
		int second_best_distance;
	    int itemno;
		int g;
		T key;
		std::string itemName;
		Node<T>* next;
};



#endif // NODE_H