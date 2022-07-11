#pragma once

#include "Util.h"
#include "../CloudFileServLib/include/CommandLineProvider.h"
#include "../CloudFileServLib/include/BlobStorageProvider.h"

using namespace CloudFileServLib::BL;
using namespace std;

void Test1()
{
	string rootDir("D:\\Workspace\\TestSpace\\remote");
	DeleteDirectoryContents(rootDir);
	CommandLineProvider cp;
	cp.Run(0, NULL);
}