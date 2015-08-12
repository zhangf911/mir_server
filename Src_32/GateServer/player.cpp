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

		// ���ؽ�ɫ���ݣ���ʼ��

		// 
		std::cout << "��ʼ����ɫ�ɹ�" << std::endl;

		// ״̬����
		while (true)
		{
			gce::message msg;
			gce::aid_t sender = actor.recv(msg, gce::pattern(gce::seconds(1)));
			if (sender != gce::aid_nil)
			{
				// δ��ʱ��������Ϣ
				if(msg.get_type() == gce::exit)
				{
					std::cout << "��ɫ�˳���Ϸ" << std::endl;
					break;
				}
			}
			else
			{
				// ��ʱ��û���յ��κ���Ϣ����������Լ�����ѭ������break�˳�
			}
		}
	}
	catch (std::exception& ex)
	{
		GCE_ERROR(lg) << ex.what();
	}
}