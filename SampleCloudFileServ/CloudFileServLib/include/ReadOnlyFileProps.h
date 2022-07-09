#pragma once

#include "Common.h"
#include "IPrintable.h"
#include <sstream>

namespace CloudFileServLib
{
	namespace BL
	{
		/// <summary>
		/// This struct acts a readonly representation of the currently available information
		/// The result of this data should not be saved
		/// </summary>
		struct ReadOnlyFileProps : public IPrintable
		{
			const std::string& FileName;
			const std::string& FileType;
			const file_size_t& ActualSize;
			const time_t& LastSync;

			ReadOnlyFileProps(const std::string& fn, const std::string& ft, const file_size_t& as, const time_t& ls) : FileName(fn), FileType(ft), ActualSize(as), LastSync(ls)
			{}

			std::string ToString()
			{
				std::ostringstream stringStream;
				stringStream << "FileName: `" << FileName << "` | Size: `" << ActualSize << "` bytes" << "` | Type: `" << FileType << "`";
				return stringStream.str();
			}
		};
	}
}