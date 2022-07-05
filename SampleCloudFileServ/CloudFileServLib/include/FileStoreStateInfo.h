#pragma once
#include "Common.h"
#include "FileProps.h"

namespace CloudFileServLib
{
	namespace BL
	{
		using namespace std;
		class FileStoreStateInfo
		{
		public:
			vector<FileProps> Files;
		};
	}
}
