#include "CommDef.h"
#include <gce/actor/all.hpp>
#include <gce/asio/all.hpp>

struct echo_header
{
	uint32_t size_;
};

AMSG(echo_header, (v.size_&sfix));

class gce_server
{
public:
	gce_server();

	~gce_server();
public:
	void start(gce::stackful_actor base_actor);

	void run(gce::stackful_actor actor);

	void stop();

	void new_session(gce::stackful_actor actor);
};