/*
Project Author: Blake McGahee
UFID: 82924917
UF – COP3530 Summer’25
Started: 05/24/2025
Last Modified: 06/08/2025

Change Log:
Date:           Change:
05/24/2025      Implemented basic Node constructor, AVLTree constructor/destructor (with recursive cleanup), and initial helper functions like getHeight, updateHeight, getBalance. This laid the groundwork for the AVL tree.
05/26/2025      Developed the fundamental AVL tree operations: insert (both wrapper and recursive helper) and remove (both wrapper and recursive helper). This included the complex AVL rotation logic (rotateLeft, rotateRight) to maintain balance during insertions and deletions.
06/01/2025      Started implementing processCommand to parse "insert", "remove" (by ID), and "search" (by ID), routing them to the correct AVL tree methods. Also added searchID and printInorder functionality.
06/05/2025      Expanded processCommand to include searchName, printPreorder, printPostorder, printLevelCount, and removeInorder. Crucially, integrated input validation for IDs (8 digits) and Names (alphabets/spaces) directly into processCommand.
06/07/2025      Corrected searchName to use a pre-order traversal as required (removing std::sort). Added comprehensive rebalancing logic (height updates and rotations) to the removeInorder recursive helper, ensuring the tree remains balanced after inorder deletions.
06/08/2025      Adjusted traversal helper functions (printInorder, printPreorder, printPostorder) to append comma conditionally, preventing a trailing comma in the final output string.
*/

#include "avl_tree.h"
#include <iostream>     // Standard library for using in/out objects
#include <sstream>      // For std::istringstream and std::ostringstream
#include <algorithm>    // For std::max, std::all_of
#include <iomanip>      // For std::quoted
#include <functional>   // For std::function in destructor
#include <vector>       // Standard library for using vector objects.
#include <string>       // Standard library for using string objects.
#include <stdexcept>    // For std::logic_error
#include <cctype>       // For std::isalpha, std::isspace
#include <regex>        // For std::regex (for isValidName and ID validation)

// Helper function to validate names (only alphabets and spaces)
// This function checks if a given string contains only alphabetic characters (a-z, A-Z) and spaces.
// It iterates through each character of the string. If any character is neither an alphabet nor a space,
// the function returns false, indicating an invalid name. Otherwise, it returns true.
bool isValidName(const std::string& name) {
    for (char c : name) {
        if (!std::isalpha(c) && !std::isspace(c)) {
            return false; // Found a character that is not an alphabet or space
        }
    }
    return true; // All characters are valid
}

// Node Constructor
Node::Node(Student student) : data(student), left(nullptr), right(nullptr), height(0) {}

// AVLTree Constructor
AVLTree::AVLTree() {
    root = nullptr;
    size = 0;
}

// AVLTree Destructor
// This destructor uses a lambda function (std::function) to recursively
// delete all nodes in the tree, preventing memory leaks.
AVLTree::~AVLTree() {
    std::function<void(Node*)> deleteNodes = [&](Node* node) {
        if (!node) return; // Base case: if node is null, do nothing
        deleteNodes(node->left);    // Recursively delete left subtree
        deleteNodes(node->right);   // Recursively delete right subtree
        delete node;                // Delete the current node
        };
    deleteNodes(root); // Start deletion from the root
}

// Get Size of the AVL tree
int AVLTree::getSize() {
    return size;
}

// Get Height of the AVL tree (public wrapper)
// Returns the height of the root node.
int AVLTree::getHeight() {
    return getHeight(root);
}

// Helper: Get height of a specific node
// Returns the height of the given node. If the node is null, its height is considered -1.
int AVLTree::getHeight(Node* node) {
    return (node == nullptr) ? -1 : node->height;
}

// Helper: Update height of a node
// Recalculates and sets the height of the given node based on the heights of its children.
// The height of a node is 1 plus the maximum height of its left or right child.
void AVLTree::updateHeight(Node* node) {
    if (node) { // Only update if the node is not null
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
}

// Helper: Get balance factor of a node
// Calculates the balance factor of a node, which is the difference between the
// height of its left child and the height of its right child.
int AVLTree::getBalance(Node* node) {
    return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
}

// Helper: Right rotation
// Performs a right rotation around node 'y'. 'x' becomes the new root of the subtree.
// This is used to balance a left-heavy subtree.
Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T = x->right; // 'T' is the right child of x, which becomes left child of y

    // Perform rotation
    x->right = y;
    y->left = T;

    // Update heights after rotation, starting from the lower node (y), then the new root (x)
    updateHeight(y);
    updateHeight(x);

    return x; // Return the new root of the rotated subtree
}

