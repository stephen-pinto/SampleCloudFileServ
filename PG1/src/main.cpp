#include <iostream>
//#include "../include/cmd_line_provider.h"
//#include "../include/salt_generator.hpp"
#include "../include/crypto_helper.h"
#include "../include/file_chunker.h"
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

void TestThree()
{
    file_chunker fc(100000);
    //std::string full_file = "";
    fc.open_file("/Users/stephen/Workspace/cpp/Projects/TestData/small.txt");
    int chunk_set = 1;
    std::vector<byte> one_vec;
    while (fc.has_more())
    {
        _PRINT("Printing chunk : " << chunk_set);
        _PRINT("\n");
        auto chunk = fc.read_next_chunk();
        one_vec.insert(one_vec.end(), chunk.begin(), chunk.end());
        _PRINT("\n");
        chunk_set++;
    }
    
    _PRINT("Nothing more to read");
    std::string full_file(one_vec.begin(), one_vec.end());
    _PRINT(full_file.length());
    _PRINT(full_file);

    std::cout << "File closed" << std::endl;
}

int main()
{
    std::cout << "Hello crypto world" << std::endl;
    //TestTwo();
    TestThree();
    return 0;
}