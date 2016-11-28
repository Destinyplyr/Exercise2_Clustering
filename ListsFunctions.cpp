#include "Headers.h"
#include "ListData.h"

template <typename T>
ListData<T>::ListData()
{
	header = NULL;
	//cout << "------->  ListData initialized successfully!" << endl << endl;
}


template <typename T>
ListData<T>::~ListData()
{
	if (header != NULL)
	{
		delete header;
		header = NULL;
		//cout << "------->  Finished processing the ListData." << endl;
	}
	else
	{
		//cout << "------->  Finished processing the ListData." << endl;
	}
}


template <typename T, size_t N>
inline
size_t sizeOfArray( const T(&)[ N ] )
{
	return N;
}


template <typename T>
Node<T>* ListData<T>::getNode()
{
	return header;
}


template <typename T>
void ListData<T>::PrintData()
{
	Node<T>* node = new Node<T>();
	node = header;
	int counter = 1;
	while (node->getNext() != NULL)
	{
		cout << "Item " << counter << " in list : " << node->getKey()[0] << endl;
		node = node->getNext();
		++counter;
	}

	cout << "Item " << counter << " in list : " << node->getKey()[0] << endl;
}


template <typename T>
void ListData<T>::Insert(T newItem, int itemno, string itemName)
{
 	Node<T>* node = new Node<T>(newItem, 0, itemno, itemName);
	if (header == NULL)
    {
		header = node;
    }
	else
	{
		Node<T>* tail = header;
		while (tail->getNext() != NULL)
		{
			tail = tail->getNext();
		}
		tail->setNext(node);
	}

	//cout << "Item inserted" << endl;
}

template <typename T>
int ListData<T>::Distance(T item1, T item2)
{
	int distance = 0;
	int i = 0, j = 0;

	while ((i < item1.size()) && (j < item2.size()))
	{
		if (item1[i] == item2[j])
		{
			//cout << "Same bit" << endl;
			++i;
			++j;
		}
		else
		{
			//cout << "Different bit" << endl;
			++distance;
			++i;
			++j;
		}
	}

	return distance;
}


template <typename T>
double ListData<T>::DistanceB2BHamming(T item1, T item2)
{
	return (item1 ^= item2).count();
}


template <typename T>
double ListData<T>::CosineDistance(double item1[], double item2[], int size)      //Cosine
{
	double norm1, norm2;
	double cosine;

	norm1 = euclid_norm(item1, size);
	norm2 = euclid_norm(item2, size);
    cosine = dot_product(item1, item2, size) / (norm1 * norm2);

    return (1 - cosine);
}


template <typename T>
Node<T>* ListData<T>::ReturnHead() {
    return header;
}


template <typename T>
bool ListData<T>::HammingDuplicate(T item) {
	Node<T>* currentNode = header;
	while(currentNode != NULL) {
		if (item.compare(currentNode->getKey()) == 0) {
			return true;
		}
		currentNode = currentNode->getNext();
	}
	return false;
}

template <typename T>
bool ListData<T>::HammingB2BDuplicate(T item) {
	Node<T>* currentNode = header;
	while(currentNode != NULL) {
		if ((item ^= currentNode->getKey()) == 0) {
			return true;
		}
		currentNode = currentNode->getNext();
	}
	return false;
}


template <typename T>
bool ListData<T>::EuclideanDuplicate(T item, int size) {
	Node<T>* currentNode = header;
	while(currentNode != NULL) {
		if (SameArray(currentNode->getKey(), item, size)) {
			return true;
		}
		currentNode = currentNode->getNext();
	}
	return false;
}

template <typename T>
bool ListData<T>::ExistsOnce(int itemno, Node<T>* header_out)
{
	Node<T>* currentNode = header_out;
	//cout << endl;
	while (currentNode != NULL)
	{
		// cout << "once - current node key: " << currentNode->getKey() << endl;
		// cout << "once -current node itemno: " << currentNode->getItemNo() << endl;
		if (currentNode->getItemNo() == itemno) 
		{
			if (Exists(itemno, currentNode->getNext()) == false) 
			{
				return true;
			}
			else 
			{
				return false;
			}
		}
		currentNode = currentNode->getNext();
	}
	return false;
}

template <typename T>
bool ListData<T>::Exists(int itemno, Node<T>* header_out)
{
	Node<T>* currentNode = header_out;
	while (currentNode != NULL)
	{
		// cout << "simple - current node key: " << currentNode->getKey() << endl;
		// cout << "simple -current node itemno: " << currentNode->getItemNo() << endl;
		// cout << "simple: " << currentNode->getItemNo() << " " << itemno <<endl;
		if (currentNode->getItemNo() == itemno) 
		{
			return true;
		}
		currentNode = currentNode->getNext();
	}
	return false;
}

template <typename T>
string* ListData<T>::ItemNamesFromItemNos(int* items_in_cluster_itemNo, int size_of_cluster)
{
	Node<T>* currentNode;
	string* items_in_cluster_itemName = new string[size_of_cluster+1];
	for (int items_in_cluster_iter = 0; items_in_cluster_iter <= size_of_cluster; items_in_cluster_iter++)
	{
		currentNode = this->ReturnHead();
		while (currentNode != NULL) 
		{
			//cout << "currentNode->getItemNo()" << currentNode->getItemNo() << " items_in_cluster_itemNo[items_in_cluster_iter] " <<items_in_cluster_itemNo[items_in_cluster_iter] <<endl; 
			if (currentNode->getItemNo() == items_in_cluster_itemNo[items_in_cluster_iter])
			{
				//cout << "problem in if" <<endl;
				//cout << "currentNode->getItemName() " << currentNode->getItemName() <<endl;
				items_in_cluster_itemName[items_in_cluster_iter] = currentNode->getItemName();
			}
			currentNode = currentNode->getNext();
			//cout << "stuck on you" <<endl;
		}
		//cout << "and managed to get out" <<endl;
	}
	return items_in_cluster_itemName;
}

