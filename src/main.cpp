#include <iostream>
#include <gtest/gtest.h>
#include "bst.h"

int main(int argc, char **argv)
{
    if (true) // make false to run unit-tests
    {
        // debug section
        {
            BST bst{};
            bst.add_node(25);
            bst.add_node(10);
            bst.add_node(50);
            bst.add_node(65);
            bst.add_node(5);
            bst.add_node(20);
            bst.add_node(22);
            
            int test_value{bst.get_root()->left->right->value};
            BST::Node* adddress_of_root{*bst.find_node(25)};

            BST move{};
            move = std::move(bst);
        }
        //destructor is broken for move constructed instance!!!  

        //
        // BST bst1{5, 1, 10, 2, 8, 50, 4, 60};
        // BST bst2{3, 2, 100, 20, 8, 50, 4, 60, 44, 23};
        // std::cout << (*bst1.find_successor(5))->value << std::endl;
        // std::cout << bst2.length() << std::endl;
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;   
}