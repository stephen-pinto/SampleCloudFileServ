#include "pch.h"
#include "../include/FileChunker.h"

using namespace CloudFileServLib::BL;

FileChunker::FileChunker(const file_size_t chunk_size) : chunkSize(chunk_size)
{
}

FileChunker::~FileChunker()
{
    Close();
}

void FileChunker::OpenFile(const string filePath)
{
    //Open a file in binary mode to the EOF
    state.Stream = new ifstream(filePath, ios::ate | ios::binary);
    if (!*state.Stream)
        throw runtime_error("Could not open file");

    //Get the size of the file
    state.TotalBytes = state.Stream->tellg();
    //Clear EOF flag and move read pointer to start
    state.Stream->clear();
    state.Stream->seekg(0);
}

vector<byte> FileChunker::ReadNextChunk()
{
    vector<char> buff(chunkSize);
    if (!state.Stream->eof())
    {
        //if we are not at the end of file then read next chunk
        state.Stream->read(buff.data(), chunkSize);
        state.TotalChunksObtained += chunkSize;
        state.LastChunkSize = state.Stream->gcount();
    }

    //Prepare a byte vector
    vector<byte> vc((char *)buff.data(), buff.data() + state.LastChunkSize);
    return vc;
}

bool FileChunker::HasMore()
{
    return !state.Stream->eof();
}

void FileChunker::Close()
{
    state.Close();
}