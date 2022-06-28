#include <iostream>
//#include "../include/cmd_line_provider.h"
#include "../include/salt_generator.hpp"

using namespace cmd_tool;

int main()
{
    std::cout << "Hello world" << std::endl;
    //cmd_line_provider provider;
    //provider.run(0, NULL);
    salt_generator gen;
    auto hash = gen.generate_salt(32);
    std::cout << "Hex hash: " << hash << std::endl;
    return 0;
}