#include "../include/file_change_checker.h"
#include "../include/common.h"
#include <boost/filesystem.hpp>
#include <iostream>

using namespace cmd_tool;
using namespace boost::filesystem;

map<string, size_t> file_change_checker::check_changes(const string root)
{
    path root_path(root);
    recursive_directory_iterator dir_end;
    for (recursive_directory_iterator itr(root_path); itr != dir_end; ++itr)
    {
        if(is_directory(itr->status()))
            continue;
        
        if(is_regular_file(itr->status()))
        {
            auto fn = itr->path().filename();
            _PRINT("----------------------");
            _PRINT("Iterator: " << *itr);
            _PRINT("Filename: " << fn.c_str());
            _PRINT("Parent: " << fn.parent_path());
        }
    }

    map<string, size_t> map;
    return map;
}
