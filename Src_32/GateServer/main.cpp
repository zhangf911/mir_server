#include "CommDef.h"
#include <gce/actor/all.hpp>
#include <gce/asio/all.hpp>
#include "server.h"
#include "gce_tcp_server.h"

int main()
{
	gce::log::asio_logger lgr;
	gce::log::logger_t lg = boost::bind(&gce::log::asio_logger::output, &lgr, _arg1, "");
	gce::attributes attrs;
	attrs.lg_ = lg;

	try
	{
		gce::context gce_context(attrs);
		gce::threaded_actor gate_base = gce::spawn(gce_context);

		gce_tcp_server server;
		gce::aid_t svr = spawn(gate_base, boost::bind(&gce_tcp_server::start, &server, _arg1), gce::monitored);

		gate_base->send(svr, "init");

		gate_base->recv("ready");

		gce::aid_t main_loop = spawn(gate_base, boost::bind(&gce_tcp_server::run, &server, _arg1), gce::monitored);

		gate_base->send(main_loop, "init");
		gate_base->recv("ready");

		// 等待退出信号
		gate_base->recv(gce::exit);
	}
	catch (std::exception& ex)
	{
		GCE_ERROR(lg) << ex.what();
	}
	
	return 0;
}