/*
Old version//
#include "Utils.h"
#include "FileLoader.h"
#include "CampusGraph.h"
#include "Facility.h"
#include "DepartmentTree.h"
#include <iostream>
#include <string>

void displayMenu() {
    std::cout << "\n--- System Menu ---\n"
              << "1. View all facilities\n"
              << "2. Search facility by ID\n"
              << "3. Search facility by name\n"
              << "4. Search facility by category\n"
              << "5. View campus graph\n"
              << "6. Display graph counts and degrees\n"
              << "7. Find reachable buildings (BFS)\n"
              << "8. Find shortest path (BFS)\n"
              << "9. Add department\n"
              << "10. Search department\n"
              << "11. Display department hierarchy\n"
              << "12. Preorder traversal\n"
              << "13. Postorder traversal\n"
              << "14. Level-order traversal\n"
              << "15. Department statistics\n"
              << "16. Facility category report\n"
              << "17. Graph connectivity report\n"
              << "18. Exit\n";
}

int main(int argc, char* argv[]) {
    std::string dataDir = "data/";
    if (argc > 1) {
        dataDir = argv[1];
        if (dataDir.back() != '/' && dataDir.back() != '\\') {
            dataDir += "/";
        }
    }

    CampusGraph graph;
    FacilityDatabase db;
    DepartmentTree tree;

    loader::loadBuildings(dataDir + "buildings.txt", graph);
    loader::loadConnections(dataDir + "connections.txt", graph);
    loader::loadFacilities(dataDir + "facilities.txt", graph, db);
    loader::loadDepartments(dataDir + "departments.txt", tree);

    std::string input;
    while (true) {
        displayMenu();
        if (!utils::readLine("Select an option: ", input)) break;
        
        int choice;
        if (!utils::parseInt(input, choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 18) {
            std::cout << "Exiting program.\n";
            break;
        }

        switch (choice) {
            case 1:
                db.displayAll();
                break;
            case 2:
                if (utils::readLine("Enter Facility ID: ", input)) db.searchById(input);
                break;
            case 3:
                if (utils::readLine("Enter Facility Name: ", input)) db.searchByName(input);
                break;
            case 4:
                if (utils::readLine("Enter Facility Category: ", input)) db.searchByCategory(input);
                break;
            case 5:
                graph.display();
                break;
            case 6:
                graph.displayCountsAndDegrees();
                break;
            case 7:
                if (utils::readLine("Enter starting building: ", input)) graph.reachable(input);
                break;
            case 8: {
                std::string start, dest;
                if (utils::readLine("Enter starting building: ", start) && 
                    utils::readLine("Enter destination building: ", dest)) {
                    graph.shortestPath(start, dest);
                }
                break;
            }
            case 9: {
                if (!utils::readLine("Enter new department name: ", input) || input.empty()) {
                    std::cout << "Error: Invalid department name.\n";
                    break;
                }
                if (tree.find(input)) {
                    std::cout << "Error: Department name already exists.\n";
                    break;
                }
                if (tree.isEmpty()) {
                    tree.addRoot(input);
                    std::cout << "Root department added.\n";
                } else {
                    std::string parentInput;
                    if (utils::readLine("Enter parent department name: ", parentInput)) {
                        DepartmentNode* parentNode = tree.find(parentInput);
                        if (!parentNode) {
                            std::cout << "Error: Unknown parent department.\n";
                        } else {
                            tree.addChild(parentNode, input);
                            std::cout << "Department added.\n";
                        }
                    }
                }
                break;
            }
            case 10:
                if (utils::readLine("Enter department name: ", input)) tree.search(input);
                break;
            case 11:
                tree.displayHierarchy();
                break;
            case 12:
                tree.preorder();
                break;
            case 13:
                tree.postorder();
                break;
            case 14:
                tree.levelOrder();
                break;
            case 15:
                tree.statistics();
                break;
            case 16:
                db.categoryReport();
                break;
            case 17:
                graph.connectivityReport();
                break;
            default:
                std::cout << "Invalid menu choice. Please select 1-18.\n";
                break;
        }
    }

    return 0;
}
   */


// updated final main.cpp
#include "Utils.h"
#include "FileLoader.h"
#include "CampusGraph.h"
#include "Facility.h"
#include "DepartmentTree.h"
#include <iostream>
#include <string>

// Set to true for the Final submission, false for Milestone 1 (UI-7).
const bool USE_FINAL_MENU = true;

// Reads a name. Prints an error and returns false if it is blank (UI-5).
bool readName(const std::string& prompt, std::string& out) {
    if (!utils::readLine(prompt, out)) return false;
    if (out.empty()) {
        std::cout << "Error: name cannot be blank.\n";
        return false;
    }
    return true;
}