// Helper: Left rotation
// Performs a left rotation around node 'z'. 'y' becomes the new root of the subtree.
// This is used to balance a right-heavy subtree.
Node* AVLTree::rotateLeft(Node* z) {
    Node* y = z->right;
    Node* T = y->left; // 'T' is the left child of y, which becomes right child of z

    // Perform rotation
    y->left = z;
    z->right = T;

    // Update heights after rotation, starting from the lower node (z), then the new root (y)
    updateHeight(z);
    updateHeight(y);

    return y; // Return the new root of the rotated subtree
}

// Helper: Find minimum node in a subtree
// Traverses the left subtree to find the node with the smallest key.
Node* AVLTree::findMin(Node* node) {
    while (node->left) { // Keep going left until there's no left child
        node = node->left;
    }
    return node; // Return the node with the minimum key
}

// Public Insert (wrapper function)
// Inserts a new student into the AVL tree. Handles duplicate IDs and calls the recursive helper.
std::string AVLTree::insert(const std::string& name, int id) {
    // First, check if an ID already exists in the tree using the search helper.
    if (searchID(root, id) != nullptr) {
        return "unsuccessful"; // ID must be unique
    }
    // Call the recursive insert helper to add the student and rebalance the tree.
    root = insert(root, { name, id });
    size++; // Increment the tree size
    return "successful";
}

// Helper: Insert (recursive function)
// Recursively inserts a new student into the tree and performs AVL rotations as needed
// to maintain balance.
Node* AVLTree::insert(Node* node, Student student) {
    // Base case: If the current node is null, create a new node here.
    if (!node) return new Node(student);

    // Traverse the tree to find the correct insertion spot based on ID.
    if (student.id < node->data.id) {
        node->left = insert(node->left, student);
    }
    else if (student.id > node->data.id) {
        node->right = insert(node->right, student);
    }
    else {
        // This case should ideally be handled by the public wrapper (duplicate check).
        // If reached, it means attempting to insert a duplicate ID, so just return the node.
        return node;
    }

    // Update height of the current node after (possible) insertion in its subtree.
    updateHeight(node);
    // Get the balance factor of the current node.
    int balance = getBalance(node);

    // Perform rotations if the tree becomes unbalanced (balance factor > 1 or < -1).
    // Left-Left Case: Node is left-heavy, and new node inserted in left-left subtree.
    if (balance > 1 && student.id < node->left->data.id)
        return rotateRight(node);
    // Right-Right Case: Node is right-heavy, and new node inserted in right-right subtree.
    if (balance < -1 && student.id > node->right->data.id)
        return rotateLeft(node);
    // Left-Right Case: Node is left-heavy, but new node inserted in left-right subtree.
    if (balance > 1 && student.id > node->left->data.id) {
        node->left = rotateLeft(node->left); // Perform Left rotation on left child
        return rotateRight(node);           // Then Right rotation on current node
    }
    // Right-Left Case: Node is right-heavy, but new node inserted in right-left subtree.
    if (balance < -1 && student.id < node->right->data.id) {
        node->right = rotateRight(node->right); // Perform Right rotation on right child
        return rotateLeft(node);            // Then Left rotation on current node
    }

    return node; // Return the (potentially new) root of this subtree
}

// Public Remove by ID (wrapper function)
// Removes a student with the specified ID from the AVL tree.
std::string AVLTree::remove(int id) {
    bool found = false; // Flag to track if the ID was found and removed
    root = remove(root, id, found); // Call the recursive remove helper
    if (found) {
        size--; // Decrement tree size if deletion was successful
        return "successful";
    }
    return "unsuccessful"; // ID not found
}

