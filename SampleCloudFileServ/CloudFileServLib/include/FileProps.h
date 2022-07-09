#pragma once
#include "Common.h"
#include "IPrintable.h"
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>

namespace CloudFileServLib
{
	namespace BL
	{
		struct FileProps : public IPrintable
		{
			std::string FileName;
			std::string FileType;
			file_size_t ActualSize = 0;
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
				size_t max = (tarSize > curSize) ? tarSize : curSize;

				size_t i;
				for (i = 0; i < len; i++)
				{
					if (i <= curSize && i <= tarSize)
					{
						if (fprops.Checksums[i] != Checksums[i])
							break;
					}
					else
						break;
				}

				if (curSize == tarSize == i)
					return 0;

				//Largest number minus initial similar items = delta
				return std::abs((long long)max - (long long)i);
			}

			std::string ToString()
			{
				std::ostringstream stringStream;
				stringStream << "FileName: `" << FileName << "` | Size: `" << ActualSize << "` bytes" << "` | Type: `" << FileType << "`";
				return stringStream.str();
			}

		private:
			bool doesExist = false;
		};
	}
}