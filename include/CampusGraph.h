
// Purpose: Undirected, unweighted campus graph stored as an adjacency list.
//          Provides display, counts/degrees, BFS reachability, BFS shortest
//          path, and the connectivity report.
// Author:  Member B
#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H

#include <string>
#include <vector>

class CampusGraph {
public:
    CampusGraph();

    // Returns the vertex index of a building (case-insensitive, trimmed), or -1.
    int findBuilding(const std::string& name) const;

    // Adds a building. Returns false if the name already exists (ignoring case).
    bool addBuilding(const std::string& name);

    // True if a and b are already connected (in either direction).
    bool hasEdge(int a, int b) const;

    // Adds an undirected edge (both endpoints updated, counted once).
    // Returns false for self-connections or duplicates.
    bool addEdge(int a, int b);

    const std::string& buildingName(int index) const;
    int buildingCount() const;
    int connectionCount() const;

    // Menu operations.
    void display() const;                                         // GRAPH-3
    void displayCountsAndDegrees() const;                         // GRAPH-4
    void reachable(const std::string& start) const;               // BFS-1..3
    void shortestPath(const std::string& start, const std::string& dest) const; // BFS-4,5
    void connectivityReport() const;                              // RPT-2

private:
    std::vector<std::string> names;          // buildings in insertion order
    std::vector<std::vector<int> > adj;      // neighbors in insertion order
    int edgeCount;
};

#endif
