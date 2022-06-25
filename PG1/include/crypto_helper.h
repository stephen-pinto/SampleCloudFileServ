#ifndef __CRYPTO_HELPER_H__
#define __CRYPTO_HELPER_H__

#include <string>
#include "salt_generator.hpp"

namespace cmd_tool
{
    using namespace std;
    class crypto_helper
    {
    public:
        wstring encrypt(string data, string key);
        string decrypt(wstring encr_data, string key);
        string generate_hash(string password, string salt);

    private:

    };
}

#endif // __CRYPTO_HELPER_H__