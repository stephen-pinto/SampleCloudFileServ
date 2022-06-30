#ifndef __FILE_CHANGE_CHECKER_H__
#define __FILE_CHANGE_CHECKER_H__

#include <string>
#include <vector>
#include <map>
#include "file_store_state.h"

namespace cmd_tool
{
    using namespace std;

    class file_change_checker
    {
    public:
        map<string, size_t> check_changes(const string root);

    private:
        file_store_state store_state;
    };
}

#endif // __FILE_CHANGE_CHECKER_H__