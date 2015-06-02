#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#pragma warning(disable:4251)

#include "Ensure.hpp"

#ifdef ENSURE_HAS_BOOST

class my_except : public virtual un::exception {};

int EnsureTest()
{
	try
	{
		boost::int32_t i = 0;
		std::string str("test str");
		ENSURE(i == 0 && str.empty(), (i)(str)("Test Ensure Msg")(my_except()));
		std::cout << "Shouldn't be here." << std::endl;
	}
	catch (my_except& ex)
	{
		std::cerr << boost::diagnostic_information(ex) << std::endl;
	}

	return 0;
}

#else

class my_except : public virtual std::exception 
{
public:
	void set_error(std::string const& err) const
	{
		err_ = err;
	}

	virtual char const* what() const throw()
	{
		return err_.c_str();
	}

private:
	mutable std::string err_;
};

int EnsureTest()
{
	try
	{
		int i = 0;
		std::string str("test str");
		ENSURE(i == 0 && str.empty())(i)(str)("Test Ensure Msg")(my_except());
		std::cout << "Shouldn't be here." << std::endl;
	}
	catch (my_except& ex)
	{
		std::cerr << ex.what() << std::endl;
	}

	return 0;
}

#endif

void TestCurrentOSTypeSize()
{
	cout << "UnitTest : " << __FUNCTION__ << endl;
	cout << "Size of char : " << sizeof(char) << endl;
	cout << "Size of short : " << sizeof(short) << endl;
	cout << "Size of int : " << sizeof(int) << endl;
	cout << "Size of long : " << sizeof(long) << endl;
	cout << "Size of long long : " << sizeof(long long) << endl;
}

#include "IoService.h"
#include "NetServer.h"

/*
int main(int argc, char *argv[])
{
	cout << "Start Library Unit Test" << endl;
#ifdef WIN32
	cout << "Compile Version ID : " << _MSC_VER << endl;
	cout << "Operator System Version ID: " << _WIN32_WINNT << endl;
#else

#endif
	TestCurrentOSTypeSize();

	//EnsureTest();

	IoService ioService;
	NetServer netServer(ioService, 60001);
	
	netServer.Start();

	ioService.GetIOService().run();

	return 0;
}
*/