#include <iostream>
#include "program.h" // Now includes program.h to get runProgram

// main function for your standalone application
int main() {
    runProgram(std::cin, std::cout); // Calls the core program logic
    return 0;
}
