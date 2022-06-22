#pragma once

#include "IFileBasedStorageProvider.h"
#include <azure/storage/blobs.hpp>

namespace CloudFileServLib
{
	namespace BL
	{
		using namespace Azure::Storage::Blobs; 
		using namespace std;

		class FileStorageProvider : public IFileBasedStorageProvider
		{
		public:
			FileStorageProvider(const string& connectionString);
			~FileStorageProvider();

			// Inherited via IFileBasedStorageProvider
			virtual vector<string> GetFileList() override;
			virtual string GetFile(const string filename) override;
			virtual FileProps& GetFileProps(const string fileName) override;
			virtual void OpenContainer(const string containerName) override;

		private:
			const string& connectionString;
			std::unique_ptr<BlobContainerClient> containerClient;
		};
	}
}