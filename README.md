# Smart-Campus-Navigation-Facility-Analytics-System-2110-UNT

# Smart Campus Navigation and Facility Analytics System
**Phase:** Milestone 1

## Purpose
This project is a modular C++ application designed to load, validate, and analyze campus data from structured text files. The system allows users to:
- Locate campus facilities using a custom-built Hash Table indexed by facility IDs.
- Explore campus walkways and find reachable buildings using an undirected Graph and Breadth-First Search (BFS).
- Browse academic department hierarchies represented through a General (n-ary) Tree structure and preorder traversals.

## Directory Layout
* `include/` : Contains all C++ header files (`.h`), defining the data structures and class interfaces (e.g., `HashTable.h`, `CampusGraph.h`, `DepartmentTree.h`, `Facility.h`, `Utils.h`, `FileLoader.h`).
* `src/` : Contains all C++ implementation files (`.cpp`), including the core logic and `main.cpp` for the interactive menu.
* `data/` : Contains the four instructor-provided starter data files (`buildings.txt`, `connections.txt`, `facilities.txt`, `departments.txt`).
* `testdata/` : Contains custom test files used to demonstrate edge cases, data validation, and hash collisions (e.g., `bad_fields.txt`, `collision_test.txt`).

## Build Instructions (UNT CSE CELL Machines)
To compile the project on the UNT CSE CELL machines, navigate to the root directory of the project and run the following `g++` command:

```bash
g++ -Wall -std=c++11 -Iinclude src/*.cpp -o campus
```
*Note: This command links all `.cpp` files in the `src/` folder, resolves includes from the `include/` folder, and generates an executable named `campus`.*

## Run Instructions
The program accepts an optional command-line argument to specify the directory containing the data files.

**1. Run with the default data directory (`data/`):**
If no arguments are provided, the program automatically looks for files in the `data/` folder.
```bash
./campus
```

**2. Run with a custom data directory (e.g., for testing):**
To test edge cases or hash collisions, provide the path to your custom directory (like `testdata/`).
```bash
./campus testdata/
```
