#pragma once

//#include <windows.h>
#include <fstream>
#include <string>
#include "../CloudFileServLib/include/BlobStorageProvider.h"

using namespace CloudFileServLib::BL;
using namespace std;

string containerName = "test";

//string GetCurrentDir()
//{
//	char buffer[1024] = { 0 };
//	GetModuleFileNameA(NULL, buffer, 1024);
//	std::string::size_type pos = string(buffer).find_last_of("\\/");
//	return string(buffer).substr(0, pos);
//}

string ReadConnectionStringFromFile(string fileName)
{
	ifstream strm;
	string content;
	strm.open(fileName);
	strm >> content;
	return content;
}

void Test1()
{
	//auto dir = GetCurrentDir();
	auto connectionString = ReadConnectionStringFromFile("ConnectionStrings.txt");

	BlobStorageProvider blobProvider(connectionString);
	blobProvider.OpenContainer("test");

	auto fileList = blobProvider.GetFileList();

	cout << "Complete list of files in the provided storage:" << endl;
	for (auto fn : fileList)
	{
		cout << fn << endl;
	}

	cout << "Properties of all files in the provided storage:" << endl;
	for (auto fn : fileList)
	{
		auto props = blobProvider.GetFileProps(fn);
		cout << props.FileName << " --- " << props.FileSize << " --- " << props.FileType << endl;
	}

	auto props = blobProvider.GetFileProps("some");
}