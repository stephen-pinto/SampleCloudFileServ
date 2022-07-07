#include "pch.h"
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include "../include/FileChangeChecker.h"

using namespace std;
using namespace boost::filesystem;
using namespace boost::algorithm;
using namespace CloudFileServLib::BL;

FileChangeChecker::FileChangeChecker(const string& rootDir) : root(rootDir)
{}

void FileChangeChecker::Initialize()
{
	path rootPath(root);
	recursive_directory_iterator dirEnd;
	FileChunker chunker(BLOCK_SIZE);

	for (recursive_directory_iterator itr(rootPath); itr != dirEnd; ++itr)
	{
		if (is_directory(itr->status()))
			continue;

		if (is_regular_file(itr->status()))
		{
			//Get file properties first
			FileProps fprops;
			fprops.FileName = itr->path().string();
			fprops.ActualSize = file_size(fprops.FileName);
			fprops.LastSync = time(0);

			chunker.OpenFile(fprops.FileName);

			//Generate checksums for each block
			while (chunker.HasMore())
			{
				auto chunk = chunker.ReadNextChunk();
				auto chkSum = cryptoHelper.GenerateChecksum(chunk);
				fprops.Checksums.push_back(chkSum);
			}

			//Add to memory store
			fileStoreState.Files.push_back(fprops);
		}
	}

	_PRINT("Printing file list after initialization:\n\n");
	for (auto item : fileStoreState.Files)
	{
		_PRINT("File: " << item.FileName);
		_PRINT("Size: " << item.ActualSize);
		_PRINT("Last Sync: " << item.LastSync);
		_PRINT("Checksums: [" << item.Checksums.size() << "]");
		for (auto chksm : item.Checksums)
		{
			_PRINT("	>>> " << chksm);
		}
	}
	_PRINT("----------------------------------------");
}

map<string, size_t> FileChangeChecker::GetChangedFiles()
{
	path root_path(root);
	recursive_directory_iterator dir_end;
	FileChunker chunker(BLOCK_SIZE);
	map<string, size_t> changeInfo;

	for (recursive_directory_iterator itr(root_path); itr != dir_end; ++itr)
	{
		if (is_directory(itr->status()))
			continue;

		if (is_regular_file(itr->status()))
		{
			FileProps fprops;
			fprops.FileName = itr->path().string();
			fprops.ActualSize = file_size(fprops.FileName);
			fprops.LastSync = time(0);

			chunker.OpenFile(fprops.FileName);

			//Generate checksums for each block
			while (chunker.HasMore())
			{
				auto chunk = chunker.ReadNextChunk();
				auto chkSum = cryptoHelper.GenerateChecksum(chunk);
				fprops.Checksums.push_back(chkSum);
			}

			_PRINT("Printing file list after change:\n\n");
			_PRINT("File: " << fprops.FileName);
			_PRINT("Size: " << fprops.ActualSize);
			_PRINT("Last Sync: " << fprops.LastSync);
			_PRINT("Checksums: [" << fprops.Checksums.size() << "]");
			for (auto chksm : fprops.Checksums)
			{
				_PRINT("	>>> " << chksm);
			}
			_PRINT("----------------------------------------");

			//Capture all the properties matching this file
			auto it = find_if(fileStoreState.Files.begin(), fileStoreState.Files.end(), [&fprops](const FileProps& fp) { return fp.FileName == fprops.FileName; });

			//If we found even one entry
			if (it != fileStoreState.Files.end())
			{
				//Get the difference if any
				auto diff = *it - fprops;

				//If the checksums are different then save the change count else ignore
				if (diff > 0)
				{
					changeInfo.insert(pair<string, size_t>(fprops.FileName, diff));

					//If there is any differnce then clear the previous info and load the new data
					it->Checksums.clear();
					it->Checksums.insert(it->Checksums.end(), fprops.Checksums.begin(), fprops.Checksums.end());
				}
			}

			fileStoreState.Files.push_back(fprops);
		}
	}

	_PRINT("Total files found: " << fileStoreState.Files.size());

	return changeInfo;
}
