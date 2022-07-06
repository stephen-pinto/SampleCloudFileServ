#include "pch.h"
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include "../include/FileChangeChecker.h"

using namespace std;
using namespace boost::filesystem;
using namespace boost::algorithm;
using namespace CloudFileServLib::BL;

FileChangeChecker::FileChangeChecker(const string& root) : root(root)
{}

void FileChangeChecker::Initialize()
{
	path root_path(root);
	recursive_directory_iterator dir_end;
	FileChunker chunker(BLOCK_SIZE);

	for (recursive_directory_iterator itr(root_path); itr != dir_end; ++itr)
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
}

map<string, size_t> FileChangeChecker::GetChangedFiles()
{
	path root_path(root);
	recursive_directory_iterator dir_end;
	FileChunker chunker(BLOCK_SIZE);

	for (recursive_directory_iterator itr(root_path); itr != dir_end; ++itr)
	{
		if (is_directory(itr->status()))
			continue;

		if (is_regular_file(itr->status()))
		{
			//auto prnt = itr->path().parent_path();
			//auto fn = itr->path().filename();
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

			fileStoreState.Files.push_back(fprops);

			//_PRINT("----------------------");
			////_PRINT("Iterator: " << *itr);
			//_PRINT("Filename: " << fprops.FileName);
			//_PRINT("Path: " << fprops.FileName);
			//_PRINT("Parent: " << prnt.string());
			//_PRINT("Size: " << fprops.ActualSize / 1024);
		}
	}

	_PRINT("Total files found: " << fileStoreState.Files.size());

	return std::map<std::string, size_t>();
}
