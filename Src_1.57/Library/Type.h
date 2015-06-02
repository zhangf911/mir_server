#ifndef LIBRARY_TYPE_H
#define LIBRARY_TYPE_H

typedef char Int8;
typedef unsigned char UInt8;
typedef short Int16;
typedef unsigned short UInt16;
typedef int Int32;
typedef unsigned int UInt32;
#ifdef WIN32
typedef __int64 Int64;
typedef unsigned __int64 UInt64;
#else
typedef long long Int64;
typedef unsigned long long UInt64;
#endif

#include <cstring>

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <sstream>
using std::stringstream;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <list>
using std::list;

#include <set>
using std::set;

#include <map>
using std::map;

#include <deque>
using std::deque;

#ifdef OPEN_NET_DEBUG_INFO
#define NET_DEBUG_INFO 1
#endif

// ��Ϣ���ӽ���
//#define  ENCRYPT

// ����һ�δ�������������
#define  COUNT_NET_RECEIVEDPACKET   100
// ������ܰ����������
#ifdef TXJ_DEBUG
#define  MAX_NET_RECEIVEDPACKET    0 // 60000
#else
#define  MAX_NET_RECEIVEDPACKET   0
#endif
#endif

// �����������
#ifdef TXJ_DEBUG
#define  TIANTI_TEAMCOUNT_MAX   5
#else
#define  TIANTI_TEAMCOUNT_MAX   5
#endif
// ���ݻ��ֳ�ʼ��
#define  TIANTI_TTSCORE_INIT  1000
// ����Ӣ�۳�ʼ��
#define  TIANTI_HEROSCORE_INIT  1000
