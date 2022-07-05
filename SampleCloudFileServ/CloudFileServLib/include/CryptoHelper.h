#pragma once

#include "Common.h"
#include "SaltGenerator.hpp"

namespace CloudFileServLib
{
	namespace BL
	{
		class CryptoHelper
		{
		public:
			std::string Encrypt(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv, const std::string data);
			std::string Decrypt(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv, const std::string encrData);
			CryptoPP::SecByteBlock GenerateKey(const std::string& password, const CryptoPP::SecByteBlock& salt);
			std::string GenerateChecksum(const std::string content);
		};
	}
}
