#ifndef HASH_H
#define HASH_H

#include "Headers.h"
#include "Node.h"
#include "TrickList.h"

using namespace std;

extern "C"
{
	#include <stdlib.h>
}


template <typename T>
class headHashNode
{
	public:
		headHashNode();
		//headHashNode(int k, string metric_space);
		~headHashNode();
		Node<T>* getNext();
		Node<T>* getBucket();
		void initHeadHashNode(string metric);
		void InsertTrick(int g, TrickList<T>* trickList, int L);
		void setBucketKey(int key);
		void printHash();
		void setBucket(Node<T>* bucket);
		int Insert(int hashResult, Node<T>* newItem);
		int Insert(int hashResult, Node<T>* newItem, int g);
		int getBucketKey();

	private:
	    int bucket_key;
		Node<T>* bucket;
};



template <typename T>
class Hash
{
	public:
		Hash(int k, string metric_space);
		Hash();
		~Hash();
		//void initHash(int k, string metric_space);
		void initHash(int tableSize);//, string metric);
		void setNext(Node<T>* next);
		void setKey(T key);
		void Insert(int hashResult, T newItem);
		void Insert(int hashResult, T newItem, int g, int itemno, std::string itemName);
		void MoveToBack(int item_no, int cluster_no);
		void printHash();
		T getKey();
		headHashNode<T>* getHashTable();

	private:
		int tableSize;
		string metric_space;
		headHashNode<T>* hashTable;
};


#endif // HASH_H