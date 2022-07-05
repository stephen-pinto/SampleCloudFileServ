#pragma once

#include "Common.h"
#include <cryptopp/cryptlib.h>
#include <cryptopp/osrng.h>
#include <cryptopp/modes.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>

namespace CloudFileServLib
{
	namespace BL
	{
		using namespace std;
		
		class SaltGenerator
		{
		public:
			inline string GenerateSalt(size_t lenBytes);
			inline CryptoPP::SecByteBlock GenerateIV(size_t lenBytes);
			inline string GenerateRandomString(size_t lenBytes);
		};

		/*
		Below function generates a random salt based on random data generated using AutoSeededRandomPool.
		*/
		string SaltGenerator::GenerateSalt(size_t lenBytes)
		{
			CryptoPP::AutoSeededRandomPool prng;
			string hexKey;
			CryptoPP::HexEncoder hexencoder(new CryptoPP::StringSink(hexKey));
			CryptoPP::SecByteBlock iv(lenBytes);
			prng.GenerateBlock(iv, iv.size());
			hexencoder.Put(iv, iv.size());
			return hexKey;
		}

		/*
		Below function generates a random IV based on random data generated using AutoSeededRandomPool.
		*/
		CryptoPP::SecByteBlock SaltGenerator::GenerateIV(size_t lenBytes)
		{
			CryptoPP::AutoSeededRandomPool rndpool;
			string hexKey;
			CryptoPP::SecByteBlock iv(lenBytes);
			rndpool.GenerateBlock(iv, iv.size());
			return iv;
		}

		/*
		Below function generates a random string based on random data generated from pool of characters.
		*/
		std::string SaltGenerator::GenerateRandomString(size_t lenBytes)
		{
			static const char alphaNum[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";

			std::string str;
			str.reserve(lenBytes);

			for (size_t i = 0; i < lenBytes; ++i)
				str += alphaNum[rand() % (sizeof(alphaNum) - 1)];

			return str;
		}
	}
}