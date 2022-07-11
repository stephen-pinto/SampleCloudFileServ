#include "pch.h"
#include "../include/CryptoHelper.h"
#include <cryptopp/pwdbased.h>
#include <cryptopp/rijndael.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/eax.h>
#include <cryptopp/base64.h>

using namespace CloudFileServLib::BL;
using namespace CryptoPP;
using namespace std;

//TODO: Make it more larger as per performance
#define PBKDF2_ITERATIONS 1024

string CloudFileServLib::BL::CryptoHelper::Encrypt(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv, const string data)
{
    string encrText;

    try
    {
        //Encrypt the content using AES algorithm
        //We could also use CBC but we chose a more secure EAX
        EAX<AES>::Encryption encr;
        encr.SetKeyWithIV(key, key.size(), iv);
        StringSource str(data, true, new AuthenticatedEncryptionFilter(encr, new StringSink(encrText)));
    }
    catch (const Exception& e)
    {
        cerr << e.what() << '\n';
        throw e;
    }

    return encrText;
}

string CloudFileServLib::BL::CryptoHelper::Decrypt(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv, const string encrData)
{
    string actText;

    try
    {
        //Decrypt the content using AES algorithm
        //We could also use CBC but we chose a more secure EAX
        EAX<AES>::Decryption decr;
        decr.SetKeyWithIV(key, key.size(), iv);
        StringSource str(encrData, true, new AuthenticatedDecryptionFilter(decr, new StringSink(actText)));
    }
    catch (const Exception& e)
    {
        std::cerr << e.what() << '\n';
        throw e;
    }

    return actText;
}

CryptoPP::SecByteBlock CloudFileServLib::BL::CryptoHelper::GenerateKey(const string& password, const CryptoPP::SecByteBlock& salt)
{
    // Generate a key based on PBKDF2 key strengthening alogorithm
    SecByteBlock key(SHA256::DIGESTSIZE);
    PKCS5_PBKDF2_HMAC<SHA256> pbkdf;
    pbkdf.DeriveKey(key.data(), key.size(), 0, (CryptoPP::byte*)password.data(), password.length(), salt.BytePtr(), salt.size(), PBKDF2_ITERATIONS, 0.0f);
    return key;
}

string CloudFileServLib::BL::CryptoHelper::GenerateChecksum(const string content)
{
    string hash;
    SHA256 sha256;
    StringSource ssrc(content, true,
        new HashFilter(sha256,
            new Base64Encoder(
                new StringSink(hash))));

    return hash;
}

string CloudFileServLib::BL::CryptoHelper::GenerateChecksum(const vector<byte> content)
{
    string hash;
    SHA256 sha256;
    VectorSource vsrc(content, true,
        new HashFilter(sha256,
            new Base64Encoder(
                new StringSink(hash))));

    return hash;
}
