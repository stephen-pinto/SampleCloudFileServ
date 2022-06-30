#ifndef __FILE_STORE_STATE_H__
#define __FILE_STORE_STATE_H__

#include <vector>
#include <string>
#include <ctime>

namespace cmd_tool
{
    using namespace std;

    struct file_info
    {
        //vector<int> chunk_size;
        string filename;
        size_t actual_size;
        vector<string> checksums;
        time_t last_sync;
    };

    class file_store_state
    {
    public:
        vector<file_info> files;
    private:
    };
}

#endif // __FILE_STORE_STATE_H__