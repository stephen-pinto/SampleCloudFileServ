#pragma once

#include "Util.h"
#include "../CloudFileServLib/include/FileShareProvider.h"

using namespace std;
using namespace CloudFileServLib::BL;

void Test1()
{
	auto connectionString = ReadConnectionStringFromFile("ConnectionStrings.txt");
	FileShareProvider provider(connectionString);
	provider.OpenContainer("test");
	provider.GetFileList();
}