// Helper: Remove by ID (recursive function)
// Recursively removes a node with the given ID and rebalances the tree.
Node* AVLTree::remove(Node* node, int id, bool& found) {
    // Base case: If the node is null, the ID is not in this subtree.
    if (!node) return node;

    // Traverse the tree to find the node to be removed.
    if (id < node->data.id) {
        node->left = remove(node->left, id, found);
    }
    else if (id > node->data.id) {
        node->right = remove(node->right, id, found);
    }
    else { // Node found (id == node->data.id)
        found = true; // Mark as found

        // Case 1 & 2: Node with zero or one child
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right; // Get the non-null child (or nullptr)
            delete node; // Delete the current node
            return temp; // Return the child (which becomes the new root of this subtree)
        }
        // Case 3: Node with two children
        else {
            // Find the inorder successor (smallest node in the right subtree)
            Node* temp = findMin(node->right);
            // Copy the successor's data to the current node
            node->data = temp->data;
            // Recursively remove the successor from the right subtree
            bool successor_found_dummy = false; // A dummy flag for the recursive call to remove successor
            node->right = remove(node->right, temp->data.id, successor_found_dummy);
        }
    }

    // If the node became null after deletion (e.g., it was a leaf or had one child), return early.
    if (node == nullptr) return node;

    // Update height and rebalance on the way up the recursion path.
    updateHeight(node);
    int balance = getBalance(node);

    // Rebalance the tree if necessary (standard AVL rotation logic)
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

    return node; // Return the (potentially new) root of this subtree
}


// Public Search by ID (wrapper function)
// Searches for a student by their GatorID and returns their name if found, "unsuccessful" otherwise.
std::string AVLTree::searchID(int id) {
    Student* student = searchID(root, id); // Call the recursive search helper
    return student ? student->name : "unsuccessful"; // Return name if found, else "unsuccessful"
}

// Helper: Search by ID (recursive function)
// Recursively searches for a node with the given ID.
Student* AVLTree::searchID(Node* node, int id) {
    if (!node) return nullptr; // Base case: If node is null, ID not found.
    if (node->data.id == id) return &node->data; // Base case: ID found, return student data.
    // Traverse based on ID comparison.
    return (id < node->data.id) ? searchID(node->left, id) : searchID(node->right, id);
}

// Public Print Inorder traversal (wrapper function)
// Returns a comma-separated string of student names in inorder traversal order.
std::string AVLTree::printInorder() {
    std::string result;
    // Call the recursive helper to populate the result string.
    printInorder(root, result);
    // No need to remove trailing comma here if helper adds conditionally
    return result;
}

// Helper: Print inorder (recursive function)
// Recursively traverses the tree in inorder (Left-Root-Right) and appends names to the result string.
void AVLTree::printInorder(Node* node, std::string& result) {
    if (!node) return; // Base case: null node

    printInorder(node->left, result); // Traverse left subtree
    // Only add ", " if it's not the very first name being added
    if (!result.empty()) {
        result += ", ";
    }
    result += node->data.name;     // Add current node's name
    printInorder(node->right, result); // Traverse right subtree
}

// Public Search by Name (wrapper function)
// Searches for students with the specified name and returns their GatorIDs.
// Prints each ID on a new line, in the same relative order as a pre-order traversal.
std::string AVLTree::searchName(const std::string& name) {
    std::vector<int> ids;
    // Call the recursive helper to find all matching IDs in pre-order.
    searchName(root, name, ids);
    if (ids.empty()) {
        return "unsuccessful"; // No student found with that name
    }
    // Construct the output string with IDs on new lines.
    std::ostringstream oss;
    for (size_t i = 0; i < ids.size(); ++i) {
        oss << ids[i];
        if (i < ids.size() - 1) {
            oss << "\n"; // Add newline for all but the last ID
        }
    }
    return oss.str();
}

// Helper: Search by Name (recursive function - Preorder Traversal)
// Recursively traverses the tree in preorder (Root-Left-Right) and collects IDs
// of students whose names match the given name.
void AVLTree::searchName(Node* node, const std::string& name, std::vector<int>& ids) {
    if (!node) return; // Base case: null node

    // Visit current node first (Preorder logic)
    if (node->data.name == name) {
        ids.push_back(node->data.id); // Add ID if name matches
    }

    // Then traverse left subtree
    searchName(node->left, name, ids);
    // Then traverse right subtree
    searchName(node->right, name, ids);
}

// Public Print Preorder traversal (wrapper function)
// Returns a comma-separated string of student names in preorder traversal order.
std::string AVLTree::printPreorder() {
    std::string result;
    printPreorder(root, result); // Call the recursive helper
    // No need to remove trailing comma here if helper adds conditionally
    return result;
}

