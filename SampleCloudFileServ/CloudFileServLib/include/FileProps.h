#pragma once
#include "Common.h"

namespace CloudFileServLib
{
	namespace BL
	{
		using namespace std;
		struct FileProps
		{
			string FileName;
			string FileType;
			int64_t FileSize;

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