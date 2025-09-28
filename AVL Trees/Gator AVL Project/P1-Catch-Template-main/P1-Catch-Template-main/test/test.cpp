/*
Project Author: Blake McGahee
UFID: 82924917
UF – COP3530 Summer’25
Started: 05/24/2025
Last Modified: 06/08/2025

Change Log:
Date:           Change:
05/24/2025      Initial Test Setup: Created the test.cpp file and integrated Catch2, setting up the basic framework for writing test cases.
05/27/2025      Command Parsing Tests: Developed a test case (Command Parsing - Invalid Inputs) to verify that processCommand correctly identifies and rejects various invalid command formats and data.
05/28/2025      Rotation and Basic Deletion Tests: Added detailed test cases for all four AVL rotation types (LL, RR, LR, RL) during insertion, and for the three fundamental deletion cases (no children, one child, two children).
05/29/2025      Large Scale Operations Test: Implemented a robust test case (Large Scale Operations - Insert and Remove) involving 100 insertions and 10 random removals, verifying tree size and integrity.
06/01/2025      Randomness Robustness Fix: Modified the Large Scale Operations test to prevent occasional failures by dynamically finding an ID known to not be randomly removed for its spot-check verification.
*/

/*
#include <catch2/catch_test_macros.hpp> // Include the Catch2 testing framework.
#include "avl_tree.h"   // Include our custom AVL tree header, so we can test its functions.
#include <iostream>     // For basic input/output, though not heavily used in tests.
#include <random>       // For generating random numbers (useful for large-scale tests).
#include <algorithm>    // For algorithms like std::shuffle (to pick random IDs).
#include <vector>       // For using dynamic arrays (vectors) to store IDs.
#include <string>       // For using string objects.

using namespace std; // Using the standard namespace to simplify code.

// Student Name: Blake McGahee
// Student UFID: 82924917

// This test suite verifies how well our program handles invalid or incorrectly formatted commands.
// It makes sure that our command parser returns "unsuccessful" for bad inputs.
TEST_CASE("Command Parsing - Invalid Inputs", "[parsing]") {
    AVLTree tree; // Create a new AVLTree instance for each test.

    // Test Case 1.1: 'insert' command where the student's name is not enclosed in double quotes.
    REQUIRE(tree.processCommand("insert A11y 45679999") == "unsuccessful");
    // Test Case 1.2: 'insert' command where the GatorID is not exactly 8 digits long.
    REQUIRE(tree.processCommand("insert \"Valid Name\" 1234567") == "unsuccessful");
    // Test Case 1.3: 'insert' command where the GatorID contains non-numeric characters.
    REQUIRE(tree.processCommand("insert \"Name\" ABCDEFGH") == "unsuccessful");
    // Test Case 1.4: 'remove' command where the ID parameter is not a valid number.
    REQUIRE(tree.processCommand("remove NotAnID") == "unsuccessful");
    // Test Case 1.5: An entirely unknown or misspelled command.
    REQUIRE(tree.processCommand("gibberish command") == "unsuccessful");
}

// This test suite checks specific, sometimes tricky, situations (edge cases) for various AVL tree functions.
// It ensures our methods behave correctly even at the boundaries or unusual conditions.
TEST_CASE("Edge Cases - Specific Scenarios", "[edge-cases]") {
    AVLTree tree; // Start with a fresh tree for this test section.

    // Edge Case 2.1: Attempting to remove a specific ID when the tree is completely empty.
    REQUIRE(tree.remove(11111111) == "unsuccessful");
    REQUIRE(tree.getSize() == 0); // Confirm the tree size remains zero.

    // Edge Case 2.2: Attempting to search for an ID that doesn't exist in a tree that has some nodes.
    REQUIRE(tree.insert("Alice", 10000000) == "successful"); // Insert one student to make the tree non-empty.
    REQUIRE(tree.searchID(99999999) == "unsuccessful"); // This ID shouldn't be found.
    REQUIRE(tree.getSize() == 1); // Confirm the tree size is still one.

    // Edge Case 2.3: Attempting to insert a new student with an ID that already exists in the tree.
    REQUIRE(tree.insert("Bob", 10000000) == "unsuccessful"); // Trying to insert Alice's ID again should fail.
    REQUIRE(tree.getSize() == 1); // The tree size should not change.

    // Edge Case 2.4 (Bonus Check): Attempting to remove a node by its inorder position from an empty tree.
    AVLTree emptyTree; // Create another new, empty tree just for this test.
    REQUIRE(emptyTree.removeInorder(0) == "unsuccessful"); // Removing the 0th item from an empty tree.
    REQUIRE(emptyTree.getSize() == 0); // Confirm the tree size is still zero.
}

// This test suite carefully checks if the AVL tree maintains its balance using all four standard rotation types
// during the 'insert' operation.
TEST_CASE("Insert - All Four Rotation Cases", "[insertion][rotation]") {
    // Test Case 3.1: Left-Left (LL) Rotation scenario.
    // Inserting nodes in this order forces a Left-Left imbalance, which should be fixed by a single right rotation.
    AVLTree tree_ll;
    tree_ll.insert("C_Name", 30000000);
    tree_ll.insert("B_Name", 20000000);
    tree_ll.insert("A_Name", 10000000); // This insertion triggers the LL rotation.
    REQUIRE(tree_ll.getHeight() == 1); // A 3-node balanced tree has a height of 1 (levels 0 and 1).
    REQUIRE(tree_ll.printInorder() == "A_Name,B_Name,C_Name"); // Verify the nodes are now in correct inorder sequence.

    // Test Case 3.2: Right-Right (RR) Rotation scenario.
    // Inserting nodes in this order forces a Right-Right imbalance, fixed by a single left rotation.
    AVLTree tree_rr;
    tree_rr.insert("A_Name", 10000000);
    tree_rr.insert("B_Name", 20000000);
    tree_rr.insert("C_Name", 30000000); // This insertion triggers the RR rotation.
    REQUIRE(tree_rr.getHeight() == 1); // Expected height after balancing.
    REQUIRE(tree_rr.printInorder() == "A_Name,B_Name,C_Name"); // Verify inorder.

    // Test Case 3.3: Left-Right (LR) Rotation scenario.
    // Inserting nodes in this order forces a Left-Right imbalance, fixed by two rotations (left then right).
    AVLTree tree_lr;
    tree_lr.insert("A_Name", 10000000);
    tree_lr.insert("C_Name", 30000000);
    tree_lr.insert("B_Name", 20000000); // This insertion triggers the LR rotation.
    REQUIRE(tree_lr.getHeight() == 1); // Expected height after balancing.
    REQUIRE(tree_lr.printInorder() == "A_Name,B_Name,C_Name"); // Verify inorder.

    // Test Case 3.4: Right-Left (RL) Rotation scenario.
    // Inserting nodes in this order forces a Right-Left imbalance, fixed by two rotations (right then left).
    AVLTree tree_rl;
    tree_rl.insert("C_Name", 30000000);
    tree_rl.insert("A_Name", 10000000);
    tree_rl.insert("B_Name", 20000000); // This insertion triggers the RL rotation.
    REQUIRE(tree_rl.getHeight() == 1); // Expected height after balancing.
    REQUIRE(tree_rl.printInorder() == "A_Name,B_Name,C_Name"); // Verify inorder.
}

// This test suite checks if the AVL tree's 'remove' function correctly handles
// the three fundamental scenarios when deleting a node:
// 1. Deleting a node with no children (a leaf).
// 2. Deleting a node with only one child.
// 3. Deleting a node with two children (which requires finding an inorder successor).
TEST_CASE("Remove - Deletion Cases", "[deletion]") {
    AVLTree tree;
    // First, build a specific tree structure with enough nodes to reliably test all deletion cases.
    // The IDs are chosen to help create a predictable structure for these tests.
    // Conceptual tree structure after these insertions (actual balance may vary slightly due to AVL properties):
    //        50
    //       /  \
    //      25   75
    //     / \   / \
    //    10 30 60 80
    //       /
    //      28
    REQUIRE(tree.insert("Node50", 50000000) == "successful");
    REQUIRE(tree.insert("Node25", 25000000) == "successful");
    REQUIRE(tree.insert("Node75", 75000000) == "successful");
    REQUIRE(tree.insert("Node10", 10000000) == "successful");
    REQUIRE(tree.insert("Node30", 30000000) == "successful");
    REQUIRE(tree.insert("Node60", 60000000) == "successful");
    REQUIRE(tree.insert("Node80", 80000000) == "successful");
    REQUIRE(tree.insert("Node28", 28000000) == "successful"); // Makes 30 a parent of 28.
    REQUIRE(tree.getSize() == 8); // Confirm that all 8 nodes were inserted.

    // Test Case 4.1: Delete a leaf node (a node with no children).
    // Node with ID 10000000 ("Node10") is a leaf in our example tree.
    REQUIRE(tree.remove(10000000) == "successful");
    REQUIRE(tree.getSize() == 7); // The tree size should decrease by 1.
    REQUIRE(tree.searchID(10000000) == "unsuccessful"); // Verify that Node10 is no longer found in the tree.

    // Test Case 4.2: Delete a node with one child.
    // Node with ID 30000000 ("Node30") has one child (Node28).
    REQUIRE(tree.remove(30000000) == "successful");
    REQUIRE(tree.getSize() == 6); // Tree size should decrease by 1 again.
    REQUIRE(tree.searchID(30000000) == "unsuccessful"); // Verify Node30 is gone.
    REQUIRE(tree.searchID(28000000) == "Node28"); // Its child (Node28) should still be in the tree and correctly linked.

    // Test Case 4.3: Delete a node with two children.
    // Node with ID 50000000 ("Node50") is the current root and has both left and right children.
    // When a node with two children is removed, it's typically replaced by its inorder successor (here, Node60).
    REQUIRE(tree.remove(50000000) == "successful");
    REQUIRE(tree.getSize() == 5); // Tree size decreases by 1.
    REQUIRE(tree.searchID(50000000) == "unsuccessful"); // Verify the original Node50 is gone.
    REQUIRE(tree.searchID(60000000) == "Node60"); // Verify its inorder successor (Node60) is still present.

    // As a simple check of overall structure, ensure the inorder traversal is not empty.
    REQUIRE(tree.printInorder().length() > 0);
}

// This test suite evaluates the AVL tree's performance and correctness
// under a high volume of operations, specifically 100 insertions followed by 10 random deletions.
TEST_CASE("Large Scale Operations - Insert, Random Remove, and Verify", "[large]") {
    AVLTree tree; // Start with a clean tree for this large-scale test.
    vector<int> inserted_ids; // A vector to keep track of all GatorIDs that were inserted.

    // Section 5.1: Insert at least 100 nodes.
    // Loop to insert 100 unique students with valid 8-digit GatorIDs.
    for (int i = 1; i <= 100; ++i) {
        string name = "User" + to_string(i); // Create a unique name for each user.
        int id = 10000000 + i; // Generate a unique 8-digit GatorID (e.g., 10000001, ..., 10000100).
        REQUIRE(tree.insert(name, id) == "successful"); // Assert that every insertion is successful.
        inserted_ids.push_back(id); // Store the ID so we can potentially remove it later.
    }
    REQUIRE(tree.getSize() == 100); // Verify that the tree now contains exactly 100 nodes.

    vector<int> ids_to_remove; // This vector will hold the 10 randomly selected IDs for removal.

    // Section 5.2: Select 10 random nodes for removal.
    // Set up a random number generator.
    random_device rd; // Provides a non-deterministic seed for better randomness.
    mt19937 gen(rd()); // Mersenne Twister engine for generating high-quality pseudo-random numbers.

    // Shuffle the entire list of inserted IDs to randomize their order.
    shuffle(inserted_ids.begin(), inserted_ids.end(), gen);

    // Take the first 10 IDs from the now-shuffled list. These will be our targets for removal.
    // This guarantees we try to remove 10 distinct elements that are known to exist.
    for (int i = 0; i < 10; ++i) {
        ids_to_remove.push_back(inserted_ids[i]);
    }

    // Section 5.3: Perform the removals and verify success.
    for (int id : ids_to_remove) {
        REQUIRE(tree.remove(id) == "successful"); // Assert that the removal of each selected ID is successful.
    }
    REQUIRE(tree.getSize() == 90); // Verify that the tree size has correctly decreased by 10.

    // Section 5.4: Check the tree's state (using inorder traversal as a proxy).
    string inorder_output = tree.printInorder();
    REQUIRE(inorder_output.length() > (90 * 4));

    // Spot-check: Verify that a specific ID that was *not* among the removed ones is still found.
    // Instead of assuming 'User11', find an ID that was definitely *not* removed.
    int id_to_spot_check = -1;
    for (int id : inserted_ids) { // Iterate through all initially inserted IDs
        bool was_removed = false;
        for (int removed_id : ids_to_remove) {
            if (id == removed_id) {
                was_removed = true;
                break;
            }
        }
        if (!was_removed) { // If this ID was NOT in the list of removed IDs
            id_to_spot_check = id; // This is a safe ID to check
            break; // Found one, no need to search further
        }
    }

    // Ensure we actually found an ID that wasn't removed (should always happen if <100% removed)
    REQUIRE(id_to_spot_check != -1);

    // Now perform the spot-check with an ID we know should still be there
    // Need to know the name associated with id_to_spot_check.
    // A simple way is to re-construct the name:
    string expected_name = "User" + to_string(id_to_spot_check - 10000000);
    REQUIRE(tree.searchID(id_to_spot_check) == expected_name); // Check for the found un-removed ID and its name
}

*/