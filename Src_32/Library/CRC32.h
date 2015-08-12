#ifndef LIBRARY_UTIL_CRC32_H
#define LIBRARY_UTIL_CRC32_H

class CRC32
{
public:
	/* This computes a 32 bit CRC of the data in the buffer, and returns the
   CRC.  The polynomial used is 0xedb88320. */
	static unsigned long GetCRC32(const unsigned char* s, unsigned int len);

};


#endif