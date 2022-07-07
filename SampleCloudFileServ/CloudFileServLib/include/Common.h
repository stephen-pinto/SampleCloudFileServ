#pragma once

#include <iostream>
#include <math.h>
#include <memory>
#include <vector>
#include <string>

typedef size_t file_size_t;
typedef unsigned char byte;

#ifdef _DEBUG
	#define _PRINT(str) std::cout << str << std::endl;
#else
	#define _PRINT(str) 
#endif

#define BLOCK_SIZE 1024 * 10