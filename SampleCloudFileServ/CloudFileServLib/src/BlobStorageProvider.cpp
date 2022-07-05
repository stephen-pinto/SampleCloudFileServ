#include "pch.h"
#include "../include/IFileBasedStorageProvider.h"
#include "../include/BlobStorageProvider.h"
using namespace Azure::Storage::Blobs::Models;
using namespace CloudFileServLib::BL;
using namespace std;

BlobStorageProvider::BlobStorageProvider(const string& connStr) : connectionString(connStr)
{
}

BlobStorageProvider::~BlobStorageProvider()
{
	containerClient.release();
}

void CloudFileServLib::BL::BlobStorageProvider::OpenContainer(const string containerName)
{
	//Initialize the contianerClient
	auto client = BlobContainerClient::CreateFromConnectionString(connectionString, containerName);
	containerClient = make_unique<BlobContainerClient>(client);	
}

vector<string> CloudFileServLib::BL::BlobStorageProvider::GetFileList()
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

string CloudFileServLib::BL::BlobStorageProvider::GetFile(const string fileName)
{
	if (containerClient.get() == NULL)
		throw runtime_error("No container opened");

	auto blobClient = containerClient->GetBlockBlobClient(fileName);
	auto props = blobClient.GetProperties().Value;
	
	vector<uint8_t> blobFile(props.BlobSize);
	blobClient.DownloadTo(blobFile.data(), blobFile.size());

	return string(blobFile.begin(), blobFile.end());
}

FileProps CloudFileServLib::BL::BlobStorageProvider::GetFileProps(const string fileName)
{
	if (containerClient.get() == NULL)
		throw runtime_error("No container opened");
	
	FileProps fp;
	BlobProperties props;
	try
	{
		auto blobClient = containerClient->GetBlockBlobClient(fileName);
		props = blobClient.GetProperties().Value;
	}
	catch (Azure::Storage::StorageException e)
	{
		if (e.StatusCode == Azure::Core::Http::HttpStatusCode::NotFound)
			return fp;		
	}

	fp.SetPresence(true);
	fp.FileName = fileName;
	fp.FileType = props.BlobType.ToString();
	fp.ActualSize = props.BlobSize;
	
	return fp;
}
