#include "pch.h"
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include "../include/FileChangeChecker.h"

using namespace std;
using namespace boost::filesystem;
using namespace boost::algorithm;
using namespace CloudFileServLib::BL;

FileChangeChecker::FileChangeChecker(const string rootDir) : root(rootDir)
{}

/// <summary>
/// Generates initial list of the file changes to compare with future changes.
/// </summary>
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

	_PRINT("Total files: " << fileStoreState.Files.size());
}

/// <summary>
/// Gets the latest changes of files and compares with previous to determined changed blocks.
/// </summary>
/// <returns></returns>
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

			//Capture all the properties matching this file
			auto it = find_if(fileStoreState.Files.begin(), fileStoreState.Files.end(), [&fprops](const FileProps& fp) { return fp.FileName == fprops.FileName; });

			//If we found our entry
			if (it != fileStoreState.Files.end())
			{
				//Get the difference if any
				auto diff = *it - fprops;

				//If the checksums are different then save the change count else ignore
				if (diff > 0)
				{
					changeInfo.insert(pair<string, size_t>(fprops.FileName, diff));

					//If there is any differnce then clear the previous info and load the new checksums
					it->Checksums.clear();
					it->Checksums.insert(it->Checksums.end(), fprops.Checksums.begin(), fprops.Checksums.end());
				}
			}
			else
			{
				//If we didn't find this file then add it to the store and notify as changed			
				fileStoreState.Files.push_back(fprops);
				changeInfo.insert(pair<string, size_t>(fprops.FileName, fprops.Checksums.size()));
			}
		}
	}

	_PRINT("Total files: " << fileStoreState.Files.size());

	return changeInfo;
}

std::vector<ReadOnlyFileProps> FileChangeChecker::GetSyncdFiles()
{
	std::vector<ReadOnlyFileProps> files;

	for (auto& item : fileStoreState.Files)
	{
		ReadOnlyFileProps rfprops(item.FileName, item.FileType, item.ActualSize, item.LastSync);
		files.push_back(rfprops);
	}

	return files;
}
