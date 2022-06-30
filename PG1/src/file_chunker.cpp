#include "../include/file_chunker.h"

using namespace std;
using namespace cmd_tool;

file_chunker::file_chunker(size_t chunk_size) : chunk_size(chunk_size)
{
}
    
file_chunker::~file_chunker()
{
    close();
}

void file_chunker::open_file(string file_path)
{
    //Open a file in binary mode to the EOF
    state.stream = new ifstream(file_path, ios::ate | ios::binary);
    
    if(!*state.stream)
        throw runtime_error("Could not open file");
    
    //Get the size of the file
    state.total_bytes = state.stream->tellg();
    //Clear EOF flag and move read pointer to start
    state.stream->clear();
    state.stream->seekg(0);
    _PRINT("File open completed");
    _PRINT("File size: " << state.total_bytes);
}

vector<byte> file_chunker::read_next_chunk()
{
    _PRINT("file_chunker entered read_next_chunk()");
    char buff[chunk_size];
    if(!state.stream->eof())
    {
        _PRINT("file_chunker reading chunk");
        //if we are not at the end of file then read next chunk
        state.stream->read(buff, chunk_size);
        state.total_chunks_obtained += chunk_size;
        state.last_chunk_size = state.stream->gcount();
    }
    else
    {
        _PRINT("file_chunker reading chunk");
    }

    vector<byte> vc(buff, buff + state.last_chunk_size);
    _PRINT("Vector : " << vc.size() << " bytes");
    _PRINT("file_chunker read : " << state.last_chunk_size << " bytes");

    return vc;
}

bool file_chunker::has_more()
{
    return !state.stream->eof();
}

void file_chunker::close()
{
    state.close();
}
