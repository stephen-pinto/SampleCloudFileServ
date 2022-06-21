#include "pch.h"
#include "../include/IFileBasedStorageProvider.h"
#include "../include/FileStorageProvider.h"
using namespace CloudFileServLib::BL;
using namespace std;

FileStorageProvider::FileStorageProvider(const string& connStr) : connectionString(connStr)
{
}

FileStorageProvider::~FileStorageProvider()
{
}

void CloudFileServLib::BL::FileStorageProvider::OpenContainer(string containerName)
{
	//Initialize the contianerClient
	auto client = BlobContainerClient::CreateFromConnectionString(connectionString, containerName);
	containerClient = make_unique<BlobContainerClient>(client);
	containerClient->CreateIfNotExists();
}

vector<string> CloudFileServLib::BL::FileStorageProvider::GetFileList()
{
	vector<string> fileList;
	auto blobPage = containerClient->ListBlobs();
	for (auto blob : blobPage.Blobs)
	{
		fileList.push_back(blob.Name);
	}

	return fileList;
}

string CloudFileServLib::BL::FileStorageProvider::GetFile(string filename)
{
	return string();
}

FileProps CloudFileServLib::BL::FileStorageProvider::GetFileProps(string fileName)
{
	return FileProps();
}
