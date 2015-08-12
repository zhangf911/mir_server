#include "ThreadExitHelper.h"

std::mutex ThreadExitHelper::m_dbWorkThreadMutex;
std::condition_variable ThreadExitHelper::m_dbWorkThreadExitCV;

std::mutex ThreadExitHelper::m_dataSyncWorkThreadMutex;
std::condition_variable ThreadExitHelper::m_dataSyncThreadExitCV;