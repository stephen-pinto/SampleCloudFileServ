// TestFileServ.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <crtdbg.h>
#include <boost/program_options.hpp>
#include "../CloudFileServLib/include/ListBlobs.h"
//#include "TestOne.h"
//#include "TestTwo.h"
#include "TestThree.h"
//#include "TestFour.h"

using namespace CloudFileServLib::BL;

void SimpleTest()
{
    std::cout << "Hello World!\n";
    ListBlobs lb;
    lb.ListAll();
}

int main()
{
    //Test1();
    //TestTwo_2();
    //return TestTwo_3(0, NULL);
    //Test2();
    //Test3();
    //Test4();

    Test1();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
