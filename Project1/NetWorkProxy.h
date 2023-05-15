#pragma once
#include "common.h"
class NetWorkProxy
{
private:
	std::string Port;
	
public:
	NetWorkProxy(const std::string Port);
	~NetWorkProxy();

	std::string getPort();
	void setPort(const std::string port);
};

