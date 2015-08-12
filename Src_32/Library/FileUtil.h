#ifndef LIBRARY_UTIL_FILEUTIL_H
#define LIBRARY_UTIL_FILEUTIL_H

#include "Type.h"

namespace Library
{
	class FileUtil
	{
	public:
		/**
		* @brief 获取文件数据
		**/
		static char* GetFileData(const char* INfile, UInt32* OUTfileSize);
	};
}


#endif