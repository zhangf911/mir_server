#ifndef LIBRARY_UTIL_FILEUTIL_H
#define LIBRARY_UTIL_FILEUTIL_H

#include "Type.h"

namespace Library
{
	class FileUtil
	{
	public:
		/**
		* @brief ��ȡ�ļ�����
		**/
		static char* GetFileData(const char* INfile, UInt32* OUTfileSize);
	};
}


#endif