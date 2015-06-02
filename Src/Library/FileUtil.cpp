#include "FileUtil.h"
#include <fstream>
using std::ifstream;
using std::ios;

namespace Library
{
	char* FileUtil::GetFileData(const char* INfile, UInt32* OUTfileSize)
	{
		char* pData = NULL;
		ifstream ifile(INfile, ios::binary);
		if(!ifile)
		{
			return 0;
		}
		Int32 dataSize = 0;
		ifile.seekg(0, ios::end);
		dataSize = static_cast<Int32>(ifile.tellg());
		ifile.seekg(0, ios::beg);

		try
		{
			pData = new char[dataSize + 1];
		}
		catch(...)
		{
			return NULL;
		}
		
		ifile.read(pData, dataSize);
		pData[dataSize] = '\0';
		*OUTfileSize = dataSize;
		return pData;
	}
}
