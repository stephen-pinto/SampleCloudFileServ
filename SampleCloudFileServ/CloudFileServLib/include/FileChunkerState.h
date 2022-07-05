#pragma once

#include "Common.h"
#include <fstream>

namespace CloudFileServLib
{
	namespace BL
	{
		using namespace std;
		class FileChunkerState
		{
		public:
			file_size_t TotalBytes;
			file_size_t TotalChunksObtained;
			file_size_t LastChunkSize;
			ifstream* Stream;

			file_size_t GetTotalChunks(file_size_t chunkSize);
			void Close();
		};
	}
}
