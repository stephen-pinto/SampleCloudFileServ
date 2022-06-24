#include <iostream>
#include "../include/cmd_line_provider.h"

using namespace cmd_tool;

int main()
{
    std::cout << "Hello world" << std::endl;
    cmd_line_provider provider;
    provider.run(0, NULL);
    return 0;
}