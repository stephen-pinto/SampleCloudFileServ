#include "../include/crypto_helper.h"
#include <vector>
#include <include/cryptopp/pwdbased.h>

using namespace cmd_tool;
using namespace std;

vector<CryptoPP::byte> crypto_helper::generate_key(const string& password, SecByteBlock iv)
{
    //CryptoPP::byte key[SHA256::DIGESTSIZE];
    vector<CryptoPP::byte> key(SHA256::DIGESTSIZE);
    PKCS5_PBKDF2_HMAC<SHA256> pbkdf;
    //CryptoPP::byte pass[password.length()];
    //std::memcpy(pass, password.data(), password.length());
    pbkdf.DeriveKey(key.data(), key.size(), 0, (CryptoPP::byte*)password.data(), password.length(), iv.BytePtr(), iv.size(), 1024, 0.0f);

    // string hexKey;
    // HexEncoder hexencoder(new StringSink(hexKey));
    // hexencoder.Put(key.data(), key.size());
    // hexencoder.MessageEnd();
    // std::cout << hexKey << std::endl;

    return key;
}

wstring crypto_helper::encrypt(string data, string key)
{
    return L"";
}

string crypto_helper::decrypt(wstring encr_data, string key)
{
    return "";
}

string crypto_helper::generate_hash(string password, string salt)
{
    return "";
}