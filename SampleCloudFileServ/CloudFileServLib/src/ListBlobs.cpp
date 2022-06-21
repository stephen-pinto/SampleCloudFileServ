#include "pch.h"
#include "../include/ListBlobs.h"
#include <stdlib.h>
#include <azure/storage/blobs.hpp>

using namespace Azure::Storage::Blobs;

const std::string connectionString = "DefaultEndpointsProtocol=https;AccountName=spazteststorage;AccountKey=S4zLAOtL1jxBBkIdlIOIlnbX/t14Y3PA1U7PugREwK3yetB8wqX81DHggXATom0xKSqH4NGSo9Qv+AStwL1Kdw==;EndpointSuffix=core.windows.net";
const std::string container = "test";

CloudFileServLib::BL::ListBlobs::ListBlobs()
{

}

CloudFileServLib::BL::ListBlobs::~ListBlobs()
{

}

void CloudFileServLib::BL::ListBlobs::ListAll()
{
	BlobContainerClient containerClient = BlobContainerClient::CreateFromConnectionString(connectionString, container);
	containerClient.CreateIfNotExists();
	auto blobPage = containerClient.ListBlobs();
	
	for (auto blob : blobPage.Blobs)
		std::cout << "Blob item: " << blob.Name << std::endl;
	
	containerClient.Delete();
}
