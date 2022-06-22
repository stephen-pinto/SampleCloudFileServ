#include "pch.h"
#include "../include/IFileBasedStorageProvider.h"
#include "../include/FileStorageProvider.h"
using namespace Azure::Storage::Blobs::Models;
using namespace CloudFileServLib::BL;
using namespace std;

FileStorageProvider::FileStorageProvider(const string& connStr) : connectionString(connStr)
{
}

FileStorageProvider::~FileStorageProvider()
{	
}

void CloudFileServLib::BL::FileStorageProvider::OpenContainer(const string containerName)
{
	//Initialize the contianerClient
	auto client = BlobContainerClient::CreateFromConnectionString(connectionString, containerName);
	containerClient = make_unique<BlobContainerClient>(client);
	containerClient->CreateIfNotExists();
}

vector<string> CloudFileServLib::BL::FileStorageProvider::GetFileList()
{
	if (containerClient.get() == NULL)
		throw runtime_error("No container opened");

	vector<string> fileList;
	auto blobPage = containerClient->ListBlobs();
	for (auto blob : blobPage.Blobs)
	{
		fileList.push_back(blob.Name);
	}

	return fileList;
}

string CloudFileServLib::BL::FileStorageProvider::GetFile(const string filename)
{
	if (containerClient.get() == NULL)
		throw runtime_error("No container opened");

	auto blobClient = containerClient->GetBlockBlobClient(filename);
	auto props = blobClient.GetProperties().Value;
	
	vector<uint8_t> blobFile(props.BlobSize);
	blobClient.DownloadTo(blobFile.data(), blobFile.size());

	return string(blobFile.begin(), blobFile.end());
}

FileProps& CloudFileServLib::BL::FileStorageProvider::GetFileProps(const string fileName)
{
	if (containerClient.get() == NULL)
		throw runtime_error("No container opened");
	
	FileProps fp;
	
	auto blobPage = containerClient->ListBlobs();
	for (BlobItem blob : blobPage.Blobs)
	{
		if (blob.Name == fileName && !blob.IsDeleted)
		{
			fp.SetPresence(true);
			fp.FileName = blob.Name;
			fp.FileType = blob.BlobType.ToString();
			fp.FileSize = blob.BlobSize;
		}
	}
	return fp;
}
