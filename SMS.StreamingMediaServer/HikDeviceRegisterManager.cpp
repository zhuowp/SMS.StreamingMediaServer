#include "HikDeviceRegisterManager.h"
#include  "HCNetSDK.h"
#include <iostream>
#include <time.h>
#include <algorithm>

HikDeviceRegisterManager::HikDeviceRegisterManager()
{
	isInitialized = false;
	Init();
}

HikDeviceRegisterManager::~HikDeviceRegisterManager()
{
	LogoutAllConnections();
}

void HikDeviceRegisterManager::Init()
{
	if (isInitialized)
	{
		return;
	}

	bool isInitializeSuccess = NET_DVR_Init();
	if (!isInitializeSuccess)
	{
		DWORD erroCode = NET_DVR_GetLastError();

		string output = "HIK NET_DVR_Init Failed ! LastErrorCode = " + std::to_string(erroCode) + "\n";
		cout << output;
	}

	//��������ʱ��������ʱ��
	NET_DVR_SetConnectTime(2000, 1);
	NET_DVR_SetReconnect(10000, true);

	//�����쳣��Ϣ�ص�����
	NET_DVR_SetExceptionCallBack_V30(0, NULL, OnExceptionCallBack, NULL);

	isInitialized = true;

	cout << "HIK NET_DVR_Init Successfully!\n";
}

LONG HikDeviceRegisterManager::DeviceRegister(string ipAddress, int port, string userName, string password)
{
	string devId = ipAddress + "-" + std::to_string(port);
	map<string, SMS_DEV_REGISTER_STATUS>::iterator iter = deviceLoginMap.find(devId);
	if (iter == deviceLoginMap.end())//δ��¼�����¼�豸
	{
		SMS_DEV_REGISTER_STATUS registerStatus = DeviceFirstRegister(ipAddress, port, userName, password);
		return registerStatus.loginId;
	}
	else//�ѵ�¼�������ӵ�¼����
	{
		SMS_DEV_REGISTER_STATUS* registerStatus = &(iter->second);
		if (DeviceNonfirstRegister(registerStatus, userName, password))
		{
			return (*registerStatus).loginId;
		}
		else
		{
			return -1;
		}
	}
}

SMS_DEV_REGISTER_STATUS HikDeviceRegisterManager::DeviceFirstRegister(std::string& ipAddress, int port, std::string& userName, std::string& password)
{
	SMS_DEV_REGISTER_STATUS registerStatus;
	LONG loginId = DeviceLogin(ipAddress, port, userName, password);

	string devId = ipAddress + "-" + std::to_string(port);
	//��¼ʧ����ֱ�ӷ���ʧ����Ϣ
	if (loginId < 0)
	{
		registerStatus.loginId = -1;
		cout << "�豸��" << devId << " ��¼ʧ��" << std::endl;
	}
	else
	{
		//��¼�ɹ�����ӵ�¼��Ϣ����
		registerStatus.id = devId;
		registerStatus.loginId = loginId;
		registerStatus.userName = userName;
		registerStatus.password = password;
		registerStatus.registerCount = 1;
		deviceLoginMap.insert(pair<string, SMS_DEV_REGISTER_STATUS>(devId, registerStatus));

		cout << "�豸��" << devId << " ��¼�ɹ���ע�����Ϊ��" << registerStatus.registerCount << std::endl;
	}

	return registerStatus;
}

BOOL HikDeviceRegisterManager::DeviceNonfirstRegister(SMS_DEV_REGISTER_STATUS* registerStatus, std::string& userName, std::string& password)
{
	if ((*registerStatus).userName != userName || (*registerStatus).password != password)
	{
		cout << "�豸��" << (*registerStatus).id << " ����ע��ʧ��" << std::endl;
		return false;
	}

	(*registerStatus).registerCount++;
	cout << "�豸��" << (*registerStatus).id << " ����ע��ɹ���ע�����Ϊ��" << (*registerStatus).registerCount << std::endl;
	return true;
}

LONG HikDeviceRegisterManager::DeviceLogin(std::string& ipAddress, int port, std::string& userName, std::string& password)
{
	NET_DVR_USER_LOGIN_INFO struLoginInfo = { 0 };

	//ͬ����¼��ʽ
	struLoginInfo.bUseAsynLogin = 0;
	memcpy(struLoginInfo.sDeviceAddress, ipAddress.c_str(), ipAddress.size() >= NET_DVR_DEV_ADDRESS_MAX_LEN ? NET_DVR_DEV_ADDRESS_MAX_LEN : ipAddress.size());
	struLoginInfo.wPort = port;
	memcpy(struLoginInfo.sUserName, userName.c_str(), userName.size() >= NET_DVR_LOGIN_USERNAME_MAX_LEN ? NET_DVR_LOGIN_USERNAME_MAX_LEN : userName.size());
	memcpy(struLoginInfo.sPassword, password.c_str(), password.size() >= NET_DVR_LOGIN_PASSWD_MAX_LEN ? NET_DVR_LOGIN_PASSWD_MAX_LEN : password.size());

	NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = { 0 };

	LONG loginId = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
	if (loginId < 0)
	{
		DWORD lec = NET_DVR_GetLastError();
	}

	return loginId;
}

void HikDeviceRegisterManager::LogoutAllConnections()
{
	for (auto kvPair : deviceLoginMap)
	{
		SMS_DEV_REGISTER_STATUS registerStatus = kvPair.second;
		NET_DVR_Logout(registerStatus.loginId);
	}

	deviceLoginMap.clear();
}

bool HikDeviceRegisterManager::DeviceUnregister(string devId)
{
	map<string, SMS_DEV_REGISTER_STATUS>::iterator iter = deviceLoginMap.find(devId);
	if (iter == deviceLoginMap.end())
	{
		cout << "ϵͳ��û�е�ǰ�豸�ĵ�¼��Ϣ��ע��ʧ��" << std::endl;
		return false;
	}

	SMS_DEV_REGISTER_STATUS* registerStatus = &(iter->second);
	DeviceUnregister(registerStatus);

	return true;
}

bool HikDeviceRegisterManager::DeviceUnregister(LONG loginId)
{
	map<string, SMS_DEV_REGISTER_STATUS>::iterator iter = std::find_if(deviceLoginMap.begin(), deviceLoginMap.end(), [loginId](const std::map<string, SMS_DEV_REGISTER_STATUS>::value_type& pair) {return pair.second.loginId == loginId; });
	if (iter == deviceLoginMap.end())
	{
		cout << "ϵͳ��û�е�ǰ�豸�ĵ�¼��Ϣ��ע��ʧ��" << std::endl;
		return false;
	}

	SMS_DEV_REGISTER_STATUS* registerStatus = &(iter->second);
	DeviceUnregister(registerStatus);

	return true;
}

void HikDeviceRegisterManager::DeviceUnregister(SMS_DEV_REGISTER_STATUS* registerStatus)
{
	(*registerStatus).registerCount--;
	cout << "�豸��" << (*registerStatus).id << " ע���ɹ�����ǰע�����Ϊ��" << (*registerStatus).registerCount << std::endl;
	if ((*registerStatus).registerCount <= 0)
	{
		NET_DVR_Logout((*registerStatus).loginId);
		cout << "�豸��" << (*registerStatus).id << " �ǳ�" << std::endl;
		deviceLoginMap.erase((*registerStatus).id);
	}
}

VOID HikDeviceRegisterManager::OnExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void* pUser)
{
	switch (dwType)
	{
	case EXCEPTION_RECONNECT:
		printf("----------reconnect--------%d\n", time(NULL));
		break;
	default:
		break;
	}
}


