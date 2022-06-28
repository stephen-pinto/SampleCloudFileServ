#include <iostream>
//#include "../include/cmd_line_provider.h"
//#include "../include/salt_generator.hpp"
#include "../include/crypto_helper.h"

using namespace cmd_tool;
#define KEY_SIZE 32

int main()
{
    std::cout << "Hello crypto world" << std::endl;
    
    salt_generator gen;
    auto piv = gen.generate_iv(KEY_SIZE);
    auto encr_iv = gen.generate_iv(KEY_SIZE);
    
    crypto_helper ch;
    auto key = ch.generate_key("SamplePass", piv);
    auto cipher = ch.encrypt(key, encr_iv, "This is an ecrypted data content");
    std::cout << "Cipher:\n" << cipher << std::endl;
    auto plain = ch.decrypt(key, encr_iv, cipher);
    std::cout << "Actual:\n" << plain << std::endl;

    return 0;
}