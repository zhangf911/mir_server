#ifndef SESSION_H
#define SESSION_H

#include <gce/actor/all.hpp>
#include <gce/asio/all.hpp>
#include "Common.h"
#include "player.h"

enum session_status
{
	session_initial,
	session_auth,
	session_run,
	session_over,
};

class game_session
{
public:
	game_session(unsigned int in_session_id);

	~game_session();

public:
	void start(gce::stackful_actor actor);

	void handle_msg(gce::stackful_actor actor, unsigned int in_type, const string& msg_data);
private:
	unsigned int m_session_id = 0;
	gce::aid_t m_player_aid;
	unsigned int m_account_id = 0;
	unsigned int m_player_id = 0;
	time_t m_login_time = 0;
	string m_account_name = "";
	unsigned int m_session_status = 0;
	//gce::stackful_actor m_actor;
	game_player m_player;
};


#endif