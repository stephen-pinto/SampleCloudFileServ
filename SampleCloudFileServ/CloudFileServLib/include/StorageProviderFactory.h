#pragma once

#include "Common.h"
#include <memory>
#include "IFileBasedStorageProvider.h"
#include "BlobStorageProvider.h"
#include "FileShareProvider.h"

namespace CloudFileServLib
{
	namespace BL
	{
		enum FileBasedStorageType
		{
			Blobs,
			FileShares
		};

		class StorageProviderFactory
		{
		public:
			inline static IFileBasedStorageProvider* GetDefaultProvider(std::string connectionString, FileBasedStorageType type)
			{
				switch (type)
				{
				case CloudFileServLib::BL::FileShares:
					break;
					return new FileShareProvider(connectionString);
				case CloudFileServLib::BL::Blobs:
				default:
					return new BlobStorageProvider(connectionString);
					break;
				}
			}
		};
	}
}