#include "server.h"
#include <thread>
#include "mir_proto.adl.h"
#include "opcodes.pb.h"

typedef boost::asio::ip::tcp::socket tcp_socket_t;
typedef boost::asio::ip::tcp::resolver tcp_resolver_t;



gce_server::gce_server()
{

}

gce_server::~gce_server()
{

}

void gce_server::start(gce::stackful_actor actor)
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

		GCE_INFO(lg) << "server is ready\n";

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
				std::cout << "new client, current cout :" << (scount + 1) << endl;
				gce::aid_t cln = spawn(actor, boost::bind(&gce_server::new_session, this, _arg1), gce::monitored);
				actor->send(cln, "init", skt);
				++scount;
			}
		}
	}
	catch (std::exception& ex)
	{
		GCE_ERROR(lg) << ex.what();
	}
}

void gce_server::run(gce::stackful_actor actor)
{
	gce::context& ctx = actor.get_context();
	gce::log::logger_t& lg = ctx.get_logger();

	try
	{
		gce::aid_t sender = actor->recv("init");

		actor->send(sender, "ready");

		GCE_INFO(lg) << "main loop is ready\n";

		//while (true)
		//{
		//	std::chrono::milliseconds dura(1000);
		//	std::this_thread::sleep_for(dura);
		//}
	}
	catch (std::exception& ex)
	{
		GCE_ERROR(lg) << ex.what();
	}
}

void gce_server::stop()
{

}

void gce_server::new_session(gce::stackful_actor actor)
{
	gce::log::logger_t& lg = actor.get_context().get_logger();
	try
	{
		boost::shared_ptr<tcp_socket_t> tcp_skt;
		actor->match("init").recv(tcp_skt);

		gce::asio::tcp::socket skt(actor, tcp_skt);

		adata::zero_copy_buffer zbuf;
		gce::byte_t read_buff[256];
		std::deque<gce::bytes_t> write_queue;

		mir::msg_header hdr;
		size_t const hdr_len = adata::size_of(hdr);
		gce::match_t const recv_header = gce::atom("header");
		gce::match_t const recv_body = gce::atom("body");

		skt.async_read(boost::asio::buffer(read_buff, hdr_len), gce::message(recv_header));
		while (true)
		{
			gce::match_t type;
			gce::errcode_t ec;
			actor->match(recv_header, recv_body, gce::asio::tcp::as_send, type).recv(ec);
			GCE_VERIFY(!ec).except(ec);

			if (type == recv_header)
			{
				zbuf.set_read(read_buff, hdr_len);
				adata::read(zbuf, hdr);
				if (zbuf.bad())
				{
					break;
				}
				
				GCE_INFO(lg) << "message :" << hdr.type << " body size : " << hdr.size << "\n";

				skt.async_read(boost::asio::buffer(read_buff + hdr_len, hdr.size), gce::message(recv_body));
			}
			else if (type == recv_body)
			{
				zbuf.set_read(read_buff + hdr_len, hdr.size);
				std::string str;
				mir::echo_message echo_message;

				adata::read(zbuf, echo_message);
				str = echo_message.msg;
				if (zbuf.bad())
				{
					break;
				}

				msg_login login;
				login.ParseFromString(str);

				GCE_INFO(lg) << "server recved echo: " << login.account();
				if (str == "bye")
				{
					break;
				}

				bool write_in_progress = !write_queue.empty();
				write_queue.push_back(gce::bytes_t(read_buff, hdr_len + hdr.size));
				if (!write_in_progress)
				{
					gce::bytes_t const& echo = write_queue.front();
					skt.async_write(boost::asio::buffer(echo.data(), echo.size()));
				}

				skt.async_read(boost::asio::buffer(read_buff, hdr_len), gce::message(recv_header));
			}
			else
			{
				write_queue.pop_front();
				if (!write_queue.empty())
				{
					gce::bytes_t const& echo = write_queue.front();
					skt.async_write(boost::asio::buffer(echo.data(), echo.size()));
				}
			}
		}
	}
	catch (std::exception& ex)
	{
		GCE_ERROR(lg) << ex.what();
	}
}