#include "session.h"
#include "mir_proto.adl.h"
#include "opcodes.pb.h"

typedef boost::asio::ip::tcp::socket tcp_socket_t;
typedef boost::asio::ip::tcp::resolver tcp_resolver_t;

game_session::game_session(unsigned int in_session_id)
	:m_session_id(in_session_id)
{

}

game_session::~game_session()
{

}

void game_session::start(gce::stackful_actor actor)
{
	gce::log::logger_t& lg = actor.get_context().get_logger();
	try
	{
		boost::shared_ptr<tcp_socket_t> tcp_skt;
		actor->match("init").recv(tcp_skt);
		//m_actor = actor;
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

				// 把消息类型和消息内容转发给消息处理
				handle_msg(actor, hdr.type, echo_message.msg);
#if TEST
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
#endif
				// 继续接收
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
		GCE_ERROR(lg) << __FUNCTION__ << __LINE__ << ex.what();

		handle_msg(actor, 0, "");
	}
}

void game_session::handle_msg(gce::stackful_actor actor, unsigned int in_type, const string& msg_data)
{
	switch (m_session_status)
	{
		case session_initial:
		{
			if(in_type == opcode::cg_login_csq)
			{
				msg_login login;
				login.ParseFromString(msg_data);
				m_account_name = login.account();

				m_login_time = time(nullptr);

				m_player_aid = spawn(actor, boost::bind(&game_player::start, &m_player, _arg1), gce::monitored);
				actor->send(m_player_aid, "init");

				m_session_status = session_run;
			}
			break;
		}
		case session_run:
		{
			if(in_type == 0)
			{
				actor->send(m_player_aid, gce::exit);
				m_session_status = session_over;
			}
			break;
		}
		case session_over:
		{
			break;
		}
	}
}