#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "avl_tree.h"
#include <random>
#include <algorithm>
#include <vector>
#include <string>

// Blake McGahee
// UFID: 82924917


TEST_CASE("Incorrect Commands", "[parsing]") {
    AVLTree tree;
    REQUIRE(tree.processCommand("insert A11y 45679999") == "unsuccessful"); // Invalid name (no quotes)
    REQUIRE(tree.processCommand("insert \"Valid Name\" 1234567") == "unsuccessful"); // Invalid ID (7 digits)
    REQUIRE(tree.processCommand("insert \"Name\" ABCDEFGH") == "unsuccessful"); // Invalid ID (not a number)
    REQUIRE(tree.processCommand("remove NotAnID") == "unsuccessful"); // Invalid remove input
    REQUIRE(tree.processCommand("gibberish command") == "unsuccessful"); // Invalid command
}

TEST_CASE("Insert and Rotations", "[insertion][rotation]") {
    AVLTree tree;

    // Left-Left Rotation
    tree.processCommand("insert \"C\" 3");
    tree.processCommand("insert \"B\" 2");
    tree.processCommand("insert \"A\" 1");
    REQUIRE(tree.getHeight() == 2);

    AVLTree tree2;
    // Right-Right Rotation
    tree2.processCommand("insert \"A\" 1");
    tree2.processCommand("insert \"B\" 2");
    tree2.processCommand("insert \"C\" 3");
    REQUIRE(tree2.getHeight() == 2);

    AVLTree tree3;
    // Left-Right Rotation
    tree3.processCommand("insert \"A\" 1");
    tree3.processCommand("insert \"C\" 3");
    tree3.processCommand("insert \"B\" 2");
    REQUIRE(tree3.getHeight() == 2);

    AVLTree tree4;
    // Right-Left Rotation
    tree4.processCommand("insert \"C\" 3");
    tree4.processCommand("insert \"A\" 1");
    tree4.processCommand("insert \"B\" 2");
    REQUIRE(tree4.getHeight() == 2);
}

TEST_CASE("Large Insert and Remove", "[large]") {
    AVLTree tree;
    std::vector<int> inserted_ids;
    for (int i = 1; i <= 100; ++i) {
        std::string name = "\"User" + std::to_string(i) + "\"";
        int id = 20000000 + i;
        tree.processCommand("insert " + name + " " + std::to_string(id));
        inserted_ids.push_back(id);
    }
    REQUIRE(tree.getSize() == 100);

    std::vector<int> removed_ids;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, inserted_ids.size() - 1);

    for (int i = 0; i < 10; ++i) {
        int index = distrib(gen);
        int id_to_remove = inserted_ids[index];
        if (std::find(removed_ids.begin(), removed_ids.end(), id_to_remove) == removed_ids.end()) {
            REQUIRE(tree.processCommand("remove " + std::to_string(id_to_remove)) == "successful");
            removed_ids.push_back(id_to_remove);
        }
        else {
            i--; 
        }
    }
    REQUIRE(tree.getSize() == 90);

    std::string inorder_output = tree.printInorder();

    REQUIRE(tree.getSize() == 90);
}