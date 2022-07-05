#pragma once
#include "Common.h"
#include <ctime>

namespace CloudFileServLib
{
	namespace BL
	{
		struct FileProps
		{
			std::string FileName;
			std::string FileType;
			file_size_t ActualSize;
			std::vector<std::string> Checksums;
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