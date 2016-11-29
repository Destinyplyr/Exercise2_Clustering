#include "Headers.h"
#include "ClusterNode.h"

ClusterNode::ClusterNode()
{
	item_no = 0;
	next = NULL;
	//cout << "------->  ClusterNode initialized successfully!" << endl << endl;
}

ClusterNode::ClusterNode(int item_no, ClusterNode* next)
{
	this->item_no = item_no;
	this->next = next;
	//cout << "------->  ClusterNode initialized successfully!" << endl << endl;
}


ClusterNode::~ClusterNode()
{
/*
	cout << "mesa ston destructor tou ClusterNode" << endl;
	if (next != NULL)
	{
		delete next;
		next = NULL;
		cout << "------->  Finished processing the ClusterNode." << endl;
	}
	else
	{
		cout << "------->  Finished processing the ClusterNode." << endl;
	}*/
}



ClusterNode* ClusterNode::getNext()
{
	return next;
}


void ClusterNode::setNext(ClusterNode* next)
{
	this->next = next;
}


int ClusterNode::getItemNo()
{
	return item_no;
}


void ClusterNode::setItemNo(int item_no)
{
	this->item_no = item_no;
}
