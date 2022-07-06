#pragma once

#include <map>
#include "Common.h"
#include "FileStoreStateInfo.h"
#include "FileChunker.h"
#include "CryptoHelper.h"

namespace CloudFileServLib
{
	namespace BL
	{
		class FileChangeChecker
		{
		public:
			FileChangeChecker(const std::string& root);
			void Initialize();
			std::map<std::string, size_t> GetChangedFiles();

		private:
			const string& root;
			FileStoreStateInfo fileStoreState;
			CryptoHelper cryptoHelper;
		};
	}
}