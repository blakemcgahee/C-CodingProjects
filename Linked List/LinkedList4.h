#include <vector>
#include <stdexcept>
#include <iostream>
using namespace std;

template < class T>
class LinkedList
{
public:
	class Node {
	public:
		Node() {
			this->next = this->prev = nullptr;
		}
		T data;
		Node* next, * prev;
	};

	LinkedList() {
		head = tail = nullptr;
		length = 0;
	}

	~LinkedList() {
		if (head == nullptr) {
			return;
		}
		Node* current = head;
		Node* prev = nullptr;
		while (current != nullptr) {
			prev = current;
			current = current->next;
			delete prev;
		}
		delete current;
	}

	LinkedList(const LinkedList& otherList) {
		head = nullptr;
		tail = nullptr;
		length = 0;
		Node* current = otherList.Head();
		while (current != nullptr) {
			AddTail(current->data);
			current = current->next;
		}
	}

	void AddHead(const T data) {
		if (head == nullptr)
		{
			head = new Node;
			head->data = data;
			tail = head;
		}
		else {
			Node* new_node = new Node();
			new_node->data = data;
			new_node->next = head;
			head->prev = new_node;
			head = head->prev;
		}

		length++;
	}

	void AddTail(const T data) {

		if (tail == nullptr) {
			tail = new Node;
			tail->data = data;
			head = tail;

		}
		else {
			Node* new_node = new Node();
			new_node->data = data;
			new_node->prev = tail;
			tail->next = new_node;
			tail = tail->next;

		}
		length++;
	}

	unsigned int NodeCount() const {
		return length;
	}

	void PrintForward() {
		Node* ptr = head;
		while (ptr != nullptr) {
			cout << ptr->data << endl;
			ptr = ptr->next;
		}
	}
	void PrintReverse() {
		Node* ptr = tail;
		while (ptr != nullptr) {
			cout << ptr->data << endl;
			ptr = ptr->prev;
		}
	}
	void AddNodesHead(const T arr[], const unsigned int count) {
		for (int i = count - 1; i >= 0; i--) {
			AddHead(arr[i]);
		}
	}
	void AddNodesTail(const T arr[], const unsigned int count) {
		for (unsigned int i = 0; i < count; i++) {
			AddTail(arr[i]);
		}
	}
	Node* Find(const T val) {
		Node* front = head, * back = tail;
		Node* ptr = nullptr;
		if (front == nullptr && back == nullptr) {
			return nullptr;
		}
		while (front <= back) {
			if (front->data == val) {
				ptr = front;
				break;
			}
			else if (back->data == val) {
				ptr = back;
				break;
			}
			front = front->next;
			back = back->prev;
		}
		return ptr;
	}
	const Node* Find(const T val) const {
		Node* front = head, * back = tail;
		Node* ptr = nullptr;
		if (front == nullptr && back == nullptr) {
			return nullptr;
		}
		while (front <= back) {
			if (front->data == val) {
				ptr = front;
				break;
			}
			else if (back->data == val) {
				ptr = back;
				break;
			}
			front = front->next;
			back = back->prev;
		}
		return ptr;
	}
	void FindAll(vector<Node*>& nodes, const T search_val) {
		Node* ptr = head;
		while (ptr != nullptr) {
			if (ptr->data == search_val)
				nodes.push_back(ptr);
			ptr = ptr->next;

		}
	}
	T& operator[](const unsigned int index) {
		if (index >= length) throw out_of_range("Out of Range");
		Node* ptr = head;
		for (unsigned int i = 0; i < index; i++) {
			ptr = ptr->next;
		}
		return ptr->data;
	}
	Node* Head() const {
		return head;
	}
	Node* Tail() const {
		return tail;
	}
	Node* GetNode(const unsigned int index) {

		if (index >= length) {
			throw out_of_range("Out of Range");
		}
		Node* ptr = head;
		for (unsigned int i = 0; i < index && ptr != nullptr; i++) {
			ptr = ptr->next;
		}
		return ptr;
	}
	LinkedList& operator=(const LinkedList<T>& otherList) {
		Node* temp = head;
		Node* prev = nullptr;
		while (temp != nullptr) {
			prev = temp;
			temp = temp->next;
			delete prev;
		}
		head = nullptr;
		tail = nullptr;
		length = 0;
		Node* current = otherList.Head();
		while (current != nullptr) {
			AddTail(current->data);
			current = current->next;
		}
		return *this;
	}
	const Node* GetNode(const unsigned int index) const {
		if (index >= length) {
			throw out_of_range("Out of Range");
		}
		Node* ptr = head;
		for (unsigned int i = 0; i < index && ptr != nullptr; i++) {
			ptr = ptr->next;
		}
		return ptr;
	}
	void InsertBefore(Node* node, const T data) {
		if (node == nullptr) {
			AddTail(data);
		}
		else {
			Node* newNode = new Node();
			newNode->data = data;
			Node* prevNode = node->prev;
			if (prevNode != nullptr)
				prevNode->next = newNode;
			newNode->prev = prevNode;
			newNode->next = node;
			node->prev = newNode;
			if (prevNode == nullptr)
				head = newNode;
			length++;
		}
	}

