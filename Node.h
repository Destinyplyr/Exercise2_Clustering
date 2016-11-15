#ifndef NODE_H
#define NODE_H

#include <string>

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

	private:
	    int itemno;
		int g;
		T key;
		std::string itemName;
		Node<T>* next;
};

#endif // NODE_H