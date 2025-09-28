#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <string>
#include <vector>
#include <functional> // Added for std::function in destructor (though not strictly needed in header for this specific use)

struct Student {
    std::string name;
    int id;
};

class Node {
public:
    Student data;
    Node* left;
    Node* right;
    int height;

    Node(Student student);
};

class AVLTree {
private:
    Node* root;
    int size; // Added size as a private member, initialized in constructor

    // Helper functions for AVL tree operations (rotations, height updates, etc.)
    Node* insert(Node* node, Student student);
    // Corrected remove helper signature to match implementation
    Node* remove(Node* node, int id, bool& found);
    Node* rotateLeft(Node* z);
    Node* rotateRight(Node* y);
    int getHeight(Node* n);
    void updateHeight(Node* n);
    int getBalance(Node* n);
    Node* findMin(Node* node);

    // Helper functions for search and traversal
    Student* searchID(Node* node, int id);
    void searchName(Node* node, const std::string& name, std::vector<int>& ids);
    void printInorder(Node* node, std::string& result);
    void printPreorder(Node* node, std::string& result);
    void printPostorder(Node* node, std::string& result);
    int printLevelCount(Node* node);
    Node* removeInorder(Node* node, int& n, int& removedId, bool& found); // This helper was declared but not used in tests

public:
    AVLTree();
    ~AVLTree();

    // Public interface functions
    std::string processCommand(const std::string& command);

    // Or individual functions for each command:
    std::string insert(const std::string& name, int id);
    std::string remove(int id);
    std::string searchID(int id);
    std::string searchName(const std::string& name);
    std::string printInorder();
    std::string printPreorder();
    std::string printPostorder();
    int printLevelCount();
    std::string removeInorder(int n);

    int getSize();
    int getHeight();
};

#endif // AVL_TREE_H
