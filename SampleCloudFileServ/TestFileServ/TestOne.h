#pragma once

#include "../CloudFileServLib/include/BlobStorageProvider.h"
using namespace CloudFileServLib::BL;
using namespace std;

string connectionString = "DefaultEndpointsProtocol=https;AccountName=spazteststorage;AccountKey=S4zLAOtL1jxBBkIdlIOIlnbX/t14Y3PA1U7PugREwK3yetB8wqX81DHggXATom0xKSqH4NGSo9Qv+AStwL1Kdw==;EndpointSuffix=core.windows.net";
string containerName = "test";

void Test1()
{
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
}