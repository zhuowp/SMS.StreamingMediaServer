#pragma once
#include <cstdint>
#include <Windows.h>
#include <HCNetSDK.h>
#include <string>
#include "DeviceCommonDef.h"
using namespace std;

class HikRealtimePlayController
{
public:
	virtual std::int64_t PlayLive(string ipAddress, int port, string userName, string password, int channel, int streamType);
	virtual bool PlayLiveSetStandardStream(DevRealtimePlayStatus playInfo);
	virtual std::int64_t StopLive(std::int64_t hplay);

private:
	static VOID CALLBACK OnRealPlayESCallBack(LONG lPreviewHandle, NET_DVR_PACKET_INFO_EX* pstruPackInfo, void* pUser);
	static VOID CALLBACK OnRealPlayCallBack(LONG lPlayHandle, DWORD dwDataType, BYTE* pBuffer, DWORD dwBufSize, DWORD pUser);

	map<LONG, DevRealtimePlayStatus> realtimePlayStatusMap;
};

