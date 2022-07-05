#pragma once

#include "IFileBasedStorageProvider.h"
#include <azure/storage/blobs.hpp>

namespace CloudFileServLib
{
	namespace BL
	{
		using namespace Azure::Storage::Blobs; 
		
		class BlobStorageProvider : public IFileBasedStorageProvider
		{
		public:
			BlobStorageProvider(const std::string& connectionString);
			~BlobStorageProvider();

			// Inherited via IFileBasedStorageProvider
			virtual std::vector<std::string> GetFileList() override;
			virtual std::string GetFile(const std::string fileName) override;
			virtual FileProps GetFileProps(const std::string fileName) override;
			virtual void OpenContainer(const std::string containerName) override;

		private:
			const std::string& connectionString;
			std::unique_ptr<BlobContainerClient> containerClient;
		};
	}
}