	void InsertAfter(Node* node, const T data) {
		if (node == nullptr) {
			AddTail(data);
		}
		else {
			Node* newNode = new Node();
			newNode->data = data;
			Node* nextNode = node->next;
			newNode->next = nextNode;
			if (nextNode != nullptr)
				nextNode->prev = newNode;
			newNode->prev = node;
			node->next = newNode;
			if (nextNode == nullptr)
				tail = newNode;
			length++;
		}
	}

	void InsertAt(const T data, const unsigned int index) {
		if (index > length) {
			throw out_of_range("Out of Range");
		}
		Node* ptr = head;
		for (unsigned int i = 0; i < index && ptr != nullptr; i++) {
			ptr = ptr->next;
		}
		InsertBefore(ptr, data);
	}

	bool operator==(const LinkedList<T> ll) {
		Node* temp1 = head;
		Node* temp2 = ll.Head();
		while (temp1 != nullptr && temp2 != nullptr) {
			if (temp1->data != temp2->data)
				return false;
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		if (temp1 != nullptr || temp2 != nullptr)
			return false;
		return true;
	}

	void PrintForwardRecursive(Node* node) {
		if (node == nullptr) {
			return;
		}
		cout << node->data << endl;
		PrintForwardRecursive(node->next);
	}

	void PrintReverseRecursive(Node* node) {
		if (node == nullptr) {
			return;
		}
		cout << node->data << endl;
		PrintReverseRecursive(node->prev);
	}
	bool RemoveHead() {
		if (head == nullptr) {
			return false;
		}
		Node* temp = head;
		head = head->next;
		delete temp;
		if (head == nullptr) {
			tail = nullptr;
		}
		else {
			head->prev = nullptr;
		}
		length--;
		return true;
	}

	bool RemoveTail() {
		if (tail == nullptr) {
			return false;
		}
		Node* temp = tail;
		tail = tail->prev;
		delete temp;
		if (tail == nullptr) {
			head = nullptr;
		}
		else {
			tail->next = nullptr;
		}
		length--;
		return true;
	}

	bool RemoveAt(unsigned int index) {
		if (index >= length) {
			return false;
		}
		if (index == 0) {
			return RemoveHead();
		}
		if (index == length - 1) {
			return RemoveTail();
		}
		Node* current = head;
		for (unsigned int i = 0; i < index - 1; i++) {
			current = current->next;
		}
		Node* temp = current->next;
		current->next = temp->next;
		temp->next->prev = current;
		delete temp;
		length--;
		return true;
	}

	unsigned int Remove(const T& value) {
		unsigned int count = 0;
		Node* current = head;
		while (current != nullptr) {
			if (current->data == value) {
				Node* temp = current;
				current = current->next;
				if (temp == head) {
					RemoveHead();
				}
				else if (temp == tail) {
					RemoveTail();
				}
				else {
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
					delete temp;
					length--;
				}
				count++;
			}
			else {
				current = current->next;
			}
		}
		return count;
	}

	void Clear() {
		while (head != nullptr) {
			RemoveHead();
		}
	}


private:
	unsigned int length;
	Node* head, * tail;
};