#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream> // For std::istream, std::ostream
#include <string>   // For std::string

// Declare the runProgram function that will contain core logic.
// This declaration allows main.cpp and test.cpp to use it.
void runProgram(std::istream& is, std::ostream& os);

#endif // PROGRAM_H
