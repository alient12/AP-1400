#include <iostream>
#include <gtest/gtest.h>
#include "unique_ptr.h"
#include "shared_ptr.h"
#include <typeinfo>


int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        // debug section
        // std::cout << typeid(std::make_unique<int>(10)).name() << std::endl;
        UniquePtr<int> ptr{make_unique<int>(10)};
        // UniquePtr<int> ptr{new int (10)};
        std::cout << ptr.get() << std::endl;
        std::cout << *ptr << std::endl;
        
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