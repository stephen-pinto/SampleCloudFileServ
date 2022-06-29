#ifndef __SALT_GENERATOR_H__
#define __SALT_GENERATOR_H__

#include <string>
#include <include/cryptopp/cryptlib.h>
#include <include/cryptopp/osrng.h>
#include <include/cryptopp/modes.h>
#include <include/cryptopp/files.h>
#include <include/cryptopp/hex.h>

namespace cmd_tool
{
    using namespace std;
    using namespace CryptoPP;

    class salt_generator
    {
    public:
        inline string generate_salt(size_t len_in_bytes);
        inline SecByteBlock generate_iv(size_t len_in_bytes);
        inline string generate_random_str(size_t len_in_bytes);
    };
}

/*
Below function generates a random salt based on random data generated using AutoSeededRandomPool.
*/
std::string cmd_tool::salt_generator::generate_salt(size_t len_in_bytes)
{
    AutoSeededRandomPool prng;
    string hex_key;
    HexEncoder hexencoder(new StringSink(hex_key));
    SecByteBlock iv(len_in_bytes);
    prng.GenerateBlock(iv, iv.size());
    hexencoder.Put(iv, iv.size());
    return hex_key;
}

/*
Below function generates a random IV based on random data generated using AutoSeededRandomPool.
*/
CryptoPP::SecByteBlock cmd_tool::salt_generator::generate_iv(size_t len_in_bytes)
{
    AutoSeededRandomPool rndpool;
    string hexKey;
    SecByteBlock iv(len_in_bytes);
    rndpool.GenerateBlock(iv, iv.size());
    return iv;
}

/*
Below function generates a random string based on random data generated from pool of characters.
*/
std::string cmd_tool::salt_generator::generate_random_str(size_t len_in_bytes)
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    std::string str;
    str.reserve(len_in_bytes);

    for (size_t i = 0; i < len_in_bytes; ++i) 
        str += alphanum[rand() % (sizeof(alphanum) - 1)];
    
    return str;
}

#endif // __SALT_GENERATOR_H__