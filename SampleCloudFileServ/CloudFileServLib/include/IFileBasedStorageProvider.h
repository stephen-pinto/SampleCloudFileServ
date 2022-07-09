#pragma once
#include <stdlib.h>
#include <vector>
#include "Common.h"
#include "FileProps.h"

namespace CloudFileServLib
{
	namespace BL
	{
		class IFileBasedStorageProvider
		{
			virtual std::vector<std::string> GetFileList() = 0;
			virtual void OpenContainer(const std::string containerName) = 0;
			virtual std::string DownloadFile(const std::string fileName) = 0;
			virtual void UploadFile(const std::string fileName, const std::string content) = 0;
			virtual FileProps GetFileProps(const std::string fileName) = 0;
		};
	}
}