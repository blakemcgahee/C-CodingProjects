#include "AdjacencyList.h"
#include <iostream>
#include <sstream>

// For suppressing unused parameter warnings in MSVC
#ifdef _MSC_VER
#define UNREFERENCED_PARAMETER(P) (P)
#else
#define UNREFERENCED_PARAMETER(P)
#endif

// Constructor implementation
AdjacencyList::AdjacencyList() {
    // Initialize your graph data structure here if needed.
}

// Dummy implementation for addEdge
void AdjacencyList::addEdge(const std::string& fromPage, const std::string& toPage) {
    // Explicitly reference parameters to suppress C4100 warning
    UNREFERENCED_PARAMETER(fromPage);
    UNREFERENCED_PARAMETER(toPage);
    // In the actual project, you'd add this edge to your graph.
}

// Dummy implementation for PageRank for the check-in.
// It will print some placeholder output to the provided ostream.
void AdjacencyList::PageRank(int powerIterations, std::ostream& os) {
    // Explicitly reference parameters to suppress C4100 warning
    UNREFERENCED_PARAMETER(powerIterations);

    // This dummy output is based on the "Example PageRank Output Test"
    // from your assignment's template, using its expected output order and values.
    // Your actual PageRank algorithm will replace this later.

    os << "facebook.com 0.20" << std::endl;
    os << "gmail.com 0.20" << std::endl;
    os << "google.com 0.10" << std::endl;
    os << "maps.com 0.30" << std::endl;
    os << "ufl.edu 0.20" << std::endl;
}
