#ifndef __FILE_CHUNKER_H__
#define __FILE_CHUNKER_H__

#include <string>
#include <vector>
#include <fstream>
#include "common.h"

namespace cmd_tool
{
    using namespace std;

    struct file_chunk_state
    {
        size_t total_bytes;
        size_t total_chunks_obtained;
        size_t last_chunk_size;
        ifstream* stream;

        size_t total_chunks(size_t chunk_size)
        {
            size_t chunks = total_bytes / chunk_size;
            if(total_bytes % chunk_size > 0)
                chunks++;
            return chunks;
        }

        void close()
        {
            if(stream != NULL)
                delete (stream);
            total_bytes = 0;
            total_chunks_obtained = 0;
            last_chunk_size = 0;
            stream = NULL;
        }
    };

    class file_chunker
    {
    public:
        file_chunker(size_t chunk_size);
        ~file_chunker();
        void open_file(string file_path);
        string read_next_chunk();
        bool has_more();
        void close();

    private:
        size_t chunk_size;
        file_chunk_state state;
    };
}

#endif // __FILE_CHUNKER_H__