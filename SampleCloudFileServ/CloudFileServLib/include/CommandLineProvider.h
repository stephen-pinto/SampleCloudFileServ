#pragma once
#include <string>
#include <vector>
#include "../include/common.h"

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
        };
	}
}
