#include "NetWorkProxy.h"

NetWorkProxy::NetWorkProxy(std::string Port) : Port(Port)
{
	Port = "http://127.0.0.1:" + Port;
	std::cout << "proxy load finished" << std::endl;
}

NetWorkProxy::~NetWorkProxy()
{
	std::cout << "port finish used" << std::endl;
}

std::string NetWorkProxy::getPort()
{
	return Port;
}

void NetWorkProxy::setPort(const std::string port)
{
	Port = "http://127.0.0.1:" + port;
	std::cout << "port set finished" << std::endl;
}
