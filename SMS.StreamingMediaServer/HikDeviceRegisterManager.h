#pragma once
#include <string>
#include <map>
#include <Windows.h>
#include "DeviceCommonDef.h"

class HikDeviceRegisterManager
{
public:
	static HikDeviceRegisterManager* GetInstance();
	~HikDeviceRegisterManager();

	LONG DeviceRegister(string ip, int port, string userName, string password);
	bool DeviceUnregister(string devId);
	bool DeviceUnregister(LONG loginId);

private:
	HikDeviceRegisterManager();
	void Init();
	LONG DeviceLogin(std::string& ipAddress, int port, std::string& userName, std::string& password);
	SMS_DEV_REGISTER_STATUS DeviceFirstRegister(std::string& ipAddress, int port, std::string& userName, std::string& password);
	BOOL DeviceNonFirstRegister(SMS_DEV_REGISTER_STATUS* registerStatus, std::string& userName, std::string& password);
	void DeviceUnregister(SMS_DEV_REGISTER_STATUS* registerStatus);
	void LogoutAllConnections();
	static VOID CALLBACK OnExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void* pUser);

	std::map<string, SMS_DEV_REGISTER_STATUS> deviceLoginMap;
	bool isInitialized = false;
};

