#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <string>
#include <vector>
#include <map>
#include <iostream> // Needed for std::ostream

// This class will represent your graph using an adjacency list.
// For the testing check-in, only define the structure.
class AdjacencyList {
public:
    // Constructor
    AdjacencyList();

    // Method to add an edge between two pages (fromPage -> toPage)
    void addEdge(const std::string& fromPage, const std::string& toPage);

    // This method will calculate PageRank and print the results.
    // It takes an ostream reference to redirect output to a stringstream for testing.
    void PageRank(int powerIterations, std::ostream& os = std::cout);

    // Add other helper methods here later, e.g., to get graph size, etc.
    // std::map<std::string, double> getPageRanks(); // Example if want to return ranks directly

private:
    // Graph data structure will go here.
    // For example: std::map<std::string, std::vector<std::string>> adj;
    // Or more complex structures to store weights, etc.
};

#endif // ADJACENCY_LIST_H