#pragma once
#include <memory>
#include "Common.h"
#include "FileChangeChecker.h"

namespace CloudFileServLib
{
	namespace BL
	{
        class CommandLineProvider
        {
        public:
            int Run(int argc, char** argv);
        private:
            int HandleCommand(const std::string command);
            int HandleBinaryCommand(std::vector<std::string> params);

            std::string rootDir;
            std::string cacheDir;
            std::unique_ptr<FileChangeChecker> fileChangeChecker;
        };
	}
}