// Helper: Print preorder (recursive function)
// Recursively traverses the tree in preorder (Root-Left-Right) and appends names to the result string.
void AVLTree::printPreorder(Node* node, std::string& result) {
    if (!node) return; // Base case: null node
    // Only add ", " if the result string is not empty
    if (!result.empty()) {
        result += ", ";
    }
    result += node->data.name; // Add current node's name
    printPreorder(node->left, result); // Traverse left subtree
    printPreorder(node->right, result); // Traverse right subtree
}

// Public Print Postorder traversal (wrapper function)
// Returns a comma-separated string of student names in postorder traversal order.
std::string AVLTree::printPostorder() {
    std::string result;
    printPostorder(root, result); // Call the recursive helper
    // No need to remove trailing comma here if helper adds conditionally
    return result;
}

// Helper: Print postorder (recursive function)
// Recursively traverses the tree in postorder (Left-Right-Root) and appends names to the result string.
void AVLTree::printPostorder(Node* node, std::string& result) {
    if (!node) return; // Base case: null node
    printPostorder(node->left, result); // Traverse left subtree
    printPostorder(node->right, result); // Traverse right subtree
    // Only add ", " if the result string is not empty
    if (!result.empty()) {
        result += ", ";
    }
    result += node->data.name; // Add current node's name
}

// Public Print Level Count
// Returns the number of levels in the tree. An empty tree has 0 levels.
int AVLTree::printLevelCount() {
    // Height is -1 for a null tree, so add 1 to get level count.
    return getHeight(root) + 1;
}

// Public Remove Inorder (wrapper function)
// Removes the Nth (0-indexed) GatorID from the inorder traversal of the tree.
std::string AVLTree::removeInorder(int n) {
    // Validate 'n' to be within the valid range [0, size-1].
    if (n < 0 || n >= size) {
        return "unsuccessful"; // N is out of bounds
    }

    int removedId = -1; // Placeholder for the ID of the removed student.
    bool found = false; // Flag to track if the Nth node was found and removed.

    // Call the recursive helper to find and remove the Nth node.
    // 'n' is passed by reference so it decrements correctly across recursive calls
    // until it reaches the target node.
    root = removeInorder(root, n, removedId, found);

    if (found) {
        size--; // Decrement tree size only if a node was successfully removed.
        return "successful";
    }
    return "unsuccessful"; // Should theoretically not be reached if n was in bounds.
}

