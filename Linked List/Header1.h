Need help debugging this error:

In file included from main.cpp : 4 :
    LinkedList.h : In instantiation of ‘void LinkedList<T>::PrintReverse()[with T = int]’ :
    main.cpp : 35 : 20 : required from here
    LinkedList.h : 135 : 18 : error : ISO C++ forbids variable length array[-Wvla]
    135 | T listdata[this->NodeCount()];
| ^ ~~~~~~~




Header file:
#include <iostream>
#include <string>

using namespace std;
template <class T>
struct Node {

    Node <T>* next;
    T data;

};

template <class T> class LinkedList {

public:
    Node <T>* first;
    Node <T>* last;

    LinkedList <T>() {

        first = NULL;
        last = NULL;

    }

    void AddHead(T data) {

        if (first == NULL) {

            Node<T>* temp = new Node<T>();
            temp->data = data;
            temp->next = NULL;
            first = temp;
            last = temp;

        }
        else {

            Node<T>* temp = new Node<T>;
            temp->data = data;
            temp->next = first;
            first = temp;

        }
    }

    void AddTail(T data) {

        if (last == NULL) {

            Node<T>* temp = new Node<T>();
            temp->data = data;
            temp->next = NULL;
            first = temp;
            last = temp;

        }
        else {

            Node<T>* temp = new Node<T>();
            temp->data = data;
            temp->next = NULL;
            last->next = temp;
            last = temp;

        }
    }

    void AddNodesHead(T data[], int size) {

        for (int i = 0; i < size; i += 1) {

            this->AddHead(data[i]);

        }
    }

    void AddNodesTail(T data[], int size) {

        for (int i = 0; i < size; i += 1) {

            this->AddTail(data[i]);

        }
    }
    int NodeCount() {

        if (first == NULL) {

            return 0;

        }

        Node<T>* temp = first;
        int count = 0;
        while (temp != last) {

            count += 1;
            temp = temp->next;

        }

        return count;

    }

    void PrintForward() {

        if (first == NULL) {

            cout << "List IS empty!!!" << endl;

        }

        Node<T>* temp = first;
        do {

            cout << temp->data << "->";
            temp = temp->next;

        } while (temp != last);

        cout << "NULL" << endl;

    }


    /// ISSUE AREA

    void PrintReverse() {

        if (first == NULL) {

            cout << "List IS empty!!!" << endl;

        }

        Node<T>* temp = first;
        T listdata[this->NodeCount()]; // Needs to not be a VLA
        int i = 0;

        do {

            listdata[i] = temp->data;
            i += 1;
            temp = temp->next;

        } while (temp != last);
        for (int i = this->NodeCount() - 1; i >= 0; i -= 1) {

            cout << listdata[i] << "->";

        }

        cout << "NULL" << endl;

    }

    ~LinkedList() {

        Node<T> *temp;
        while (temp != last) {

            temp = first;
            first = first->next;
            free(temp);

        }

        free(first);
        free(last);

    }

};