#pragma once
#include <string>
#include <Windows.h>
using namespace std;

typedef struct DevRegisterStatus
{
	string id;
	string userName;
	string password;
	LONG loginId;
	int registerCount;
}SMS_DEV_REGISTER_STATUS, * LPSMS_DEV_REGISTER_STATUS;

typedef struct DevRealtimePlayStatus
{
	LONG playHandle;
	LONG loginId;
	string ip;
	int channel;
	int port;
}SMS_DEV_REALTIME_PLAY_STATUS, * LPSMS_DEV_REALTIME_PLAY_STATUS;