#include "binaryTree.h"
#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/* ================================== Node =================================== */
Node::Node(std::string str, int num, Node *left, Node *right) :
        str(std::move(str)), num(num), left(left), right(right) {}

Node *Node::leftSubtree() const {
    return left;
}

void Node::setleft(Node *n) {
    left = n;
}

Node *Node::rightSubtree() const {
    return right;
}

void Node::setright(Node *n) {
    right = n;
}

string Node::getstr() const {
    return str;
}

int Node::getnum() const {
    return num;
}

void Node::incnum() {
    num++;
}

Node *Node::mergeNodes(Node *leftNode, Node *rightNode) {
    return new Node(leftNode->str + rightNode->str, leftNode->num + rightNode->num, leftNode, rightNode);
}

/* =============================== Binary Tree =============================== */

Node *new_root(Node *node) {
    if (node == nullptr) {
        return nullptr;
    }

    return new Node(node->getstr(), node->getnum(), new_root(node->leftSubtree()), new_root(node->rightSubtree()));
}

Node *find_node(Node *node, Node *tree) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->getnum() == tree->getnum()) {
        return node;
    }

    Node *temp = find_node(node->leftSubtree(), tree);
    if (temp == nullptr) {
        temp = find_node(node->rightSubtree(), tree);
    }

    return temp;
}

BinaryTree::BinaryTree(Node *rootNode) {
    if (rootNode == nullptr) {
        return;
    }

    root = rootNode;
}

void delete_Node(Node *node) {
    if (node->leftSubtree() != nullptr) {
        delete_Node(node->leftSubtree());
    }
    if (node->rightSubtree() != nullptr) {
        delete_Node(node->rightSubtree());
    }

    delete node;
}

BinaryTree::~BinaryTree() {
    if (root != nullptr) {
        delete_Node(root);
    }
}

string findPath_recur(const Node *n, const string &s) {
    if (n == nullptr) { return "-1"; }
    if (n->getstr() == s) { return ""; }
    if (findPath_recur(n->leftSubtree(), s) != "-1") {
        return "0" + findPath_recur(n->leftSubtree(), s);
    }
    if (findPath_recur(n->rightSubtree(), s) != "-1") {
        return "1" + findPath_recur(n->rightSubtree(), s);
    }

    return "-1";
}

string BinaryTree::findPath(const string &s) const {
    return findPath_recur(root, s);
}

int sum_recur(Node *node) {
    if (node == nullptr) { return 0; }
    return node->getnum() + sum_recur(node->leftSubtree()) + sum_recur(node->rightSubtree());
}

int BinaryTree::sum() const {
    return sum_recur(root);
}

int depth_recur(Node *node) {
    if (node == nullptr) { return 0; }
    return max(depth_recur(node->leftSubtree()), depth_recur(node->rightSubtree())) + 1;
}

int BinaryTree::depth() const {
    return depth_recur(root);
}

void preorder_recur(Node *node) {
    if (node == nullptr) { return; }
    cout << node->getnum() << " ";
    preorder_recur(node->leftSubtree());
    preorder_recur(node->rightSubtree());
}

void BinaryTree::preorder_num() const {
    preorder_recur(root);
    cout << endl;
}

void inorder_recur(Node *node) {
    if (node == nullptr) { return; }
    inorder_recur(node->leftSubtree());
    cout << node->getstr() << " ";
    inorder_recur(node->rightSubtree());
}

void BinaryTree::inorder_str() const {
    inorder_recur(root);
    cout << endl;
}

void postorder_recur(Node *node) {
    if (node == nullptr) { return; }
    postorder_recur(node->leftSubtree());
    postorder_recur(node->rightSubtree());
    cout << node->getnum() << " ";
}

void BinaryTree::postorder_num() const {
    postorder_recur(root);
    cout << endl;
}

bool allPath_recur(Node *node, int sum) {
    if (node == nullptr && sum >= 0) { return false; }
    if (node->getnum() > sum) { return true; }
    if (!allPath_recur(node->leftSubtree(), sum - node->getnum())) { return false; }

    return allPath_recur(node->rightSubtree(), sum - node->getnum());
}

bool BinaryTree::allPathSumGreater(int sum) const {
    return allPath_recur(root, sum);
}

bool covered_recur(Node *node, Node *tree) {
    if (node == nullptr) { return true; }
    if (tree == nullptr) { return false; }

    return (node->getnum() == tree->getnum()) && covered_recur(node->leftSubtree(), tree->leftSubtree()) &&
           covered_recur(node->rightSubtree(), tree->rightSubtree());
}

bool BinaryTree::covered_by(const BinaryTree &tree) const {
    return covered_recur(root, tree.root);
}

bool BinaryTree::contained_by(const BinaryTree &tree) const {
    if (covered_recur(root, tree.root)) { return true; }
    return covered_recur(find_node(tree.root, root), root);
}

BinaryTree BinaryTree::copy() const {
    BinaryTree tree = BinaryTree(new_root(root));
    return tree;
}