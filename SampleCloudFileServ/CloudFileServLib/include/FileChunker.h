#pragma once
#include "Common.h"
#include "../include/FileChunkerState.h"

namespace CloudFileServLib
{
	namespace BL
	{
		using namespace std;
		class FileChunker
		{
		public:
			FileChunker(const file_size_t chunkSize);
			~FileChunker();

			void OpenFile(const string filePath);
			vector<byte> ReadNextChunk();
			bool HasMore();
			void Close();

		private:
			file_size_t chunkSize;
			FileChunkerState state;
		};
	}
}
