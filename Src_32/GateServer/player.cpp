#include "player.h"

game_player::game_player()
{

}

game_player::~game_player()
{

}

void game_player::start(gce::stackful_actor actor)
{
	gce::context& ctx = actor.get_context();
	gce::log::logger_t& lg = ctx.get_logger();
	try
	{
		gce::aid_t sender = actor->recv("init");

		actor->send(sender, "ready");

		// 加载角色数据，初始化

		// 
		std::cout << "初始化角色成功" << std::endl;

		// 状态更新
		while (true)
		{
			gce::message msg;
			gce::aid_t sender = actor.recv(msg, gce::pattern(gce::seconds(1)));
			if (sender != gce::aid_nil)
			{
				// 未超时，处理消息
				if(msg.get_type() == gce::exit)
				{
					std::cout << "角色退出游戏" << std::endl;
					break;
				}
			}
			else
			{
				// 超时，没有收到任何消息，根据情况自己继续循环还是break退出
			}
		}
	}
	catch (std::exception& ex)
	{
		GCE_ERROR(lg) << ex.what();
	}
}