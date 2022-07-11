#pragma once

#include "Common.h"
#include <memory>
#include "IFileBasedStorageProvider.h"
#include "BlobStorageProvider.h"

namespace CloudFileServLib
{
	namespace BL
	{
		class StorageProviderFactory
		{
		public:
			inline static IFileBasedStorageProvider* GetDefaultProvider(std::string connectionString)
			{
				return new BlobStorageProvider(connectionString);				
			}
		};
	}
}