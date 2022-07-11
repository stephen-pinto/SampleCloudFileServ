#include "pch.h"
#include "..\include\CommandLineProvider.h"
#include <boost/algorithm/string.hpp>
#include "../include/BlobStorageProvider.h"
#include "../include/StorageProviderFactory.h"

using namespace CloudFileServLib::BL;
using namespace std;
using namespace boost;

string binaryCmds[] = { "rm", "cp" };

/// <summary>
/// FIXME: Remove this function
/// </summary>
string TempReadConnectionStringFromFile(string fileName)
{
	ifstream strm;
	string content;
	strm.open(fileName);
	strm >> content;
	return content;
}

CloudFileServLib::BL::CommandLineProvider::CommandLineProvider()
{
	auto connStr = TempReadConnectionStringFromFile("ConnectionStrings.txt");
	storageProvider = unique_ptr<IFileBasedStorageProvider>(StorageProviderFactory::GetDefaultProvider(connStr, FileBasedStorageType::Blobs));
}

int CommandLineProvider::Run(int argc, char** argv)
{
	string input;

	while (true)
	{
		if (rootDir.empty())
		{
			//If not set then first collect a root directory to sync
			_PRINT("Please provide a ROOT dir to get started:");
			getline(cin, rootDir);

			_PRINT("\nPlease provide a container name to use:");
			string containerName;
			getline(cin, containerName);
			storageProvider->OpenContainer(containerName);

			//Initialize
			fileChangeChecker = make_unique<FileChangeChecker>(rootDir);
			_PRINT("\nPlease wait downloading files from server...");
			//Download all the files from the server
			storageProvider->DownloadAllFiles(rootDir);
			//TODO: Launch below operation in another thread
			_PRINT("Downloading complete. Now initializing...");
			fileChangeChecker->Initialize();
			_PRINT("");
		}

		cout << "$> ";
		getline(cin, input);

		//If exit invoked the break out
		if (input == "exit")
			break;

		//Handle the command
		int res = HandleCommand(input);

		cout << endl;

		//Incase a command failed then return appropriate status
		if (res != 0)
			return res;
	}

	return 0;
}

int CommandLineProvider::HandleCommand(string command)
{
	vector<string> cmdParams;

	split(cmdParams, command, is_any_of(" "));

	//If its a binary command then let the other function handle it
	if (cmdParams.size() > 1)
		return HandleBinaryCommand(cmdParams);

	//For all other types of commands handle here
	if (command == "ls")
	{
		auto files = fileChangeChecker->GetSyncdFiles();
		for (auto& item : files)
			_PRINT(item.ToString());
	}
	else if (command == "pwd")
	{
		_PRINT(rootDir);
	}
	else if (command == "sync")
	{
		//Make sure fileChangeChecker.Initialize was complete before proceeding here
		auto listMap = fileChangeChecker->GetChangedFiles();

		_PRINT("Files changed: " << listMap.size());
		if (listMap.size() > 0)
		{
			_PRINT("Changed files:");
			_PRINT("-------");
			for (auto item : listMap)
			{
				_PRINT("Filename: " << item.first);
				_PRINT("BlocksChanged: " << item.second);
			}
			_PRINT("-------");

			//Upload changed files
			for (auto item : listMap)
			{
				storageProvider->UploadFileFrom(ServerPath(item.first), item.first);
			}
		}
		else
		{
			_PRINT("No files were changed since last sync");
		}
	}
	else if (command == "clear")
	{
		system("cls");
	}
	else
	{
		//If the command was a binary command but without args
		for (auto item : binaryCmds)
		{
			if (starts_with(command, item))
			{
				_PRINT("Not enough arguments passed to command");
				return 0;
			}
		}

		//In all other cases
		_PRINT("Specified command not supported");
	}

	return 0;
}

int CommandLineProvider::HandleBinaryCommand(std::vector<std::string> params)
{
	if (params.front() == "rm")
	{
		_PRINT("Removed file " << params.back());
	}
	else if (params.front() == "cp")
	{
		_PRINT("Copied file" << params.back());
	}

	return 0;
}

std::string CloudFileServLib::BL::CommandLineProvider::ServerPath(std::string path)
{
	string tmpRootDir(rootDir);
	string::size_type ipos = path.find(tmpRootDir);
	if (ipos != string::npos)
		path.erase(ipos, tmpRootDir.append("\\").length());
	return path;
}
