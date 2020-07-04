#include "NetDevice.h"

NetDevice::NetDevice() {}

NetDevice::NetDevice(std::string address, std::uint16_t port, std::string username, std::string password)
{
	_address = address;
	_port = port;
	_userName = username;
	_password = password;
}

NetDevice::~NetDevice(){}

void NetDevice::SetAddress(std::string address)
{
	_address = address;
}

void NetDevice::SetPort(std::uint16_t port)
{
	_port = port;
}

void NetDevice::SetUserName(std::string username)
{
	_userName = username;
}

void NetDevice::SetPassword(std::string password)
{
	_password = password;
}

bool NetDevice::IsLogin()
{
	return _isLogin;
}

std::int64_t NetDevice::Login()
{
	return -1;
}

std::int64_t NetDevice::Logout()
{
	return -1;
}