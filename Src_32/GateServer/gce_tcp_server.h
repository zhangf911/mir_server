#ifndef GCE_TCP_SERVER_H
#define GCE_TCP_SERVER_H

#include <gce/actor/all.hpp>
#include <gce/asio/all.hpp>
#include <memory>
#include "Common.h"
#include "session.h"


class gce_tcp_server
{
public:
	gce_tcp_server();

	~gce_tcp_server();

public:
	void start(gce::stackful_actor base_actor);

	void run(gce::stackful_actor actor);

	void stop();

private:
	gce::aid_t m_root_id;
	std::list<boost::shared_ptr<game_session>> m_session_list;
	//std::list<game_session*> m_session_list;
};


#endif