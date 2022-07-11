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
		class StorageProviderFactory
		{
		public:
			inline static IFileBasedStorageProvider* GetDefaultProvider(std::string connectionString, int index)
			{
				if (index == 0)
					return new BlobStorageProvider(connectionString);
				else
					return new FileShareProvider(connectionString);
			}
		};
	}
}