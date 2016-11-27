#include "Hash.h"


using namespace std;

//HEADHASHNODE FUNCTIONS

template <typename T>
headHashNode<T>::headHashNode()
{
    bucket_key = -1;
    bucket = NULL;
}


template <typename T>
headHashNode<T>::~headHashNode() 
{
    if (bucket != NULL)
    {
        delete bucket;
        bucket = NULL;
        //cout << "HeadHashNode deleted bucket." << endl;
    }
    else
    {
        //cout << "HeadHashNode deleted else ." << endl;
    }
}


template <typename T>
int headHashNode<T>::getBucketKey() {
    return bucket_key;
}


template <typename T>
void headHashNode<T>::setBucketKey(int bucket_key) {
    this->bucket_key = bucket_key;
}


template <typename T>
Node<T>* headHashNode<T>::getBucket()
{
    return bucket;
}


template <typename T>
void headHashNode<T>::setBucket(Node<T>* bucket)
{
    this->bucket = bucket;
}


template <typename T>
int headHashNode<T>::Insert(int hashResult, Node<T>* newItem, int g)
{
    newItem->setNext(this->bucket);
    newItem->setG(g);
    this->bucket = newItem;
    return 0;
}


template <typename T>
void headHashNode<T>::InsertTrick(int g, TrickList<T>* trickList, int L) {
    Node<T>* currentNode;
    currentNode = this->bucket;
    while(currentNode != NULL) {
        if (currentNode->getG() == g) {
            trickList->Insert(currentNode, L);
            //cout << "Added in trickList : " << currentNode->getKey()[0] << endl;
        }
        //cout << "NodeID: " << currentNode->getG() << " - g: " <<g <<endl;
        currentNode = currentNode->getNext();
    }
}


template <typename T>
void headHashNode<T>::printHash() {
    cout << endl;
    cout << ">>>>> Printing Bucket" <<endl;
    if (this->bucket_key == -1) {
        cout << "Bucket empty" << endl;
    }
    else {
        cout << ">> Bucket key: " << bucket_key << endl;
        Node<T>* current;
        current = this->bucket;

        while (current != NULL) {
            cout << "Item:" << current->getKey() <<endl;
            current = current->getNext();
        }

        cout << ">>>>> " <<endl;
        cout << endl;
    }
}


template <typename T>
Hash<T>::Hash()
{
	hashTable = NULL;
}


template <typename T>
void Hash<T>::initHash(int tableSize) {
/*    int tableSize;
    //cout << "metric_space " << metric << endl;
    if (strcmp(metric.c_str(), "hamming") == 0) {
        tableSize = pow(2, k);
    }
    if (strcmp(metric.c_str(), "euclidean") == 0) {
        tableSize = k;
    }
    if (strcmp(metric.c_str(), "cosine") == 0) {
        tableSize = pow(2, k);
    }
    if (strcmp(metric.c_str(), "matrix") == 0) {
        tableSize = pow(2, k);
    }*/
    this->tableSize = tableSize;
	this->hashTable = new headHashNode<T>[tableSize]();
    //this->metric_space = metric;
}


template <typename T>
headHashNode<T>* Hash<T>::getHashTable()
{
    return hashTable;
}


template <typename T>
void Hash<T>::Insert(int hashResult, T newItem, int g, int itemno, string itemName) {
    if (this->hashTable[hashResult].getBucketKey() == -1) {       //First item on this bucket
        this->hashTable[hashResult].setBucketKey(hashResult);
    }

    Node<T>* newNode = new Node<T>(newItem, g, itemno, itemName);
    this->hashTable[hashResult].Insert(hashResult, newNode, g);
    cout << "Printing in Hash<T>::Insert just insert: " << hashTable[hashResult].getBucket()->getItemNo()<<endl;
}

template <typename T>
void Hash<T>::MoveToBack(int item_no, int cluster_no) 
{
    Node<T>* currentNode = hashTable[cluster_no].getBucket();
    Node<T> *prev = NULL;
    Node<T> *list = currentNode;
    Node<T> *list2 = currentNode;
    if (currentNode != NULL) 
    {
        cout << "cluster_no" << cluster_no <<endl;
/*        while (list2 != NULL)
        {
            cout << "we have a friend here - 809 - all points in cluster" << list2->getItemNo() <<endl;
            list2 = list2->getNext();
        }*/
        cout << "IN remove part of movetoback " << cluster_no<< endl;
        cout << "movetoback 1" <<endl;

        while ((list->getNext() != NULL) && (list->getItemNo() != item_no)) 
        {
            cout << "we have a friend here - 807 - all points until wanted " << list->getItemNo() <<endl;
            prev = list;
            list = list->getNext();
        }
        cout << "movetoback 2" <<endl;
        if (list->getItemNo() == item_no) 
        {
            cout << "movetoback 3" <<endl;
            if (prev == NULL) 
            {
                cout << "movetoback 4.1" <<endl;
                Node<T> *next= list->getNext();
                //delete list;
                cout << "movetoback 4.2" <<endl;
                hashTable[cluster_no].setBucket(next);
            } 
            else 
            {
                cout << "movetoback 5.1" <<endl;
                Node<T> *_next = list->getNext();
                //delete list;
                cout << "movetoback 5.2" <<endl;
                prev->setNext(_next);
            }
        }
    }
    currentNode = list;
    list = hashTable[cluster_no].getBucket();
    while (list != NULL)
    {
        //cout << "we have a friend here - 907 - all points in bucket: to add back " << list->getItemNo() <<endl;
        prev = list;
        list = list->getNext();
    }
    //newNode = new ClusterNode(item_no, NULL);
    cout << "ready to add on back" <<endl;
    currentNode->setNext(NULL);
    if (prev == NULL)
    {
        hashTable[cluster_no].setBucket(currentNode);
        //cout << "sett prev first" <<endl;
    }
    else
    {
        prev->setNext(currentNode);
        //cout << "sett prev" <<endl;
    }
    cout << "added on back" <<endl;
    list = hashTable[cluster_no].getBucket();
/*    while (list != NULL)
    {
        cout << "we have a friend here - 906 - all points in bucket: added back " << list->getItemNo() <<endl;
        prev = list;
        list = list->getNext();
    }*/
    //cout << "Item inserted in hash table with hash : " << cluster_no <<endl;
}




template <typename T>
Hash<T>::~Hash()
{
    if (hashTable != NULL)
    {
        delete[] hashTable;
        hashTable = NULL;
        //cout << "Hash table deleted." << endl;
    }
    else
    {
        //cout << "Hash table deleted." << endl;
    }
}


template <typename T>
void Hash<T>::printHash() {
    cout << endl;
    cout << "------- Printing Hash Table -------" <<endl;
    for (int i = 0; i < tableSize; i++) {
        this->hashTable[i].printHash();
    }
    cout << "------- ------------------- -------" <<endl;
    cout << endl;
}