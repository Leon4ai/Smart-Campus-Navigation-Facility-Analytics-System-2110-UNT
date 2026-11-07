#include "FileLoader.h"
#include "Utils.h"
#include <iostream>
#include <fstream>

namespace loader {

void loadBuildings(const std::string& path, CampusGraph& graph) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "Error: Could not open " << path << "\n";
        return;
    }

    std::string line;
    int lineNum = 0, acc = 0, rej = 0;

    while (std::getline(file, line)) {
        lineNum++;
        if (utils::isBlankOrComment(line)) continue;

        std::string bldgName = utils::trim(line);
        if (bldgName.empty()) {
            std::cout << "Warning in " << path << " line " << lineNum << ": empty building name\n";
            rej++;
        } else if (!graph.addBuilding(bldgName)) {
            std::cout << "Warning in " << path << " line " << lineNum << ": duplicate building name\n";
            rej++;
        } else {
            acc++;
        }
    }
    std::cout << path << ": " << acc << " accepted, " << rej << " rejected\n";
}

void loadConnections(const std::string& path, CampusGraph& graph) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "Error: Could not open " << path << "\n";
        return;
    }

    std::string line;
    int lineNum = 0, acc = 0, rej = 0;

    while (std::getline(file, line)) {
        lineNum++;
        if (utils::isBlankOrComment(line)) continue;

        std::vector<std::string> fields = utils::splitFields(line);
        if (fields.size() != 2) {
            std::cout << "Warning in " << path << " line " << lineNum << ": wrong field count\n";
            rej++;
            continue;
        }

        int b1 = graph.findBuilding(fields[0]);
        int b2 = graph.findBuilding(fields[1]);
        
        if (b1 == -1 || b2 == -1) {
            std::cout << "Warning in " << path << " line " << lineNum << ": unknown building reference\n";
            rej++;
        } else if (!graph.addEdge(b1, b2)) {
            std::cout << "Warning in " << path << " line " << lineNum << ": duplicate or self-connection\n";
            rej++;
        } else {
            acc++;
        }
    }
    std::cout << path << ": " << acc << " accepted, " << rej << " rejected\n";
}

void loadFacilities(const std::string& path, const CampusGraph& graph, FacilityDatabase& db) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "Error: Could not open " << path << "\n";
        return;
    }

    std::string line;
    int lineNum = 0, acc = 0, rej = 0;

    while (std::getline(file, line)) {
        lineNum++;
        if (utils::isBlankOrComment(line)) continue;

        std::vector<std::string> fields = utils::splitFields(line);
        if (fields.size() != 4) {
            std::cout << "Warning in " << path << " line " << lineNum << ": wrong field count\n";
            rej++;
            continue;
        }

        std::string upperId = utils::toUpper(fields[0]);
        if (!FacilityDatabase::isValidId(upperId)) {
            std::cout << "Warning in " << path << " line " << lineNum << ": invalid ID format\n";
            rej++;
            continue;
        }
        if (fields[1].empty() || fields[3].empty()) {
            std::cout << "Warning in " << path << " line " << lineNum << ": empty facility name or category\n";
            rej++;
            continue;
        }
        int bIdx = graph.findBuilding(fields[2]);
        if (bIdx == -1) {
            std::cout << "Warning in " << path << " line " << lineNum << ": unknown building reference\n";
            rej++;
            continue;
        }

        Facility f;
        f.id = upperId;
        f.name = fields[1];
        f.building = graph.buildingName(bIdx); // Use exact spelling from buildings.txt
        f.category = fields[3];

        if (!db.add(f)) {
            std::cout << "Warning in " << path << " line " << lineNum << ": duplicate ID\n";
            rej++;
        } else {
            acc++;
        }
    }
    const HashTable& ht = db.table();
    std::cout << path << ": " << acc << " accepted, " << rej << " rejected "
              << "(hash capacity " << ht.capacity() << ", entries " << ht.size() 
              << ", collisions " << ht.collisions() << ")\n";
}

void loadDepartments(const std::string& path, DepartmentTree& tree) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "Error: Could not open " << path << "\n";
        return;
    }

    std::string line;
    int lineNum = 0, acc = 0, rej = 0;

    while (std::getline(file, line)) {
        lineNum++;
        if (utils::isBlankOrComment(line)) continue;

        std::vector<std::string> fields = utils::splitFields(line);
        if (fields.size() != 2) {
            std::cout << "Warning in " << path << " line " << lineNum << ": wrong field count\n";
            rej++;
            continue;
        }
        
        std::string name = fields[0];
        std::string parentName = fields[1];
        
        if (name.empty()) {
            std::cout << "Warning in " << path << " line " << lineNum << ": empty department name\n";
            rej++;
            continue;
        }
        
        if (tree.find(name)) {
            std::cout << "Warning in " << path << " line " << lineNum << ": duplicate department name\n";
            rej++;
            continue;
        }

        if (tree.isEmpty()) {
            if (utils::equalsIgnoreCase(parentName, "NONE")) {
                tree.addRoot(name);
                acc++;
            } else {
                std::cout << "Warning in " << path << " line " << lineNum << ": first record must have parent NONE\n";
                rej++;
            }
        } else {
            DepartmentNode* parentNode = tree.find(parentName);
            if (!parentNode) {
                std::cout << "Warning in " << path << " line " << lineNum << ": unknown parent reference\n";
                rej++;
            } else {
                tree.addChild(parentNode, name);
                acc++;
            }
        }
    }
    std::cout << path << ": " << acc << " accepted, " << rej << " rejected\n";
}

} // namespace loader
