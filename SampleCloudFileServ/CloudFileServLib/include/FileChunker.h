#pragma once
#include "Common.h"
#include "../include/FileChunkerState.h"

namespace CloudFileServLib
{
	namespace BL
	{
		class FileChunker
		{
		public:
			FileChunker(const file_size_t chunkSize);
			~FileChunker();

			void OpenFile(const std::string filePath);
			std::vector<byte> ReadNextChunk();
			bool HasMore();
			void Close();

		private:
			file_size_t chunkSize;
			FileChunkerState state;
		};
	}
}
