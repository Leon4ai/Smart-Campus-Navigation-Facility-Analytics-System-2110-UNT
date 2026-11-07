#include "CampusGraph.h"
#include "Utils.h"
#include <iostream>
#include <queue>

CampusGraph::CampusGraph() : edgeCount(0) {}

int CampusGraph::findBuilding(const std::string& name) const {
    for (size_t i = 0; i < names.size(); i++) {
        if (utils::equalsIgnoreCase(names[i], name)) {
            return (int)i;
        }
    }
    return -1;
}

bool CampusGraph::addBuilding(const std::string& name) {
    if (findBuilding(name) != -1) return false;
    names.push_back(name);
    adj.push_back(std::vector<int>());
    return true;
}

bool CampusGraph::hasEdge(int a, int b) const {
    for (size_t i = 0; i < adj[a].size(); i++) {
        if (adj[a][i] == b) return true;
    }
    return false;
}

bool CampusGraph::addEdge(int a, int b) {
    if (a == b) return false; // Self-connection
    if (hasEdge(a, b)) return false; // Duplicate
    
    adj[a].push_back(b);
    adj[b].push_back(a);
    edgeCount++;
    return true;
}

const std::string& CampusGraph::buildingName(int index) const {
    return names[index];
}

int CampusGraph::buildingCount() const {
    return (int)names.size();
}

int CampusGraph::connectionCount() const {
    return edgeCount;
}

void CampusGraph::display() const {
    if (names.empty()) {
        std::cout << "No buildings in graph.\n";
        return;
    }
    for (size_t i = 0; i < names.size(); i++) {
        std::cout << names[i] << ": ";
        if (adj[i].empty()) {
            std::cout << "(no connections)\n";
        } else {
            for (size_t j = 0; j < adj[i].size(); j++) {
                std::cout << names[adj[i][j]];
                if (j + 1 < adj[i].size()) std::cout << ", ";
            }
            std::cout << "\n";
        }
    }
}

void CampusGraph::displayCountsAndDegrees() const {
    std::cout << "Building Degrees:\n";
    for (size_t i = 0; i < names.size(); i++) {
        std::cout << names[i] << ": " << adj[i].size() << "\n";
    }
    std::cout << "Total buildings: " << names.size() << "\n";
    std::cout << "Total connections: " << edgeCount << "\n";
}

void CampusGraph::reachable(const std::string& start) const {
    int startIdx = findBuilding(start);
    if (startIdx == -1) {
        std::cout << "Error: Unknown starting building.\n";
        return;
    }
    
    std::vector<bool> visited(names.size(), false);
    std::vector<int> distances(names.size(), 0);
    std::queue<int> q;
    
    visited[startIdx] = true;
    q.push(startIdx);
    
    int reachableCount = 0;
    std::cout << "From " << names[startIdx] << ":\n";
    
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        reachableCount++;
        
        std::cout << names[curr] << " (distance " << distances[curr] << ")\n";
        
        for (size_t i = 0; i < adj[curr].size(); i++) {
            int neighbor = adj[curr][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                distances[neighbor] = distances[curr] + 1;
                q.push(neighbor);
            }
        }
    }
    std::cout << "Reachable: " << reachableCount << " of " << names.size() << " buildings\n";
}

void CampusGraph::shortestPath(const std::string& start, const std::string& dest) const {
    int startIdx = findBuilding(start);
    int destIdx = findBuilding(dest);
    
    if (startIdx == -1 || destIdx == -1) {
        std::cout << "Error: Unknown building reference.\n";
        return;
    }
    
    if (startIdx == destIdx) {
        std::cout << names[startIdx] << "\nNumber of connections: 0\n";
        return;
    }
    
    std::vector<bool> visited(names.size(), false);
    std::vector<int> parent(names.size(), -1);
    std::queue<int> q;
    
    visited[startIdx] = true;
    q.push(startIdx);
    
    bool found = false;
    while (!q.empty() && !found) {
        int curr = q.front();
        q.pop();
        
        for (size_t i = 0; i < adj[curr].size(); i++) {
            int neighbor = adj[curr][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = curr;
                q.push(neighbor);
                if (neighbor == destIdx) {
                    found = true;
                    break;
                }
            }
        }
    }
    
    if (!found) {
        std::cout << "No path exists between " << names[startIdx] << " and " << names[destIdx] << "\n";
        return;
    }
    
    std::vector<int> path;
    int curr = destIdx;
    while (curr != -1) {
        path.push_back(curr);
        curr = parent[curr];
    }
    
    for (int i = (int)path.size() - 1; i >= 0; i--) {
        std::cout << names[path[i]] << "\n";
    }
    std::cout << "Number of connections: " << path.size() - 1 << "\n";
}

void CampusGraph::connectivityReport() const {
    if (names.empty()) {
        std::cout << "Total buildings: 0\nTotal connections: 0\n";
        return;
    }
    
    int maxDegree = -1;
    for (size_t i = 0; i < adj.size(); i++) {
        if ((int)adj[i].size() > maxDegree) maxDegree = (int)adj[i].size();
    }
    
    std::vector<std::string> highest;
    std::vector<std::string> isolated;
    for (size_t i = 0; i < adj.size(); i++) {
        if ((int)adj[i].size() == maxDegree) highest.push_back(names[i]);
        if (adj[i].empty()) isolated.push_back(names[i]);
    }
    
    int components = 0;
    std::vector<bool> visited(names.size(), false);
    
    for (size_t i = 0; i < names.size(); i++) {
        if (!visited[i]) {
            components++;
            std::queue<int> q;
            visited[i] = true;
            q.push(i);
            while (!q.empty()) {
                int curr = q.front();
                q.pop();
                for (size_t j = 0; j < adj[curr].size(); j++) {
                    if (!visited[adj[curr][j]]) {
                        visited[adj[curr][j]] = true;
                        q.push(adj[curr][j]);
                    }
                }
            }
        }
    }
    
    std::cout << "Total buildings: " << names.size() << "\n";
    std::cout << "Total connections: " << edgeCount << "\n";
    std::cout << "Highest degree (" << maxDegree << "): ";
    for (size_t i = 0; i < highest.size(); i++) {
        std::cout << highest[i] << (i + 1 == highest.size() ? "" : ", ");
    }
    std::cout << "\nIsolated buildings: ";
    if (isolated.empty()) {
        std::cout << "None";
    } else {
        for (size_t i = 0; i < isolated.size(); i++) {
            std::cout << isolated[i] << (i + 1 == isolated.size() ? "" : ", ");
        }
    }
    std::cout << "\nConnected components: " << components << "\n";
}
