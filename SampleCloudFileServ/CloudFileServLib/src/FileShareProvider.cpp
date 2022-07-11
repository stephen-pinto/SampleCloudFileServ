#include "pch.h"
#include "..\include\FileShareProvider.h"
#include <ostream>
#include <fstream>
#include <stdlib.h>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/directory.hpp>
#include <boost/filesystem/operations.hpp>
#include <direct.h>

using namespace CloudFileServLib::BL;
using namespace Azure::Storage::Files::Shares;
using namespace Azure::Storage::Files::Shares::Models;
using namespace Azure::Core::IO;
using namespace std;
using namespace boost::filesystem;

CloudFileServLib::BL::FileShareProvider::FileShareProvider(const string connectionString) : connectionString(connectionString)
{
}

CloudFileServLib::BL::FileShareProvider::~FileShareProvider()
{
	fileShareClient.release();
}

void FileShareProvider::OpenContainer(const string containerName)
{
	auto client = ShareClient::CreateFromConnectionString(connectionString, containerName);
	fileShareClient = make_unique<ShareClient>(client);
}

vector<string> FileShareProvider::GetFileListFromDir(ShareDirectoryClient dirClient)
{
	vector<string> list;
	auto resp = dirClient.ListFilesAndDirectories();

	for (auto file : resp.Files)
	{
		if (!resp.DirectoryPath.empty())
			list.push_back(resp.DirectoryPath + "/" + file.Name);
		else
			list.push_back(file.Name);
	}

	for (auto dir : resp.Directories)
	{
		vector<string> dirList = GetFileListFromDir(dirClient.GetSubdirectoryClient(dir.Name));
		list.insert(list.end(), dirList.begin(), dirList.end());
	}

	return list;
}

vector<string> CloudFileServLib::BL::FileShareProvider::GetFileList()
{
	vector<string> list;
	auto rootClient = fileShareClient->GetRootDirectoryClient();

	list = GetFileListFromDir(rootClient);

	//auto x = rootClient.GetSubdirectoryClient("small/vsmall");
	//auto url = x.GetUrl();

	//auto resp = rootClient.ListFilesAndDirectories();
	//auto handles = rootClient.ListHandles();
	//
	//while (resp.HasPage())
	//{
	//	_PRINT("----------------------------");
	//	for (auto dir : resp.Directories)
	//	{
	//		_PRINT("[DIR] Name: " << dir.Name);
	//	}

	//	for (auto file : resp.Files)
	//	{
	//		_PRINT("[FILE] Name: " << file.Name);
	//		_PRINT("[FILE] Size: " << file.Details.FileSize);
	//	}
	//	_PRINT("----------------------------");

	//	resp.MoveToNextPage();
	//}

	////auto fclient = rootClient.GetFileClient(resp.Directories[0].Name);
	//auto dclient = rootClient.GetSubdirectoryClient(resp.Directories[0].Name);

	for (auto item : list)
	{
		_PRINT("[FILE] Name: " << item);
	}

	return list;
}

void FileShareProvider::DownloadFileTo(const string fileName, string destDir)
{
	if (fileShareClient.get() == NULL)
		throw runtime_error("No container opened");
}

void FileShareProvider::UploadFileFrom(const string fileName, const string filePath)
{
	if (fileShareClient.get() == NULL)
		throw runtime_error("No container opened");
}

void FileShareProvider::DownloadAllFiles(const string destDir, const string srcFolder)
{
	if (fileShareClient.get() == NULL)
		throw runtime_error("No container opened");
}

FileProps FileShareProvider::GetFileProps(const string fileName)
{
	if (fileShareClient.get() == NULL)
		throw runtime_error("No container opened");

	return FileProps();
}

//vector<string> FileShareProvider::GetFileListFromDir(DirectoryItem dirPath)
//{
//    
//}