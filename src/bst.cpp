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
    Node*& root{this->get_root()};
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
    Node*& root{this->get_root()};
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

size_t BST::length()
{
    size_t length{1};
    std::function<void(BST::Node *&,size_t&)> add_children_num;
    add_children_num = [&add_children_num](BST::Node *&node, size_t &len)
    {
        if (node->right != nullptr)
        {
            len++;
            add_children_num(node->right, len);
        }
        if (node->left != nullptr)
        {
            len++;
            add_children_num(node->left, len);
        }
    };
    Node*& root{this->get_root()};
    if (root == nullptr) return 0;
    add_children_num(root, length);
    return length;
}

BST::Node** BST::find_successor(int value)
{
    Node*& node{*find_node(value)};
    if (node == nullptr || node->left == nullptr) return nullptr;
    node = node->left;
    while(true)
    {
        if (node->right != nullptr)
            node = node->right;
        else
            return &node;
    }
}