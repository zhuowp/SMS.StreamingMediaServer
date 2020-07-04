#pragma once

#include "windows.h"
#include <string>

class NetDevice
{
public:
	NetDevice();
	NetDevice(std::string address, std::uint16_t port, std::string username, std::string password);
	~NetDevice();

	void SetAddress(std::string address);
	void SetPort(std::uint16_t port);
	void SetUserName(std::string username);
	void SetPassword(std::string password);

	bool IsLogin();
	virtual std::int64_t Login();
	virtual std::int64_t Logout();

private:
	std::string _address = "";
	std::uint16_t	 _port = 0;
	std::string _userName = "";
	std::string _password = "";

	bool	_isLogin = false;
	long _loginHandle = -1;
};