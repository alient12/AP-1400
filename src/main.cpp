#include <iostream>
#include <gtest/gtest.h>
#include "unique_ptr.h"
#include "shared_ptr.h"


int main(int argc, char **argv)
{
    if (true) // make false to run unit-tests
    {
        // debug section
        UniquePtr<int> ptr{new int{10}};
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