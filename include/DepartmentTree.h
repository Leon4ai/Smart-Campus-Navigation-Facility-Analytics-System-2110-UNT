
// Purpose: General tree of academic departments (any number of children per node)
//          with search, indented hierarchy, traversals, and statistics.
// Author:  Member C
#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H

#include <string>
#include <vector>

struct DepartmentNode {
    std::string name;
    DepartmentNode* parent;                 // NULL for the root
    std::vector<DepartmentNode*> children;  // insertion order

    DepartmentNode(const std::string& n, DepartmentNode* p) : name(n), parent(p) {}
};

class DepartmentTree {
public:
    DepartmentTree();
    ~DepartmentTree();  // frees every node

    bool isEmpty() const;

    // Finds a node by name (case-insensitive, trimmed); NULL if missing.
    DepartmentNode* find(const std::string& name) const;

    // Creates the root. Fails if a root already exists.
    bool addRoot(const std::string& name);

    // Adds a child under an existing parent node.
    void addChild(DepartmentNode* parent, const std::string& name);

    int size() const;

    // Menu operations.
    void search(const std::string& name) const;   // TREE-4
    void displayHierarchy() const;                // TREE-5
    void preorder() const;                        // TREE-6
    void postorder() const;                       // TREE-7 (Final)
    void levelOrder() const;                      // TREE-7 (Final)
    void statistics() const;                      // TREE-8 (Final)

private:
    DepartmentNode* root;
    int nodeCount;

    // Copying would double-free nodes, so it is disabled.
    DepartmentTree(const DepartmentTree&);
    DepartmentTree& operator=(const DepartmentTree&);

    static void destroy(DepartmentNode* node);
    static DepartmentNode* findFrom(DepartmentNode* node, const std::string& lowerName);
    static void hierarchyFrom(const DepartmentNode* node, int depth);
    static void preorderFrom(const DepartmentNode* node, std::vector<std::string>& out);
    static void postorderFrom(const DepartmentNode* node, std::vector<std::string>& out);
    static int leavesFrom(const DepartmentNode* node);
    static int heightFrom(const DepartmentNode* node);
    static void printSequence(const std::string& title, const std::vector<std::string>& seq);
};

#endif
