#pragma once

#include "IFileBasedStorageProvider.h"
#include "FileProps.h"
#include <azure/storage/files/shares.hpp>

namespace CloudFileServLib
{
	namespace BL
	{
		class FileShareProvider : public IFileBasedStorageProvider
		{
		public:
			FileShareProvider(const std::string connectionString);
			~FileShareProvider();

			// Inherited via IFileBasedStorageProvider
			virtual std::vector<std::string> GetFileList() override;
			virtual void OpenContainer(const std::string containerName) override;
			virtual void DownloadFileTo(const std::string fileName, std::string destDir) override;
			virtual void UploadFileFrom(const std::string fileName, const std::string filePath) override;
			virtual void DownloadAllFiles(const std::string destDir, const std::string srcFolder = "") override;
			virtual FileProps GetFileProps(const std::string fileName) override;
		private:
			std::vector<std::string> GetFileListFromDir(Azure::Storage::Files::Shares::ShareDirectoryClient dirClient);
			
			const std::string connectionString;
			std::unique_ptr <Azure::Storage::Files::Shares::ShareClient> fileShareClient;
		};
	}
}