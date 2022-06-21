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
			//virtual vector<string>& GetFileList2() override;
			virtual string GetFile(string filename) override;
			virtual FileProps GetFileProps(string fileName) override;
			virtual void OpenContainer(string containerName) override;

		private:
			const string& connectionString;
			std::unique_ptr<BlobContainerClient> containerClient;
		};
	}
}