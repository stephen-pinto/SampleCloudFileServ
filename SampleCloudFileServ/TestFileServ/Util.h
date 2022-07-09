#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <boost/filesystem.hpp>
#include "../CloudFileServLib/include/BlobStorageProvider.h"

using namespace std;

string ReadConnectionStringFromFile(string fileName)
{
	ifstream strm;
	string content;
	strm.open(fileName);
	strm >> content;
	return content;
}

void DeleteDirectoryContents(const std::string& dirPath)
{
	namespace fs = boost::filesystem;
	fs::path pathToRemove(dirPath);
	for (fs::directory_iterator endDirItr, it(pathToRemove); it != endDirItr; ++it) {
		fs::remove_all(it->path());
	}
}

//string GetCurrentDir()
//{
//	char buffer[1024] = { 0 };
//	GetModuleFileNameA(NULL, buffer, 1024);
//	std::string::size_type pos = string(buffer).find_last_of("\\/");
//	return string(buffer).substr(0, pos);
//}