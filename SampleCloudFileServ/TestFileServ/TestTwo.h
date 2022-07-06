#pragma once

#include "../CloudFileServLib/include/CryptoHelper.h"
#include "../CloudFileServLib/include/SaltGenerator.hpp"
#include "../CloudFileServLib/include/FileChangeChecker.h"

#define KEY_SIZE 32

using namespace CloudFileServLib::BL;


void TestTwo_1()
{
    SaltGenerator gen;
    auto piv = gen.GenerateIV(KEY_SIZE);
    auto encr_iv = gen.GenerateIV(KEY_SIZE);

    CryptoHelper ch;
    auto key = ch.GenerateKey("SamplePass", piv);
    auto cipher = ch.Encrypt(key, encr_iv, "This is an ecrypted data content");
    std::cout << "Cipher:\n" << cipher << std::endl;
    auto plain = ch.Decrypt(key, encr_iv, cipher);
    std::cout << "Actual:\n" << plain << std::endl;
}

void TestTwo_2()
{
    FileChangeChecker fcc;
    auto mp = fcc.GetChangedFiles("D:\\CV");
}