// Helper: Remove Inorder (recursive function)
// Recursively finds and removes the Nth node in inorder traversal, then rebalances the tree.
Node* AVLTree::removeInorder(Node* node, int& n, int& removedId, bool& found) {
    if (!node) return node; // Base case: If node is null, return it.

    // First, try to find and remove the Nth node in the left subtree.
    node->left = removeInorder(node->left, n, removedId, found);

    // If the node was found and removed in the left subtree,
    // we need to rebalance this 'node' and its ancestors on the way up the recursion stack.
    if (found) {
        // After potential change in left subtree, update current node's height.
        updateHeight(node);
        int balance = getBalance(node);

        // Perform AVL rebalancing if necessary (same logic as insert/remove by ID).
        // LL Case: Node is left-heavy, and new node inserted in left-left subtree.
        if (balance > 1) {
            if (getBalance(node->left) >= 0) return rotateRight(node);
            // LR Case: Node is left-heavy, but new node inserted in left-right subtree.
            else {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }
        // RR Case: Node is right-heavy, and new node inserted in right-right subtree.
        if (balance < -1) {
            if (getBalance(node->right) <= 0) return rotateLeft(node);
            // RL Case: Node is right-heavy, but new node inserted in right-left subtree.
            else {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }
        return node; // No rotation needed, or balance restored.
    }

    // If not found in the left subtree, check the current node.
    // Decrement 'n' as we visit this node in inorder sequence.
    n--;
    // If 'n' becomes -1, this is the Nth node (since 'n' started as 0-indexed and was decremented).
    if (n == -1) {
        found = true; // Mark that the node has been found.
        removedId = node->data.id; // Store the ID of the removed student.

        // Perform actual deletion based on standard BST deletion logic.
        // Case 1 & 2: Node with zero or one child.
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right; // Get the non-null child (or nullptr if leaf).
            delete node; // Delete the current node.
            return temp; // Return the child (which becomes the new link in the tree).
        }
        // Case 3: Node with two children.
        else {
            // Find the inorder successor (smallest node in the right subtree).
            Node* temp = findMin(node->right);
            // Copy the successor's data to the current node (logically "deleting" current node by overwriting).
            node->data = temp->data;
            // Recursively remove the successor from the right subtree.
            // The recursive 'remove' by ID helper already handles its own rebalancing.
            bool successor_found_dummy = false; // Dummy flag as 'found' is already true.
            node->right = remove(node->right, temp->data.id, successor_found_dummy);
        }
    }

    // If the node was not found in the left subtree and was not the current node,
    // try to find and remove it in the right subtree.
    // Only proceed if the node hasn't been found yet (`!found`).
    if (!found) {
        node->right = removeInorder(node->right, n, removedId, found);
    }

    // After recursive calls (or if this node was deleted and rebuilt with successor),
    // rebalance the current node if it still exists.
    if (node == nullptr) return node; // If node was just deleted, nothing to rebalance here.

    // Update current node's height.
    updateHeight(node);
    int balance = getBalance(node);

    // Perform AVL rebalancing if necessary (same logic as insert/remove by ID).
    // LL Case
    if (balance > 1) {
        if (getBalance(node->left) >= 0) return rotateRight(node);
        // LR Case
        else {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }
    // RR Case
    if (balance < -1) {
        if (getBalance(node->right) <= 0) return rotateLeft(node);
        // RL Case
        else {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }
    return node; // Return the (potentially new) root of this subtree.
}


// Public Process Command (main parser for commands)
// Parses the input command string and calls the appropriate AVLTree method.
std::string AVLTree::processCommand(const std::string& command) {
    std::istringstream iss(command); // Use string stream to parse the command line input.
    std::string operation;
    iss >> operation; // Extract the command operation (e.g., "insert", "remove").

    if (operation == "insert") {
        std::string name_str;
        int id;
        // Attempt to extract the quoted name and integer ID.
        // std::quoted handles names with spaces enclosed in double quotes.
        if (!(iss >> std::quoted(name_str) >> id)) {
            return "unsuccessful"; // Invalid format (e.g., missing quotes, ID not an integer).
        }
        // Validate ID length: must be strictly 8 digits.
        if (std::to_string(id).length() != 8) {
            return "unsuccessful";
        }
        // Validate Name: must contain only alphabets and spaces.
        if (!isValidName(name_str)) {
            return "unsuccessful";
        }
        // Call the insert method if all validations pass.
        return insert(name_str, id);
    }
    else if (operation == "remove") {
        int id;
        // Attempt to extract the integer ID.
        if (!(iss >> id)) {
            return "unsuccessful"; // Invalid ID format (e.g., not an integer).
        }
        // Validate ID length for remove command.
        if (std::to_string(id).length() != 8) {
            return "unsuccessful";
        }
        // Call the remove by ID method.
        return remove(id);
    }
    else if (operation == "search") {
        std::string param_str;
        iss >> std::ws; // Consume any leading whitespace before checking the next character.
        // Check if the next character is a double quote (indicating a name search).
        if (iss.peek() == '"') {
            iss >> std::quoted(param_str); // Extract the quoted name.
            // No explicit validation for name in search, the searchName function will
            // simply not find matches if the name format is odd.
            return searchName(param_str); // Call search by Name method.
        }
        else { // Otherwise, assume it's an ID search.
            int id;
            if (!(iss >> id)) {
                return "unsuccessful"; // Invalid format if not a quoted string or integer.
            }
            // Validate ID length for search by ID command.
            if (std::to_string(id).length() != 8) {
                return "unsuccessful";
            }
            return searchID(id); // Call search by ID method.
        }
    }
    else if (operation == "printInorder") {
        return printInorder();
    }
    else if (operation == "printPreorder") { // Handle printPreorder command.
        return printPreorder();
    }
    else if (operation == "printPostorder") { // Handle printPostorder command.
        return printPostorder();
    }
    else if (operation == "printLevelCount") {
        // Convert the integer result from printLevelCount() to a string.
        return std::to_string(printLevelCount());
    }
    else if (operation == "removeInorder") { // Handle removeInorder command.
        int n;
        // Attempt to extract the integer 'n' for removeInorder.
        if (!(iss >> n)) {
            return "unsuccessful"; // Invalid format for 'n'.
        }
        return removeInorder(n); // Call removeInorder method.
    }
    // If the extracted operation command itself is not recognized.
    return "unsuccessful";
}
