/*
Project Author: Blake McGahee
UFID: 82924917
UF – COP3530 Summer’25
Started: 05/24/2025
Last Modified: 06/08/2025

Change Log:
Date:           Change:
05/24/2025      Initial Setup: Started with a basic 'main' function to ensure the project compiles and prints a simple greeting message.
05/27/2025      Command Loop Integration: Implemented the core loop to read the number of commands and process each command line-by-line using 'getline'.
05/28/2025      AVLTree Instance Creation: Instantiated the AVLTree object and began calling its 'processCommand' method to route input to the AVL tree's functionality.
06/01/2025      Input Consumption Refinement: Added 'cin.ignore()' after reading 'num_commands' to handle leftover newline characters, ensuring 'getline()' reads correctly.
06/01/2025      Output Display: Configured the program to print the string result returned by 'processCommand', displaying "successful", "unsuccessful", or query results.
*/


#include <iostream>  // Standard library for using in/out objects
#include <string>    // Standard library for using string objects.
#include "avl_tree.h" // Custom header file for our AVLTree class. This makes the AVL tree functions available.

using namespace std; // Using the standard namespace to simplify code by not having to type 'std::' everywhere.

int main() {
    // A simple message to confirm the program has started successfully.
    // cout << "AVL program has started!\n";

    // Create an instance of our AVLTree class. This object will manage all the student data
    // (insertions, deletions, searches, etc.) according to AVL tree rules.
    AVLTree tree;

    int num_commands;
    // Read the very first number from the input. This number tells us how many commands will follow.
    cin >> num_commands;
    // Important: 'cin >> num_commands' only reads the number. This line consumes the leftover newline character
    // so that 'getline' in the loop starts reading from the next actual command line.
    cin.ignore();

    // Loop through each command, processing them one by one.
    for (int i = 0; i < num_commands; ++i) {
        string command_line;
        // Read the entire line of input for the current command. This is crucial because commands can contain spaces.
        getline(cin, command_line);

        // Pass the full command line string to the AVLTree's 'processCommand' method.
        // This method is designed to figure out what operation to perform, validate input,
        // and execute the corresponding AVL tree function.
        string result = tree.processCommand(command_line);

        // Print the result of the command processing to the console.
        // This result could be "successful", "unsuccessful", a student's name, or a list of IDs.
        cout << result << endl;
    }

    // The program successfully completes after all commands have been processed.
    return 0;
}
