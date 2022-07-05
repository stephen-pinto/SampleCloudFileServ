#pragma once
#include "Common.h"
#include "FileProps.h"

namespace CloudFileServLib
{
	namespace BL
	{
		class FileStoreStateInfo
		{
		public:
			std::vector<FileProps> Files;
		};
	}
}
