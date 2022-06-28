#include <iostream>
//#include "../include/cmd_line_provider.h"
//#include "../include/salt_generator.hpp"
#include "../include/crypto_helper.h"

using namespace cmd_tool;

int main()
{
    std::cout << "Hello world" << std::endl;
    //cmd_line_provider provider;
    //provider.run(0, NULL);
    
    salt_generator gen;
    auto salt = gen.generate_salt(32);
    auto iv = gen.generate_iv(32);
    // std::cout << "Hex hash: " << salt << std::endl;

    crypto_helper ch;
    ch.generate_key("SamplePass", iv);
    ch.generate_key("SamplePass", iv);

    return 0;
}