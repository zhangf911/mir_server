#ifndef LIBRARY_CIRCULARBUFFER_H
#define LIBRARY_CIRCULARBUFFER_H

#include "Type.h"
#include <boost/aligned_storage.hpp>

class CircularBuffer
{
public:
	enum 
	{
		CircularBufferSize = 1024 * 4,
	};
public:
	CircularBuffer();

	~CircularBuffer();

public:
	char* GetBuffer();

	void ReadBuffer(char* OUTbuffer, UInt32 INsize);

	void WriteBuffer(const char* INpBuffer, UInt32 INsize);

	UInt32 GetFreeSpace();

	UInt32 GetUsedSpace();

	void ClearBuffer();
private:
	// ����
	boost::aligned_storage<CircularBufferSize>	m_buffer;
	// ��ȡλ��
	UInt32 m_readPos;
	// д��λ��
	UInt32 m_writePos;
};



#endif