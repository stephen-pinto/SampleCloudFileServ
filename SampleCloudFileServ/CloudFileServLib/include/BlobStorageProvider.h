#pragma once

#include "Common.h"
#include "IFileBasedStorageProvider.h"
#include <azure/storage/blobs.hpp>

namespace CloudFileServLib
{
	namespace BL
	{
		class BlobStorageProvider : public IFileBasedStorageProvider
		{
		public:
			BlobStorageProvider(const std::string connectionString);
			~BlobStorageProvider();

			// Inherited via IFileBasedStorageProvider
			virtual std::vector<std::string> GetFileList() override;
			virtual std::string DownloadFile(const std::string fileName);
			virtual void DownloadFileTo(const std::string destDir, const std::string fileName) override;
			virtual void UploadFile(const std::string fileName, const std::string content);
			virtual void UploadFileFrom(const std::string fileName, const std::string filePath) override;
			virtual FileProps GetFileProps(const std::string fileName) override;
			virtual void DownloadAllFiles(const std::string destDir, const std::string srcFolder = "") override;
			virtual void OpenContainer(const std::string containerName) override;

		private:
			const std::string connectionString;
			std::unique_ptr<Azure::Storage::Blobs::BlobContainerClient> containerClient;
		};
	}
}