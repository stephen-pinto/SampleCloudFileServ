#pragma once
#include "Common.h"
#include <stdlib.h>
#include <vector>

namespace CloudFileServLib
{
	namespace BL
	{
		using namespace std;
		struct FileProps
		{
			string fileName;
			string filePath;
			size_t fileSize;
		};

		class IFileBasedStorageProvider
		{
			virtual vector<string> GetFileList() = 0;
			virtual void OpenContainer(string containerName) = 0;
			virtual string GetFile(string filename) = 0;
			virtual FileProps GetFileProps(string fileName) = 0;
		};
	}
}