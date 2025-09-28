#include "avl_tree.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <functional>
#include <string>
#include <vector>
#include <stdexcept>



// Node Constructor                  

Node::Node(Student student) : data(student), left(nullptr), right(nullptr), height(0) {}


// AVLTree Constructor                
AVLTree::AVLTree() {
    root = nullptr;
    size = 0;
}


// AVLTree Destructor
AVLTree::~AVLTree() {
    // Helper function to recursively delete nodes
    std::function<void(Node*)> deleteNodes = [&](Node* node) {
        if (!node) return;
        deleteNodes(node->left);
        deleteNodes(node->right);
        delete node;
        };
    deleteNodes(root);
}


// Get Size                            
int AVLTree::getSize() {
    return size;
}


// Get Height                          
int AVLTree::getHeight() {
    return getHeight(root);
}


// Helper: Get height of a node        
int AVLTree::getHeight(Node* node) {
    return (node == nullptr) ? -1 : node->height;
}


// Helper: Update height of a node    
void AVLTree::updateHeight(Node* node) {
    if (node) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
}


// Helper: Get balance factor of a node
int AVLTree::getBalance(Node* node) {
    return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
}


// Helper: Right rotation
Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T = x->right;

    x->right = y;
    y->left = T;

    updateHeight(y);
    updateHeight(x);

    return x;
}


// Helper: Left rotation 
Node* AVLTree::rotateLeft(Node* z) {
    Node* y = z->right;
    Node* T = y->left;

    y->left = z;
    z->right = T;

    updateHeight(z);
    updateHeight(y);

    return y;
}


// Helper: Find minimum node in a subtree  
Node* AVLTree::findMin(Node* node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}


// Public Insert (wrapper)            
std::string AVLTree::insert(const std::string& name, int id) {
    // Check for duplicate ID before attempting insert
    if (searchID(root, id) != nullptr) {
        return "unsuccessful";
    }
    root = insert(root, { name, id });
    size++;
    return "successful";
}


// Helper: Insert (recursive)                   
Node* AVLTree::insert(Node* node, Student student) {
    if (!node) return new Node(student);

    if (student.id < node->data.id) {
        node->left = insert(node->left, student);
    }
    else if (student.id > node->data.id) {
        node->right = insert(node->right, student);
    }
    else {
        // Handle duplicates in public wrapper
        return node;
    }

    updateHeight(node);
    int balance = getBalance(node);

    // Rotations to maintain AVL properties
    // Left-Left Case
    if (balance > 1 && student.id < node->left->data.id)
        return rotateRight(node);
    // Right-Right Case
    if (balance < -1 && student.id > node->right->data.id)
        return rotateLeft(node);
    // Left-Right Case
    if (balance > 1 && student.id > node->left->data.id) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // Right-Left Case
    if (balance < -1 && student.id < node->right->data.id) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}


// Public Remove (wrapper)            
std::string AVLTree::remove(int id) {
    bool found = false;
    root = remove(root, id, found);
    if (found) {
        size--;
        return "successful";
    }
    return "unsuccessful";
}


// Helper: Remove (recursive)               
Node* AVLTree::remove(Node* node, int id, bool& found) {
    if (!node) return node;

    if (id < node->data.id) {
        node->left = remove(node->left, id, found);
    }
    else if (id > node->data.id) {
        node->right = remove(node->right, id, found);
    }
    else {
        found = true;
        // Node with one or no child
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }
        // Node with two children: Get inorder successor
        Node* temp = findMin(node->right);
        node->data = temp->data;
        node->right = remove(node->right, temp->data.id, found);
    }

    // Return if tree had only one node
    if (node == nullptr) return node;

    updateHeight(node);
    int balance = getBalance(node);

    // Rebalance the tree
    // Left Left Case
    if (balance > 1 && getBalance(node->left) >= 0)
        return rotateRight(node);
    // Left Right Case
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // Right Right Case
    if (balance < -1 && getBalance(node->right) <= 0)
        return rotateLeft(node);
    // Right Left Case
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}


