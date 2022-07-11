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

	return list;
}

void FileShareProvider::DownloadFileTo(const string fileName, string destDir)
{
	if (fileShareClient.get() == NULL)
		throw runtime_error("No container opened");

	auto fileClient = fileShareClient->GetRootDirectoryClient().GetFileClient(fileName);
	auto props = fileClient.GetProperties().Value;

	//Replace any path discrepences before writing to drive
	string fullFileName(destDir + "\\" + fileName);
	replace(fullFileName.begin(), fullFileName.end(), '/', '\\');
	path fPath(fullFileName);

	//Create folder structure if not exists before writing to file
	if (!exists(fPath.parent_path()))
	{
		int res = _mkdir(fPath.parent_path().string().c_str());
	}

	//Write to the given path
	fileClient.DownloadTo(fullFileName);
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

	vector<string> fileList = GetFileList();
	for (auto fname : fileList)
	{
		DownloadFileTo(fname, destDir);
	}
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