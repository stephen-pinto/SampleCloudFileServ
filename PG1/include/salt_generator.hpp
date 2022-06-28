#ifndef __SALT_GENERATOR_H__
#define __SALT_GENERATOR_H__

#include <string>
#include <gcrypt.h>

namespace cmd_tool
{
    using namespace std;

    class salt_generator
    {
    public:
        inline string generate_salt(size_t len_in_bytes);
    };
}

std::string cmd_tool::salt_generator::generate_salt(size_t len_in_bytes)
{
    auto salt_c = gcry_random_bytes(len_in_bytes, GCRY_STRONG_RANDOM);
    std::string salt((char*)salt_c);
    return salt;
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