#ifndef __CRYPTO_HELPER_H__
#define __CRYPTO_HELPER_H__

#include <string>
#include "salt_generator.hpp"
typedef vector<CryptoPP::byte> key_t;

namespace cmd_tool
{
    using namespace std;
    class crypto_helper
    {
    public:
        wstring encrypt(key_t key, string data);
        string  decrypt(key_t key, wstring encr_data);
        key_t generate_key(const string &password, SecByteBlock salt);

    private:

    };
}

#endif // __CRYPTO_HELPER_H__