/*
Project Author: Blake McGahee
UFID: 82924917
UF – COP3530 Summer’25
Started: 05/24/2025
Last Modified: 06/08/2025

Change Log:
Date:           Change:
05/24/2025      Initial Class & Node Structure: Implemented basic Node constructor, AVLTree constructor/destructor (with recursive cleanup), and initial helper functions like getHeight, updateHeight, getBalance.
05/27/2025      Core AVL Operations: Developed fundamental AVL tree operations: insert (wrapper and recursive) and remove (wrapper and recursive), including AVL rotation logic (rotateLeft, rotateRight) for balancing.
06/01/2025      Basic Command Processing & Search: Started implementing 'processCommand' to parse "insert", "remove" (by ID), and "search" (by ID), routing to AVL tree methods. Also added initial searchID and printInorder functionality.
06/05/2025      Full Command Implementation & Validation: Expanded 'processCommand' to handle all remaining required commands (searchName, printPreorder, printPostorder, printLevelCount, removeInorder). Integrated comprehensive input validation for IDs (8 digits) and Names (alphabets/spaces).
06/07/2025      Traversal & Deletion Logic Refinements: Implemented correct pre-order traversal for searchName. Also added full rebalancing logic (height updates and rotations) within the recursive removeInorder helper to ensure tree balance after those specific deletions.
*/

#ifndef AVL_TREE_H // This is a 'header guard' to prevent the file from being included multiple times.
#define AVL_TREE_H // Defines a unique identifier for this header file.

#include <string>    // Standard library for using string objects.
#include <vector>    // Standard library for using dynamic arrays (vectors).
#include <functional> // Needed for std::function, often used for things like lambda functions in destructors.

// This struct represents a single student, holding their name and GatorID.
struct Student {
    std::string name; // The student's name.
    int id;           // The student's unique GatorID number.
};

// This class represents a single node within our AVL tree.
// Each node holds student data and pointers to its left and right children.
class Node {
public:
    Student data;  // The student data stored in this node.
    Node* left;    // Pointer to the left child node.
    Node* right;   // Pointer to the right child node.
    int height;    // The height of this node in the tree (important for AVL balancing).

    // Constructor for a Node, taking a Student object.
    Node(Student student);
};

// This class represents the entire AVL tree data structure.
// It manages the collection of nodes and provides methods for tree operations.
class AVLTree {
private:
    Node* root; // Pointer to the root node of the AVL tree.
    int size;   // Keeps track of the total number of nodes (students) in the tree.

    // --- Helper Functions (Private Methods) ---
    // These functions perform the internal work of the AVL tree and are not directly called by 'main'.

    // Recursive helper for inserting a new student into the tree, returns the updated subtree root.
    Node* insert(Node* node, Student student);
    // Recursive helper for removing a student by ID, returns the updated subtree root.
    // 'found' is a reference to a boolean that will be set if the ID is successfully found and removed.
    Node* remove(Node* node, int id, bool& found);
    // Performs a left rotation operation to rebalance a subtree.
    Node* rotateLeft(Node* z);
    // Performs a right rotation operation to rebalance a subtree.
    Node* rotateRight(Node* y);
    // Gets the height of a specific node.
    int getHeight(Node* n);
    // Updates the height of a specific node after operations.
    void updateHeight(Node* n);
    // Calculates the balance factor of a node (height of left - height of right).
    int getBalance(Node* n);
    // Finds the node with the minimum ID in a given subtree (used for deletion with two children).
    Node* findMin(Node* node);

    // Helper for searching for a student by ID (recursive).
    Student* searchID(Node* node, int id);
    // Helper for searching for students by name (recursive, performs pre-order traversal).
    void searchName(Node* node, const std::string& name, std::vector<int>& ids);
    // Helper for generating the inorder traversal string (recursive).
    void printInorder(Node* node, std::string& result);
    // Helper for generating the preorder traversal string (recursive).
    void printPreorder(Node* node, std::string& result);
    // Helper for generating the postorder traversal string (recursive).
    void printPostorder(Node* node, std::string& result);
    // Helper for calculating the level count of a specific subtree.
    int printLevelCount(Node* node); // Note: This helper might not be needed if public printLevelCount just uses getHeight(root)+1
    // Recursive helper for removing the Nth node in inorder traversal.
    // 'n' is passed by reference to count down to the target node.
    Node* removeInorder(Node* node, int& n, int& removedId, bool& found);

public:
    // Constructor for the AVLTree.
    AVLTree();
    // Destructor for the AVLTree, responsible for cleaning up all allocated memory.
    ~AVLTree();

    // --- Public Interface Functions ---
    // These functions are what the 'main' program will call to interact with the AVL tree.

    // Processes a full command string (like "insert "Name" 12345678").
    std::string processCommand(const std::string& command);

    // Inserts a new student with the given name and ID into the tree.
    std::string insert(const std::string& name, int id);
    // Removes a student with the given ID from the tree.
    std::string remove(int id);
    // Searches for a student by ID and returns their name.
    std::string searchID(int id);
    // Searches for students by name and returns their IDs (in pre-order).
    std::string searchName(const std::string& name);
    // Returns a string of all student names in inorder traversal.
    std::string printInorder();
    // Returns a string of all student names in preorder traversal.
    std::string printPreorder();
    // Returns a string of all student names in postorder traversal.
    std::string printPostorder();
    // Returns the number of levels (height + 1) in the tree.
    int printLevelCount();
    // Removes the Nth student encountered during an inorder traversal.
    std::string removeInorder(int n);

    // Returns the current number of students in the tree.
    int getSize();
    // Returns the height of the tree.
    int getHeight();
};

#endif // AVL_TREE_H
