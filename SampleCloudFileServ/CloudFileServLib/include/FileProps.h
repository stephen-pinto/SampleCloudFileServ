#pragma once
#include "Common.h"
#include <ctime>

namespace CloudFileServLib
{
	namespace BL
	{
		using namespace std;
		struct FileProps
		{
			string FileName;			
			string FileType;
			file_size_t ActualSize;
			vector<string> Checksums;
			time_t LastSync;

			inline bool Exists()
			{
				return doesExist;
			}

			inline void SetPresence(bool present)
			{
				doesExist = present;
			}

		private:
			bool doesExist = false;
		};
	}
}