#pragma once

#include "Common.h"
#include "FileStoreStateInfo.h"
#include <map>

namespace CloudFileServLib
{
	namespace BL
	{
		class FileChangeChecker
		{
		public:
			std::map<std::string, size_t> GetChangedFiles(const std::string& root);
		private:
			FileStoreStateInfo fileStoreState;
		};
	}
}