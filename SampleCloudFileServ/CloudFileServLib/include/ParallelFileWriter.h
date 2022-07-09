#pragma once

#include "Common.h"
#include <thread>
#include <ostream>
#include <fstream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/directory.hpp>
#include <boost/filesystem/operations.hpp>
#include <direct.h>

using namespace std;
using namespace boost::filesystem;

namespace CloudFileServLib
{
	namespace BL
	{
		class ParallelFileWriter
		{
		public:
			std::thread WriteToFile(path fileName, std::vector<uint8_t> content)
			{
				//Create folder structure if not exists before writing to file
				if (!exists(fileName.parent_path()))
				{
					int res = _mkdir(fileName.parent_path().string().c_str());
				}

				//Initiate a thread for writing to file
				thread th{ [&]() {
					ofstream os(fileName.string(), ios::out | ios::binary);
					os.write((char*)content.data(), content.size());
					os.flush();
					os.close();
				} };

				return th;
			}
		};
	}
}