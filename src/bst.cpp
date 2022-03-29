#include "bst.h"

BST::Node::Node(int value, Node* left, Node* right)
{
    this->value = value;
    this->left = left;
    this->right = right;
}

BST::Node::Node()
{
    this->value = 0;
    this->left = nullptr;
    this->right = nullptr;
}

BST::Node::Node(const Node& node)
{
    this->value = node.value;
    this->left = node.left;
    this->right = node.right;
}
