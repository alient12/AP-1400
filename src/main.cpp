#include <iostream>
#include <gtest/gtest.h>
#include "bst.h"

int main(int argc, char **argv)
{
    if (true) // make false to run unit-tests
    {
        // debug section
        BST bst{};
        bst.add_node(10);
        bst.add_node(12);
        bst.add_node(13);
        bst.add_node(7);
        bst.add_node(8);
        bst.add_node(9);
        std::cout << bst;
        BST::Node** node = bst.find_parrent(9);
        std::cout << node << std::endl;
        // std::cout << *(node->right) << std::endl;
        // std::cout << "length: " << bst.length() << std::endl;
        // std::cout << "10 successor: " << (*bst.find_successor(10))->value << std::endl;
        std::cout << bst;
        bst.delete_node(10);
        // std::cout << bst;
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