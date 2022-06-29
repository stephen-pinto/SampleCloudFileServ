#include <iostream>
//#include "../include/cmd_line_provider.h"
//#include "../include/salt_generator.hpp"
#include "../include/crypto_helper.h"
#include <fstream>
#include <string>

using namespace cmd_tool;
#define KEY_SIZE 32

void TestOne()
{
    salt_generator gen;
    auto piv = gen.generate_iv(KEY_SIZE);
    auto encr_iv = gen.generate_iv(KEY_SIZE);
    
    crypto_helper ch;
    auto key = ch.generate_key("SamplePass", piv);
    auto cipher = ch.encrypt(key, encr_iv, "This is an ecrypted data content");
    std::cout << "Cipher:\n" << cipher << std::endl;
    auto plain = ch.decrypt(key, encr_iv, cipher);
    std::cout << "Actual:\n" << plain << std::endl;
}

void TestTwo()
{
    salt_generator gen;
    auto piv = gen.generate_iv(KEY_SIZE);
    auto encr_iv = gen.generate_iv(KEY_SIZE);
    
    crypto_helper ch;
    auto key = ch.generate_key("SamplePass", piv);
    std::ifstream f("/Users/stephen/Workspace/cpp/Projects/TestData/small.txt");
    std::string str((std::istreambuf_iterator<char>(f)),
                 std::istreambuf_iterator<char>());
    auto hash = ch.gen_checksum(str);
    std::cout << "Generated hash:\n"
              << hash << std::endl;
    std::cout << "Actual len:\n"
              << str.length() << std::endl;
    auto cipher = ch.encrypt(key, encr_iv, str);
    std::cout << "Cipher len:\n" << cipher.length() << std::endl;
    auto plain = ch.decrypt(key, encr_iv, cipher);
    //std::cout << "Actual:\n" << plain << std::endl;
    std::cout << "Actual len:\n"
              << plain.length() << std::endl;
}

int main()
{
    std::cout << "Hello crypto world" << std::endl;
    TestTwo();
    return 0;
}