#pragma once
#include <memory>
#include "Common.h"
#include "FileChangeChecker.h"
#include "IFileBasedStorageProvider.h"
#include "BlobStorageProvider.h"

namespace CloudFileServLib
{
	namespace BL
	{
        class CommandLineProvider
        {
        public:
            CommandLineProvider();
            int Run(int argc, char** argv);

        private:
            int HandleCommand(const std::string command);
            int HandleBinaryCommand(std::vector<std::string> params);
            std::string ServerPath(std::string actualPath);

            std::string rootDir;
            std::string cacheDir;
            std::unique_ptr<FileChangeChecker> fileChangeChecker;
            std::unique_ptr<BlobStorageProvider> storageProvider;
        };
	}
}
