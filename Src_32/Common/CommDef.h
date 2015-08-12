#ifndef COMMON_COMMDEF_H
#define COMMON_COMMDEF_H

#include <boost/optional.hpp>

#include "Singleton.h"
#include "Log.h"
#include "DBEngine.h"
#include "DataTime.h"

// 日志类型
#define LOG_INSTANCE Singleton<Library::Log>::Instance()
#define DEBUG_LOG Singleton<Library::Log>::Instance()->WriteDebug
#define ERROR_LOG Singleton<Library::Log>::Instance()->WriteError
#define NOTE_LOG Singleton<Library::Log>::Instance()->WriteNote
#define EXCEPTION_LOG Singleton<Library::Log>::Instance()->WriteException
#define ASSERT_LOG Singleton<Library::Log>::Instance()->WriteAssert
#define NON_LOG Singleton<Library::Log>::Instance()->WriteNon

// 断言
inline void	log_assert(const char* type, const char* str, const char* file, int line) { ASSERT_LOG("%s(%s) in %s, %d", type, str, file, line); }
#define SJ_ASSERT(x)   if( (!(x)) || (!"(#x)") ) { log_assert("SJ_ASSERT", #x, __FILE__, __LINE__); assert(!"(#x)"); } 

//#define TXJ_DEBUG
// 异常捕捉
#ifdef TXJ_DEBUG
#define		SJ_TRY
#define     SJ_DEPACKETCATCH(x,y)
#define		SJ_CATCH(x)
#define		SJ_CATCH2(x,y)
#define		SJ_CATCH3(x,y,z)
#else
#define		SJ_TRY		            try{
#ifdef WIN32
#define		SJ_SEHCATCH(x)			}catch (SEHTranslator& e){EXCEPTION_LOG("Caught SEH Exception,ExceptionCode:[0X%p]\n, %s", e.m_exptionCode, x); e.log();
#else
#define		SJ_SEHCATCH(x)
#endif
#define     SJ_DEPACKETCATCH(x,y)   }catch(DePacketErrorCode e) { EXCEPTION_LOG(("Process Msg Exception , ConnectionID=%d, PacketType=%d, DePacketErrorCode=%d"),x,y,e); 
#define		SJ_CATCH(x)	            }catch(...){ EXCEPTION_LOG((x)); }
#define		SJ_CATCH2(x,y)	        }catch(...){ EXCEPTION_LOG((x),(y)); }
#define		SJ_CATCH3(x,y,z)	    }catch(...){ EXCEPTION_LOG((x),(y),(z)); }
#endif

// 配置加载日志
#define CONFIG_LOAD_NOTE NOTE_LOG

// 战斗日志
#define OPEN_BATTLE_LOG
#ifdef OPEN_BATTLE_LOG
#define BATTLE_DEBUG_LOG NON_LOG
#define BATTLE_NOTE_LOG NOTE_LOG
#else
#define BATTLE_DEBUG_LOG NON_LOG
#define BATTLE_NOTE_LOG NON_LOG
#endif

// 单例对象析构
#define DESTROY_INSTANCE_LOG(Instance) do{	NOTE_LOG("%s, %d, 管理器 %s 执行析构", __FUNCTION__, __LINE__, #Instance); } while (0);

// 加载玩家数据库数据日志
#define LOAD_PLAYER_DATA_NOTE NON_LOG

// 数据同步日志
#define OPEN_DATA_SYNC_LOG
#ifdef OPEN_DATA_SYNC_LOG
#define DATA_SYNC_LOG DEBUG_LOG
#else
#define DATA_SYNC_LOG NON_LOG
#endif

// 网络消息包收发日志
#define NET_PACKET_LOG DEBUG_LOG

// 消息处理日志
#define GAME_MSG_HANDLER_LOG DEBUG_LOG

#endif