#ifndef __CRYPTO_HELPER_H__
#define __CRYPTO_HELPER_H__

#include <string>
#include <vector>
#include "salt_generator.hpp"

//typedef std::vector<CryptoPP::byte> key_t;

namespace cmd_tool
{
    using namespace std;
    class crypto_helper
    {
    public:
        string encrypt(const SecByteBlock& key, const SecByteBlock& iv, const string data);
        string decrypt(const SecByteBlock& key, const SecByteBlock& iv, const string encr_data);
        SecByteBlock generate_key(const string &password, const SecByteBlock& salt);
        string gen_checksum(const string content);
    };
}

#endif // __CRYPTO_HELPER_H__