#include "../include/crypto_helper.h"
#include <gcrypt.h>
#include <vector>

using namespace cmd_tool;
using namespace std;

#define AES_256_KEY_SIZE    32
#define AES_256_BLOCK_SIZE  16
#define HMAC_KEY_SIZE       64
#define KDF_ITERATIONS      50000
#define KDF_SALT_SIZE       128
#define KDF_KEY_SIZE        AES_256_KEY_SIZE + HMAC_KEY_SIZE

vector<u_char> get_key()
{
    u_char kdf_salt[KDF_SALT_SIZE];
    u_char kdf_key[KDF_KEY_SIZE];

    //Generate 128 bit salt
    gcry_create_nonce(kdf_salt, KDF_SALT_SIZE);    
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