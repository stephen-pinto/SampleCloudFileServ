#pragma once

#include "Common.h"
#include <fstream>

namespace CloudFileServLib
{
	namespace BL
	{
		class FileChunkerState
		{
		public:
			file_size_t TotalBytes = 0;
			file_size_t TotalChunksObtained = 0;
			file_size_t LastChunkSize = 0;
			std::ifstream* Stream = NULL;

			file_size_t GetTotalChunks(file_size_t chunkSize);
			void Close();
		};
	}
}
