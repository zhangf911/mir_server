#include "CircularBuffer.h"
#include <cstring>

CircularBuffer::CircularBuffer()
{
	ClearBuffer();
}

CircularBuffer::~CircularBuffer()
{
	ClearBuffer();
}

char* CircularBuffer::GetBuffer()
{
	return (char*)m_buffer.address() + m_readPos;
}

void CircularBuffer::ReadBuffer(char* OUTbuffer, UInt32 INsize)
{
	if(m_readPos + INsize < CircularBufferSize)
	{
		m_readPos += INsize;
	}
	else
	{
		UInt32 targetPos = INsize - (CircularBufferSize - m_readPos);
		if(targetPos <= m_writePos)
		{
			m_readPos = targetPos;
		}
	}
}

void CircularBuffer::WriteBuffer(const char* INpBuffer, UInt32 INsize)
{
	if(INsize > GetFreeSpace())
	{
		return;
	}

	if(m_writePos > m_readPos)
	{
		if(m_writePos + INsize >= CircularBufferSize)
		{
			memcpy((char*)m_buffer.address() + m_writePos, INpBuffer, CircularBufferSize - m_writePos);
			UInt32 lastSize = INsize - (CircularBufferSize - m_writePos);
			if(lastSize > 0)
			{
				memcpy(m_buffer.address(), INpBuffer + (CircularBufferSize - m_writePos), lastSize);
			}
		}
	}
	else
	{
		memcpy((char*)m_buffer.address() + m_writePos, INpBuffer, INsize);
	}
}

UInt32 CircularBuffer::GetFreeSpace()
{
	if(m_readPos <= m_writePos)
	{
		return CircularBufferSize - (m_writePos - m_readPos);
	}
	else
	{
		return m_readPos - m_writePos;
	}
}

UInt32 CircularBuffer::GetUsedSpace()
{
	return CircularBufferSize - GetFreeSpace();
}

void CircularBuffer::ClearBuffer()
{
	m_readPos = 0;
	m_writePos = 0;
}
