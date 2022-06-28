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
    };
}

std::string cmd_tool::salt_generator::generate_salt(size_t len_in_bytes)
{
    AutoSeededRandomPool prng;
    string hexKey;
    HexEncoder hexencoder(new StringSink(hexKey));
    SecByteBlock iv(len_in_bytes);
    prng.GenerateBlock(iv, iv.size());
    hexencoder.Put(iv, iv.size());
    return hexKey;
}

CryptoPP::SecByteBlock cmd_tool::salt_generator::generate_iv(size_t len_in_bytes)
{
    AutoSeededRandomPool prng;
    string hexKey;
    SecByteBlock iv(len_in_bytes);
    prng.GenerateBlock(iv, iv.size());
    return iv;
}

/*
std::string cmd_tool::salt_generator::generate_salt(size_t len_in_bytes)
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
*/

#endif // __SALT_GENERATOR_H__