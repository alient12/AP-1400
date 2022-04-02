#ifndef BST_H
#define BST_H

#include <functional>
#include <iostream>
#include <compare>
#include <iomanip>
#include <string>
#include <vector>
#include <initializer_list>

class BST
{
public:
    class Node
    {
    public:
        Node(int value, Node* left, Node* right);
        Node();
        Node(const Node& node);
        std::partial_ordering operator<=>(int num) const;
        bool operator==(int num) const;
        friend std::partial_ordering operator<=>(const int num, const Node& node);
        friend bool operator==(const int num, const Node& node);
        friend std::ostream &operator<<(std::ostream &os, const Node &node);

        int value;
        Node* left;
        Node* right;
    };
    BST() = default;
    BST(BST &bst);
    BST(BST &&bst);
    ~BST();
    BST(std::initializer_list<int> args);
    Node *&get_root();
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    friend std::ostream &operator<<(std::ostream &os, BST &bst);
    BST &operator++();
    BST operator++(int);
    BST &operator=(BST &&bst) = default;
    BST &operator=(BST &bst);

private:
    Node* root{nullptr};
};

#endif //BST_H