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
void Hash<T>::initHash(int k, string metric) {
    int tableSize;
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
    }
    this->tableSize = tableSize;
	this->hashTable = new headHashNode<T>[tableSize]();
    this->metric_space = metric;
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