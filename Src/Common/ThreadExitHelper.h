#ifndef GAMESERVER_THREADEXITHELPER_H
#define GAMESERVER_THREADEXITHELPER_H

#include <mutex>
#include <condition_variable>

class ThreadExitHelper
{
public:
	static std::mutex m_dbWorkThreadMutex;
	static std::condition_variable m_dbWorkThreadExitCV;

	static std::mutex m_dataSyncWorkThreadMutex;
	static std::condition_variable m_dataSyncThreadExitCV;
};


#endif