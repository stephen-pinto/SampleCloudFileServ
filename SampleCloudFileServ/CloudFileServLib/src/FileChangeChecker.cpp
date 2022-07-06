#include "pch.h"
#include "../include/FileChangeChecker.h"
#include <boost/filesystem.hpp>

using namespace std;
using namespace CloudFileServLib::BL;
using namespace boost::filesystem;

map<string, size_t> FileChangeChecker::GetChangedFiles(const string& root)
{
    path root_path(root);
    recursive_directory_iterator dir_end;
    for (recursive_directory_iterator itr(root_path); itr != dir_end; ++itr)
    {
        if (is_directory(itr->status()))
            continue;

        if (is_regular_file(itr->status()))
        {
            auto prnt = itr->path().parent_path();
            auto fn = itr->path().filename();
            auto pth = itr->path();
            auto size = file_size(pth);
            _PRINT("----------------------");
            //_PRINT("Iterator: " << *itr);
            _PRINT("Filename: " << fn.string());
            _PRINT("Path: " << pth.string());
            _PRINT("Parent: " << prnt.string());
            _PRINT("Parent: " << size);
        }
    }

    return std::map<std::string, size_t>();
}
