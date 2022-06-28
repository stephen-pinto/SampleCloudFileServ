#include "../include/crypto_helper.h"
#include <vector>
#include <include/cryptopp/pwdbased.h>

using namespace cmd_tool;
using namespace std;

//TODO: Make it more larger as per performance
#define PBKDF2_ITERATIONS 1024

key_t crypto_helper::generate_key(const string& password, SecByteBlock iv)
{
    key_t key(SHA256::DIGESTSIZE);
    PKCS5_PBKDF2_HMAC<SHA256> pbkdf;
    pbkdf.DeriveKey(key.data(), key.size(), 0, (CryptoPP::byte*)password.data(), password.length(), iv.BytePtr(), iv.size(), PBKDF2_ITERATIONS, 0.0f);
    return key;
}

wstring crypto_helper::encrypt(key_t key, string data)
{
    return L"";    
}

string crypto_helper::decrypt(key_t key, wstring encr_data)
{
    return "";
}
