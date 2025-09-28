#include <sstream>
#include <iostream>
#include <vector>
#include <string>


using namespace std;

template <typename T>
class LinkedList {

public:
	struct Node {

		T data;
		Node* next;
		Node* prev;

	};

	void AddHead(const T& data);
	void AddTail(const T& data);
	void AddNodesHead(const T* data, unsigned int count);
	void AddNodesTail(const T* data, unsigned int count);
	unsigned int NodeCount() const;
	void PrintForward() const;
	void PrintReverse() const;
	void FindAll(vector<Node*>& outData, const T& value) const;
	const Node* Find(const T& data) const;
	Node* Find(const T& data);
	const Node* GetNode(unsigned int index) const;
	Node* GetNode(unsigned int index);
	const Node* Head() const;
	Node* Head();
	const Node* Tail() const;
	Node* Tail();
	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);
	LinkedList<T>& operator=(const LinkedList<T>& rhs);
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	~LinkedList();

private:
	Node* head;
	Node* tail;
	unsigned int count;

};

template <typename T>
LinkedList<T>::LinkedList() {

	count = 0;
	head = nullptr;
	tail = nullptr;

}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {

	count = list.count;

	head = nullptr;
	tail = nullptr;

	Node* x = list.head;
	while (x != nullptr) {

		AddTail(x->data);
		x = x->next;

	}
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
	if (this != &rhs) {

		count = rhs.count;

		Node* temp = head;
		while (temp != nullptr) {

			Node* y = temp->next;
			delete temp;
			temp = y;
		}

		head = nullptr;
		tail = nullptr;

		Node* x = rhs.head;
		while (x != nullptr) {

			AddTail(x->data);
			x = x->next;

		}
	}
	return *this;

}


template <typename T>
LinkedList<T>::~LinkedList() {

	Node* n = head;
	while (n != nullptr) {

		Node* x = n;
		n = n->next;
		delete x;

	}
}

template <typename T>
void LinkedList<T>::AddHead(const T& data) {

	Node* n = new Node;
	n->data = data;
	n->next = nullptr;
	n->prev = nullptr;

	if (head == nullptr) {

		head = n;
		tail = n;
	}
	else {

		head->prev = n;
		n->next = head;
		head = n;
	}

	count++;

}

template <typename T>
void LinkedList<T>::AddTail(const T& data) {

	Node* n = new Node;
	n->data = data;
	n->next = nullptr;
	n->prev = nullptr;

	if (head == nullptr) {

		head = n;
		tail = n;
	}
	else {

		Node* temp = head;
		while (temp->next != nullptr) {

			temp = temp->next;

		}
		temp->next = n;
		n->prev = temp;
		tail = n;

	}
	count++;
}

template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {

	for (int i = (count - 1); i >= 0; --i) {

		this->AddHead(data[i]);

	}
}

template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {

	for (unsigned int i = 0; i < count; i++) {

		this->AddTail(data[i]);
	}
}

template <typename T>
unsigned int LinkedList<T>::NodeCount() const {

	return count;
}
template <typename T>
void LinkedList<T>::PrintForward() const {

	Node* n;
	n = head;
	while (n != nullptr) {

		cout << n->data << endl;
		n = n->next;

	}
}

template <typename T>
void LinkedList<T>::PrintReverse() const {

	Node* n;
	n = tail;
	while (n != nullptr) {
		cout << n->data << endl;
		n = n->prev;

	}
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {

	return head;

}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {

	return head;

}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {

	return tail;

}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {

	return tail;

}

template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const {

	Node* n = head;
	while (n != nullptr) {

		if (n->data == value)
			outData.push_back(n);
		n = n->next;

	}
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {
	Node* n = head;
	while (n != nullptr) {

		if (n->data == data)
			return n;
		n = n->next;

	}

	return nullptr;

}


template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {
	Node* n = head;
	while (n != nullptr) {

		if (n->data == data)
			return n;
		n = n->next;
	}

	return nullptr;

}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {

	if (count == 0 || index > count - 1)
		throw out_of_range("Out of range");

	if (index == 0)
		return head;

	Node* n = head->next;
	unsigned int i;
	for (i = 1; i < index; i++) {

		n = n->next;

	}

	return n;

}


template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {

	if (count == 0 || index > count - 1)
		throw out_of_range("Out of range");

	if (index == 0)
		return head;

	Node* n = head->next;
	unsigned int i;
	for (i = 1; i < index; i++) {

		n = n->next;

	}

	return n;

}


template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
	if (count == 0 || index > count - 1)
		throw out_of_range("Out of range");

	if (index == 0)
		return head->data;

	Node* n = head->next;
	unsigned int i;
	for (i = 1; i < index; i++) {

		n = n->next;

	}

	return n->data;

}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {

	if (count == 0 || index > count - 1)
		throw out_of_range("Out of range");

	if (index == 0)
		return head->data;

	Node* n = head->next;
	unsigned int i;
	for (i = 1; i < index; i++) {

		n = n->next;

	}

	return n->data;

}


