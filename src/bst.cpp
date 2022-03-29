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

std::partial_ordering BST::Node::operator<=>(int num) const
{
    return this->value <=> num;
}

std::partial_ordering operator<=>(const int num, const BST::Node& node)
{
    return node.value <=> num;
}

std::ostream& operator<<(std::ostream& os, const BST::Node& node)
{
    os << &node << std::setw(20) << "=> value:" << node.value;
    os << std::setw(20) << "left:" << node.left;
    os << std::setw(20) << "right:" << node.right;
    return os;
}