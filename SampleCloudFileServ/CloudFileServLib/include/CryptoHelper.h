#pragma once

#include "Common.h"
#include "SaltGenerator.hpp"

namespace CloudFileServLib
{
	namespace BL
	{
		using namespace std;
		class CryptoHelper
		{
		public:
			string Encrypt(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv, const string data);
			string Decrypt(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv, const string encrData);
			CryptoPP::SecByteBlock GenerateKey(const string& password, const CryptoPP::SecByteBlock& salt);
			string GenerateChecksum(const string content);
		};
	}
}
