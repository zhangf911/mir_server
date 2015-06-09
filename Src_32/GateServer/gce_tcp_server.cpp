#include "gce_tcp_server.h"
#include <thread>
#include "mir_proto.adl.h"
#include "opcodes.pb.h"
#include "session.h"

typedef boost::asio::ip::tcp::socket tcp_socket_t;
typedef boost::asio::ip::tcp::resolver tcp_resolver_t;

gce_tcp_server::gce_tcp_server()
{

}

gce_tcp_server::~gce_tcp_server()
{

}

void gce_tcp_server::start(gce::stackful_actor actor)
{
	gce::context& ctx = actor.get_context();
	gce::log::logger_t& lg = ctx.get_logger();
	try
	{
		gce::aid_t sender = actor->recv("init");

		size_t scount = 0;
		gce::errcode_t ec;

		boost::asio::ip::address addr;
		addr.from_string("0.0.0.0");
		boost::asio::ip::tcp::endpoint ep(addr, 12345);

		gce::asio::tcp::acceptor acpr(actor);

		acpr->open(ep.protocol());

		acpr->set_option(boost::asio::socket_base::reuse_address(true));
		acpr->bind(ep);

		acpr->set_option(boost::asio::socket_base::receive_buffer_size(640000));
		acpr->set_option(boost::asio::socket_base::send_buffer_size(640000));

		acpr->listen(boost::asio::socket_base::max_connections);

		acpr->set_option(boost::asio::ip::tcp::no_delay(true));
		acpr->set_option(boost::asio::socket_base::keep_alive(true));
		acpr->set_option(boost::asio::socket_base::enable_connection_aborted(true));

		actor->send(sender, "ready");

		GCE_INFO(lg) << "gce_tcp_server is ready\n";

		while (true)
		{
			boost::shared_ptr<tcp_socket_t> skt =
				boost::make_shared<tcp_socket_t>(boost::ref(ctx.get_io_service()));
			acpr.async_accept(*skt);

			gce::match_t type;
			gce::errcode_t ec;
			gce::message msg;
			actor->match(gce::asio::tcp::as_accept, "end", type).raw(msg).recv();
			if (type == gce::atom("end"))
			{
				break;
			}

			msg >> ec;
			if (!ec)
			{
				std::cout << "new client, current cout :" << (scount + 1) << std::endl;
				boost::shared_ptr<game_session> new_session_ptr = boost::make_shared<game_session>(scount + 1);
				//game_session* new_session_ptr = new game_session(scount + 1);
				m_session_list.push_back(new_session_ptr);
				gce::aid_t cln = spawn(actor, boost::bind(&game_session::start, new_session_ptr, _arg1), gce::monitored);
				actor->send(cln, "init", skt);
				++scount;
			}
		}
	}
	catch (std::exception& ex)
	{
		GCE_ERROR(lg) << __FUNCTION__ << __LINE__ << ex.what();
	}
}

void gce_tcp_server::run(gce::stackful_actor actor)
{
	gce::context& ctx = actor.get_context();
	gce::log::logger_t& lg = ctx.get_logger();

	try
	{
		gce::aid_t sender = actor->recv("init");

		actor->send(sender, "ready");

		GCE_INFO(lg) << "main loop is ready\n";

		while (true)
		{
			gce::message msg;
			gce::aid_t sender = actor.recv(msg, gce::pattern(gce::seconds(1)));
			if (sender != gce::aid_nil)
			{
				// 未超时，处理消息
			}
			else
			{
				// 超时，没有收到任何消息，根据情况自己继续循环还是break退出
			}
		}
	}
	catch (std::exception& ex)
	{
		GCE_ERROR(lg) << __FUNCTION__ << __LINE__ << ex.what();
	}
}

void gce_tcp_server::stop()
{

}
