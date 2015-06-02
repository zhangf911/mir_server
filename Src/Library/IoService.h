#ifndef LIBRARY_IOSERVICE_H
#define LIBRARY_IOSERVICE_H

#include "Type.h"
#include <boost/asio.hpp>
using boost::asio::io_service;

class IoService
{
public:
	io_service& GetIOService()
	{
		return m_ioservice;
	};

private:
	io_service m_ioservice;
};


#endif