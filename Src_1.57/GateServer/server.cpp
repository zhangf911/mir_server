#include "server.h"
#include <thread>

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

		//gce::asio::tcp::resolver rsv(actor);
		//tcp_resolver_t::query qry("0.0.0.0", "12345");
		//rsv.async_resolve(qry);
		//boost::shared_ptr<tcp_resolver_t::iterator> eitr;
		//actor->match(gce::asio::tcp::as_resolve).recv(ec, eitr);
		//GCE_VERIFY(!ec).except(ec);
		//std::cout << ec.message() << std::endl;
		//std::cout << ec.value() << std::endl;

		//gce::asio::tcp::acceptor acpr(actor);
		//boost::asio::ip::tcp::endpoint ep = **eitr;

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

			std::cout << "handle new connect" << endl;

			msg >> ec;
			if (!ec)
			{
				std::cout << "new client" << endl;
				gce::aid_t cln = spawn(actor, boost::bind(&gce_server::new_session, this, _arg1), gce::monitored);
				actor->send(cln, "init", skt);
				++scount;
			}
		}
	}
	catch (std::exception& ex)
	{
		GCE_ERROR(lg) << ex.what();
		std::cout << ex.what();
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

		while (true)
		{
			std::chrono::milliseconds dura(40);
			std::this_thread::sleep_for(dura);
		}
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

		amsg::zero_copy_buffer zbuf;
		gce::byte_t read_buff[256];
		std::deque<gce::bytes_t> write_queue;

		echo_header hdr;
		size_t const hdr_len = amsg::size_of(hdr);
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
				amsg::read(zbuf, hdr);
				if (zbuf.bad())
				{
					break;
				}

				skt.async_read(boost::asio::buffer(read_buff + hdr_len, hdr.size_), gce::message(recv_body));
			}
			else if (type == recv_body)
			{
				zbuf.set_read(read_buff + hdr_len, hdr.size_);
				std::string str;
				amsg::read(zbuf, str);
				if (zbuf.bad())
				{
					break;
				}

				GCE_INFO(lg) << "server recved echo: " << str;
				if (str == "bye")
				{
					break;
				}

				bool write_in_progress = !write_queue.empty();
				write_queue.push_back(gce::bytes_t(read_buff, hdr_len + hdr.size_));
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