#pragma once
#include <stdlib.h>
#include <vector>
#include "Common.h"
#include "FileProps.h"

namespace CloudFileServLib
{
	namespace BL
	{
		using namespace std;
		class IFileBasedStorageProvider
		{
			virtual vector<string> GetFileList() = 0;
			virtual void OpenContainer(const string containerName) = 0;
			virtual string GetFile(const string filename) = 0;
			virtual FileProps& GetFileProps(const string fileName) = 0;
		};
	}
}