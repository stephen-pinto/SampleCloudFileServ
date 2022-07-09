#pragma once

#include <map>
#include "Common.h"
#include "FileStoreStateInfo.h"
#include "FileChunker.h"
#include "CryptoHelper.h"
#include "ReadOnlyFileProps.h"

namespace CloudFileServLib
{
	namespace BL
	{
		class FileChangeChecker
		{
		public:
			FileChangeChecker(const std::string root);
			void Initialize();
			std::map<std::string, size_t> GetChangedFiles();
			std::vector<ReadOnlyFileProps> GetSyncdFiles();

		private:
			const string root;
			FileStoreStateInfo fileStoreState;
			CryptoHelper cryptoHelper;
		};
	}
}