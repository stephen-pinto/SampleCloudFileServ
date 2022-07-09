#pragma once

//#include <windows.h>
#include <fstream>
#include <string>
#include <boost/filesystem.hpp>
#include <algorithm>
#include <chrono>
#include "../CloudFileServLib/include/BlobStorageProvider.h"

using namespace boost::filesystem;
using namespace CloudFileServLib::BL;
using namespace std;
using namespace std::chrono;

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
		cout << props.FileName << " --- " << props.ActualSize << " --- " << props.FileType << endl;
	}

	auto props = blobProvider.GetFileProps("some");
}

void Test2()
{
	auto connectionString = ReadConnectionStringFromFile("ConnectionStrings.txt");
	BlobStorageProvider blobProvider(connectionString);
	blobProvider.OpenContainer("test");

	auto fileList = blobProvider.GetFileList();

	cout << "Complete list of files in the provided storage:" << endl;
	for (auto fn : fileList)
	{
		path fpath(fn);
		auto f = fpath.leaf().string();
		auto p = fpath.parent_path().string();
		cout << fn << endl;
	}

	blobProvider.DownloadFileTo(fileList[6], "D:\\TestSpace\\TestFiles\\remote");
}

void Test3()
{
	auto connectionString = ReadConnectionStringFromFile("ConnectionStrings.txt");
	
	BlobStorageProvider blobProvider(connectionString);
	blobProvider.OpenContainer("test");

	auto fileList = blobProvider.GetFileList();

	cout << "Complete list of files in the provided storage:" << endl;
	for (auto fn : fileList)
	{
		path fpath(fn);
		auto f = fpath.leaf().string();
		auto p = fpath.parent_path().string();
		cout << fn << endl;
	}

	auto start = high_resolution_clock::now();
	blobProvider.DownloadAllFiles("D:\\TestSpace\\TestFiles\\remote");
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	_PRINT("Time taken for downloading with old method: " << duration.count() / 1024.0 << " seconds");
}

void DeleteDirectoryContents(const std::string& dirPath)
{
	namespace fs = boost::filesystem;
	fs::path pathToRemove(dirPath);
	for (fs::directory_iterator endDirItr, it(pathToRemove); it != endDirItr; ++it) {
		fs::remove_all(it->path());
	}
}

void Test4()
{
	auto connectionString = ReadConnectionStringFromFile("ConnectionStrings.txt");
	auto testRoot("D:\\TestSpace\\TestFiles\\remote");

	{
		BlobStorageProvider blobProvider(connectionString);
		blobProvider.OpenContainer("test");

		auto start = high_resolution_clock::now();
		blobProvider.DownloadAllFiles(testRoot);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(stop - start);
		_PRINT("Time taken for downloading with old method: " << duration.count() / 1024.0 << " seconds");
	}

	DeleteDirectoryContents(testRoot);

	{
		BlobStorageProvider blobProvider(connectionString);
		blobProvider.OpenContainer("test");

		auto start = high_resolution_clock::now();
		blobProvider.DownloadAllFiles2(testRoot);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(stop - start);
		_PRINT("Time taken for downloading with new method: " << duration.count() / 1024.0 << " seconds");
	}
}