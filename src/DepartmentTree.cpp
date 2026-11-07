

#include "DepartmentTree.h"
#include "Utils.h"
#include <iostream>
#include <queue>

DepartmentTree::DepartmentTree() : root(NULL), nodeCount(0) {}

DepartmentTree::~DepartmentTree() {
    destroy(root);
}

void DepartmentTree::destroy(DepartmentNode* node) {
    if (!node) return;
    for (size_t i = 0; i < node->children.size(); i++) {
        destroy(node->children[i]);
    }
    delete node;
}

bool DepartmentTree::isEmpty() const {
    return root == NULL;
}

DepartmentNode* DepartmentTree::find(const std::string& name) const {
    return findFrom(root, utils::toLower(utils::trim(name)));
}

DepartmentNode* DepartmentTree::findFrom(DepartmentNode* node, const std::string& lowerName) {
    if (!node) return NULL;
    if (utils::toLower(node->name) == lowerName) return node;
    
    for (size_t i = 0; i < node->children.size(); i++) {
        DepartmentNode* result = findFrom(node->children[i], lowerName);
        if (result) return result;
    }
    return NULL;
}

bool DepartmentTree::addRoot(const std::string& name) {
    if (root) return false;
    root = new DepartmentNode(name, NULL);
    nodeCount++;
    return true;
}

void DepartmentTree::addChild(DepartmentNode* parent, const std::string& name) {
    if (parent) {
        parent->children.push_back(new DepartmentNode(name, parent));
        nodeCount++;
    }
}

int DepartmentTree::size() const {
    return nodeCount;
}

void DepartmentTree::search(const std::string& name) const {
    DepartmentNode* node = find(name);
    if (!node) {
        std::cout << "Department not found.\n";
        return;
    }
    
    int depth = 0;
    DepartmentNode* curr = node;
    while (curr->parent != NULL) {
        depth++;
        curr = curr->parent;
    }
    
    std::cout << "Name: " << node->name << "\n";
    std::cout << "Parent: " << (node->parent ? node->parent->name : "None") << "\n";
    std::cout << "Direct Children: " << node->children.size() << "\n";
    std::cout << "Depth: " << depth << "\n";
}

void DepartmentTree::displayHierarchy() const {
    if (!root) {
        std::cout << "No departments are loaded.\n";
        return;
    }
    hierarchyFrom(root, 0);
}

void DepartmentTree::hierarchyFrom(const DepartmentNode* node, int depth) {
    if (!node) return;
    for (int i = 0; i < depth * 4; i++) std::cout << " ";
    std::cout << node->name << "\n";
    for (size_t i = 0; i < node->children.size(); i++) {
        hierarchyFrom(node->children[i], depth + 1);
    }
}

void DepartmentTree::printSequence(const std::string& title, const std::vector<std::string>& seq) {
    std::cout << title << ":\n";
    for (size_t i = 0; i < seq.size(); i++) {
        std::cout << seq[i] << "\n";
    }
}

void DepartmentTree::preorder() const {
    if (!root) {
        std::cout << "Tree is empty.\n";
        return;
    }
    std::vector<std::string> seq;
    preorderFrom(root, seq);
    printSequence("Preorder", seq);
}

void DepartmentTree::preorderFrom(const DepartmentNode* node, std::vector<std::string>& out) {
    if (!node) return;
    out.push_back(node->name);
    for (size_t i = 0; i < node->children.size(); i++) {
        preorderFrom(node->children[i], out);
    }
}

void DepartmentTree::postorder() const {
    if (!root) {
        std::cout << "Tree is empty.\n";
        return;
    }
    std::vector<std::string> seq;
    postorderFrom(root, seq);
    printSequence("Postorder", seq);
}

void DepartmentTree::postorderFrom(const DepartmentNode* node, std::vector<std::string>& out) {
    if (!node) return;
    for (size_t i = 0; i < node->children.size(); i++) {
        postorderFrom(node->children[i], out);
    }
    out.push_back(node->name);
}

void DepartmentTree::levelOrder() const {
    if (!root) {
        std::cout << "Tree is empty.\n";
        return;
    }
    std::vector<std::string> seq;
    std::queue<DepartmentNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        DepartmentNode* curr = q.front();
        q.pop();
        seq.push_back(curr->name);
        for (size_t i = 0; i < curr->children.size(); i++) {
            q.push(curr->children[i]);
        }
    }
    printSequence("Level-Order", seq);
}

int DepartmentTree::leavesFrom(const DepartmentNode* node) {
    if (!node) return 0;
    if (node->children.empty()) return 1;
    int sum = 0;
    for (size_t i = 0; i < node->children.size(); i++) {
        sum += leavesFrom(node->children[i]);
    }
    return sum;
}

int DepartmentTree::heightFrom(const DepartmentNode* node) {
    if (!node || node->children.empty()) return 0;
    int maxChildHeight = 0;
    for (size_t i = 0; i < node->children.size(); i++) {
        int h = heightFrom(node->children[i]);
        if (h > maxChildHeight) maxChildHeight = h;
    }
    return 1 + maxChildHeight;
}

void DepartmentTree::statistics() const {
    if (!root) {
        std::cout << "No departments are loaded.\nTotal departments: 0\nLeaf departments: 0\nTree height: N/A\n";
        return;
    }
    std::cout << "Total departments: " << nodeCount << "\n";
    std::cout << "Leaf departments: " << leavesFrom(root) << "\n";
    std::cout << "Tree height: " << heightFrom(root) << "\n";
}
