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


