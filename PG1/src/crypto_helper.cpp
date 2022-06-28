#include "../include/crypto_helper.h"
#include <vector>
#include <include/cryptopp/pwdbased.h>
#include <include/cryptopp/rijndael.h>
#include <include/cryptopp/cryptlib.h>
#include <include/cryptopp/modes.h>
#include <include/cryptopp/osrng.h>
#include <include/cryptopp/eax.h>

using namespace cmd_tool;
using namespace std;

//TODO: Make it more larger as per performance
#define PBKDF2_ITERATIONS 1024

SecByteBlock crypto_helper::generate_key(const string& password, const SecByteBlock& iv)
{
    //Generate a key based on PBKDF2 key strengthening alogorithm
    SecByteBlock key(SHA256::DIGESTSIZE);
    PKCS5_PBKDF2_HMAC<SHA256> pbkdf;
    pbkdf.DeriveKey(key.data(), key.size(), 0, (CryptoPP::byte*)password.data(), password.length(), iv.BytePtr(), iv.size(), PBKDF2_ITERATIONS, 0.0f);
    return key;
}

string crypto_helper::encrypt(const SecByteBlock& key, const SecByteBlock& iv, const string data)
{
    string encr_text;

    try
    {
        //Encrypt the content using AES algorithm
        EAX<AES>::Encryption encr;
        encr.SetKeyWithIV(key, key.size(), iv);
        StringSource str(data, true, new AuthenticatedEncryptionFilter(encr, new StringSink(encr_text)));
    }
    catch(const Exception& e)
    {
        std::cerr << e.what() << '\n';
        throw e;
    }

    return encr_text;
}

string crypto_helper::decrypt(const SecByteBlock& key, const SecByteBlock& iv, string encr_data)
{
    string act_text;

    try
    {
        //Decrypt the content using AES algorithm
        EAX<AES>::Decryption decr;
        decr.SetKeyWithIV(key, key.size(), iv);
        StringSource str(encr_data, true, new AuthenticatedDecryptionFilter(decr, new StringSink(act_text)));
    }
    catch(const Exception& e)
    {
        std::cerr << e.what() << '\n';
        throw e;
    }

    return act_text;
}
