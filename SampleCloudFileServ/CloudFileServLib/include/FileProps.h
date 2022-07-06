#pragma once
#include "Common.h"
#include <ctime>
#include <cstdlib>

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

			inline size_t operator -(FileProps fprops)
			{
				size_t tarSize = fprops.Checksums.size();
				size_t curSize = Checksums.size();
				size_t len = (tarSize > curSize) ? curSize : tarSize;

				size_t i;
				for (i = 1; i <= len; i++)
				{
					if (i <= curSize && i <= tarSize)
					{
						if (fprops.Checksums[i] == Checksums[i])
							continue;
					}
				}

				if (curSize == tarSize == i)
					return 0;

				//Largest number minus initial similar items = delta
				return std::abs(std::abs((long long)(curSize - tarSize)) - (long long)i);
			}

		private:
			bool doesExist = false;
		};
	}
}