// Process Command                    
std::string AVLTree::processCommand(const std::string& command) {
    std::istringstream iss(command);
    std::string operation;
    iss >> operation;

    if (operation == "insert") {
        std::string name_str;
        int id;
        // Attempt to extract quoted name and ID
        if (!(iss >> std::quoted(name_str) >> id)) {
            return "unsuccessful";
        }
        // Validate ID length (8 digits)
        if (std::to_string(id).length() != 8) {
            return "unsuccessful";
        }
        return insert(name_str, id);
    }
    else if (operation == "remove") {
        int id;
        // Attempt to extract ID
        if (!(iss >> id)) {
            return "unsuccessful";
        }
        return remove(id);
    }
    // Example for searchID
    else if (operation == "search") {
        int id;
        if (!(iss >> id)) {
            return "unsuccessful";
        }
        return searchID(id);
    }
    // Example for printInorder
    else if (operation == "printInorder") {
        return printInorder();
    }
    // Example for printLevelCount
    else if (operation == "printLevelCount") {
        return std::to_string(printLevelCount());
    }

    // Command not recognized or invalid format
    return "unsuccessful";
}


// Public Search by ID                
std::string AVLTree::searchID(int id) {
    Student* student = searchID(root, id);
    return student ? student->name : "unsuccessful";
}


// Helper: Search by ID (recursive)  
Student* AVLTree::searchID(Node* node, int id) {
    if (!node) return nullptr;
    if (node->data.id == id) return &node->data;
    return (id < node->data.id) ? searchID(node->left, id) : searchID(node->right, id);
}


// Public Print Inorder              
std::string AVLTree::printInorder() {
    std::string result;
    printInorder(root, result);
    // Remove trailing space if any
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    return result;
}


// Helper: Print inorder (recursive)        
void AVLTree::printInorder(Node* node, std::string& result) {
    if (!node) return;

    printInorder(node->left, result);
    result += node->data.name + " ";
    printInorder(node->right, result);
}


// Public Search by Name         
std::string AVLTree::searchName(const std::string& name) {
    std::vector<int> ids;
    searchName(root, name, ids);
    if (ids.empty()) {
        return "unsuccessful";
    }
    std::sort(ids.begin(), ids.end());
    std::ostringstream oss;
    for (size_t i = 0; i < ids.size(); ++i) {
        oss << ids[i];
        if (i < ids.size() - 1) {
            oss << "\n";
        }
    }
    return oss.str();
}


// Helper: Search by Name (recursive) 
void AVLTree::searchName(Node* node, const std::string& name, std::vector<int>& ids) {
    if (!node) return;
    searchName(node->left, name, ids);
    if (node->data.name == name) {
        ids.push_back(node->data.id);
    }
    searchName(node->right, name, ids);
}


// Public Print Preorder            

std::string AVLTree::printPreorder() {
    std::string result;
    printPreorder(root, result);
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    return result;
}


// Helper: Print preorder (recursive) 
void AVLTree::printPreorder(Node* node, std::string& result) {
    if (!node) return;
    result += node->data.name + " ";
    printPreorder(node->left, result);
    printPreorder(node->right, result);
}


// Public Print Postorder          

std::string AVLTree::printPostorder() {
    std::string result;
    printPostorder(root, result);
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    return result;
}


// Helper: Print postorder (recursive)
void AVLTree::printPostorder(Node* node, std::string& result) {
    if (!node) return;
    printPostorder(node->left, result);
    printPostorder(node->right, result);
    result += node->data.name + " ";
}


// Public Print Level Count        
int AVLTree::printLevelCount() {
    return getHeight(root) + 1;
}


// Public Remove Inorder          
std::string AVLTree::removeInorder(int n) {
    if (n <= 0 || n > size) {
        return "unsuccessful";
    }

    int removedId = -1;
    bool found = false;
    root = removeInorder(root, n, removedId, found);
    if (found) {
        size--;
        return "successful";
    }
    return "unsuccessful";
}


// Helper: Remove Inorder (recursive)
Node* AVLTree::removeInorder(Node* node, int& n, int& removedId, bool& found) {
    if (!node) return node;

    // Traverse left subtree
    node->left = removeInorder(node->left, n, removedId, found);
    if (found) return node;

    // Visit current node
    n--;
    if (n == 0) {
        found = true;
        removedId = node->data.id;

        // Standard BST delete logic (same as remove by ID)
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }
        Node* temp = findMin(node->right);
        node->data = temp->data;
        node->right = remove(node->right, temp->data.id, found);
    }
    if (found) return node;

    // Traverse right subtree
    node->right = removeInorder(node->right, n, removedId, found);
    return node;
}