// Prints the Milestone 1 menu (Section 6.9).
void displayM1Menu() {
    std::cout << "\n--- System Menu ---\n"
              << "1. View all facilities\n"
              << "2. Search facility by ID\n"
              << "3. View campus graph\n"
              << "4. Display graph counts and degrees\n"
              << "5. Find reachable buildings (BFS)\n"
              << "6. Add department\n"
              << "7. Search department\n"
              << "8. Display department hierarchy\n"
              << "9. Run preorder traversal\n"
              << "10. Exit\n";
}

// Prints the Final menu (Section 6.9).
void displayFinalMenu() {
    std::cout << "\n--- System Menu ---\n"
              << "1. View all facilities\n"
              << "2. Search facility by ID\n"
              << "3. Search facility by name\n"
              << "4. Search facility by category\n"
              << "5. View campus graph\n"
              << "6. Display graph counts and degrees\n"
              << "7. Find reachable buildings (BFS)\n"
              << "8. Find shortest path (BFS)\n"
              << "9. Add department\n"
              << "10. Search department\n"
              << "11. Display department hierarchy\n"
              << "12. Preorder traversal\n"
              << "13. Postorder traversal\n"
              << "14. Level-order traversal\n"
              << "15. Department statistics\n"
              << "16. Facility category report\n"
              << "17. Graph connectivity report\n"
              << "18. Exit\n";
}

// Adds a department: root with no parent prompt if the tree is empty (TREE-3).
void addDepartment(DepartmentTree& tree) {
    std::string name;
    if (!readName("Enter new department name: ", name)) return;
    if (tree.find(name)) {
        std::cout << "Error: department \"" << name << "\" already exists.\n";
        return;
    }
    if (tree.isEmpty()) {
        tree.addRoot(name);
        std::cout << "Root department added.\n";
        return;
    }
    std::string parentName;
    if (!readName("Enter parent department name: ", parentName)) return;
    DepartmentNode* parentNode = tree.find(parentName);
    if (!parentNode) {
        std::cout << "Error: unknown parent department \"" << parentName << "\".\n";
        return;
    }
    tree.addChild(parentNode, name);
    std::cout << "Department added.\n";
}

int main(int argc, char* argv[]) {
    // NFR-10: optional data directory argument, default data/.
    std::string dataDir = "data/";
    if (argc > 1) {
        dataDir = argv[1];
        if (dataDir.back() != '/' && dataDir.back() != '\\') {
            dataDir += "/";
        }
    }

    CampusGraph graph;
    FacilityDatabase db;
    DepartmentTree tree;

    // LOAD-1: required load order.
    loader::loadBuildings(dataDir + "buildings.txt", graph);
    loader::loadConnections(dataDir + "connections.txt", graph);
    loader::loadFacilities(dataDir + "facilities.txt", graph, db);
    loader::loadDepartments(dataDir + "departments.txt", tree);

    const int exitOption = USE_FINAL_MENU ? 18 : 10;
    std::string input;
    while (true) {
        if (USE_FINAL_MENU) displayFinalMenu();
        else displayM1Menu();
        if (!utils::readLine("Select an option: ", input)) break;

        int choice;
        if (!utils::parseInt(input, choice) || choice > exitOption) {
            std::cout << "Invalid menu choice. Please enter a number from 1 to " << exitOption << ".\n";
            continue;
        }
        if (choice == exitOption || choice == 0) {   // 0 also exits (UI-7)
            std::cout << "Exiting program.\n";
            break;
        }

        // Map Milestone 1 numbers onto the Final numbers so one switch handles both.
        if (!USE_FINAL_MENU) {
            const int m1ToFinal[] = {0, 1, 2, 5, 6, 7, 9, 10, 11, 12};
            choice = m1ToFinal[choice];
        }

        std::string start, dest;
        switch (choice) {
            case 1: db.displayAll(); break;
            case 2:
                if (utils::readLine("Enter Facility ID: ", input)) {
                    if (input.empty()) std::cout << "Error: ID cannot be blank.\n";
                    else db.searchById(input);
                }
                break;
            case 3: if (readName("Enter Facility Name: ", input)) db.searchByName(input); break;
            case 4: if (readName("Enter Facility Category: ", input)) db.searchByCategory(input); break;
            case 5: graph.display(); break;
            case 6: graph.displayCountsAndDegrees(); break;
            case 7: if (readName("Enter starting building: ", input)) graph.reachable(input); break;
            case 8:
                if (readName("Enter starting building: ", start) &&
                    readName("Enter destination building: ", dest)) {
                    graph.shortestPath(start, dest);
                }
                break;
            case 9: addDepartment(tree); break;
            case 10: if (readName("Enter department name: ", input)) tree.search(input); break;
            case 11: tree.displayHierarchy(); break;
            case 12: tree.preorder(); break;
            case 13: tree.postorder(); break;
            case 14: tree.levelOrder(); break;
            case 15: tree.statistics(); break;
            case 16: db.categoryReport(); break;
            case 17: graph.connectivityReport(); break;
        }
    }
    return 0;
}
