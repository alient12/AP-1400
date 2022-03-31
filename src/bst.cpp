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

bool BST::Node::operator==(int num) const
{
    return this->value == num;
}

std::partial_ordering operator<=>(const int num, const BST::Node& node)
{
    return num <=> node.value;
}

bool operator==(const int num, const BST::Node& node)
{
    return node.value == num;
}

std::ostream& operator<<(std::ostream& os, const BST::Node& node)
{
    os << &node << std::setw(20) << "=> value:" << node.value;
    os << std::setw(20) << "left:" << node.left;
    os << std::setw(20) << "right:" << node.right;
    return os;
}

BST::Node*& BST::get_root()
{
    return root;
}

BST::Node** BST::find_node(int value)
{
    Node* root{this->get_root()};
    if (root == nullptr) return nullptr;

    Node*& parrent{root};
    bool is_searching{true};
    while(is_searching)
    {
        if (parrent->value == value)
        {
            is_searching = false;
            return &parrent;
        }

        else if (parrent->value < value)
        {
            if (parrent->right != nullptr)
            {
                parrent = parrent->right;
                continue;
            }
            else
            {
                is_searching = false;
            }
        }

        else if (parrent->value > value)
        {
            if (parrent->left != nullptr)
            {
                parrent = parrent->left;
                continue;
            }
            else
            {
                is_searching = false;
            }
        }
    }
    return nullptr;
}

bool BST::add_node(int value)
{
    Node*& root{this->get_root()};
    
    if (root == nullptr)
    {
        Node* node{new Node};
        node->value = value;
        root = node;
        return true;
    }

    Node* parrent{root};

    while(true)
    {
        if (parrent->value == value)
        {
            return false;
        }

        else if (parrent->value < value)
        {
            if (parrent->right != nullptr)
            {
                parrent = parrent->right;
                continue;
            }
            else
            {
                Node* node{new Node};
                node->value = value;
                parrent->right = node;
                return true;
            }
        }

        else if (parrent->value > value)
        {
            if (parrent->left != nullptr)
            {
                parrent = parrent->left;
                continue;
            }
            else
            {
                Node* node{new Node};
                node->value = value;
                parrent->left = node;
                return true;
            }
        }
    }
}

BST::Node** BST::find_parrent(int value)
{
    Node* root{this->get_root()};
    if (root == nullptr) return nullptr;

    Node*& parrent{root};
    bool is_searching{true};
    while(is_searching)
    {
        if (parrent->left != nullptr && parrent->left->value == value)
        {
            is_searching = false;
            return &parrent;
        }
        if (parrent->right != nullptr && parrent->right->value == value)
        {
            is_searching = false;
            return &parrent;
        }

        else if (parrent->value < value)
        {
            if (parrent->right != nullptr)
            {
                parrent = parrent->right;
                continue;
            }
            else
            {
                is_searching = false;
            }
        }

        else if (parrent->value > value)
        {
            if (parrent->left != nullptr)
            {
                parrent = parrent->left;
                continue;
            }
            else
            {
                is_searching = false;
            }
        }
    }
    return nullptr;
}