#include "program.h"    // Include its own header
#include "AdjacencyList.h" // AdjacencyList is used by runProgram
#include <iostream>     // Already included via program.h, but good practice for .cpp
#include <sstream>      // For std::stringstream (often useful for stream manipulation)

// The implementation of core program logic
void runProgram(std::istream& is, std::ostream& os) {
    int no_of_lines, power_iterations;
    std::string from, to;

    is >> no_of_lines;
    if (is.fail()) { os << "DEBUG: Failed to read no_of_lines." << std::endl; return; }
    is >> power_iterations;
    if (is.fail()) { os << "DEBUG: Failed to read power_iterations." << std::endl; return; }

    AdjacencyList graph; // Create a graph object

    for (int i = 0; i < no_of_lines; i++) {
        if (is.fail() || is.eof()) {
            os << "DEBUG: Stream failed or EOF reached prematurely in loop." << std::endl;
            break;
        }
        is >> from;
        if (is.fail()) { break; }
        is >> to;
        if (is.fail()) { break; }
        graph.addEdge(from, to);
    }

    graph.PageRank(power_iterations, os);
}
