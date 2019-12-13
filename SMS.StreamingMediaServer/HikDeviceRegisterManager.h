#pragma once
#include <string>
#include <map>
#include <Windows.h>
using namespace std;

struct SMS_DEV_REGISTER_STATUS
{
	string id;
	string userName;
	string password;
	LONG loginId;
	int registerCount;
};

class HikDeviceRegisterManager
{
public:
	HikDeviceRegisterManager();
	~HikDeviceRegisterManager();

	LONG DeviceRegister(string ip, int port, string userName, string password);
	bool DeviceUnregister(string devId);
	bool DeviceUnregister(LONG loginId);

private:
	void Init();
	LONG DeviceLogin(std::string& ipAddress, int port, std::string& userName, std::string& password);
	SMS_DEV_REGISTER_STATUS DeviceFirstRegister(std::string& ipAddress, int port, std::string& userName, std::string& password);
	BOOL DeviceNonfirstRegister(SMS_DEV_REGISTER_STATUS* registerStatus, std::string& userName, std::string& password);
	void DeviceUnregister(SMS_DEV_REGISTER_STATUS* registerStatus);
	void LogoutAllConnections();
	static VOID CALLBACK OnExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void* pUser);

	std::map<string, SMS_DEV_REGISTER_STATUS> deviceLoginMap;
	bool isInitialized = false;
};

