#pragma once
#include <cstdint>
#include <Windows.h>
#include <HCNetSDK.h>
#include <string>

class HikRealtimePlayController
{
public:
	virtual std::int64_t PlayLive(LONG loginHandle, std::int32_t channel, std::int32_t streamType);
	virtual std::int64_t PlayLiveSetStandardStream(std::int64_t hplay);
	virtual std::int64_t StopLive(std::int64_t hplay);

private:
	static VOID CALLBACK OnRealPlayESCallBack(LONG lPreviewHandle, NET_DVR_PACKET_INFO_EX* pstruPackInfo, void* pUser);
	static VOID CALLBACK OnRealPlayCallBack(LONG lPlayHandle, DWORD dwDataType, BYTE* pBuffer, DWORD dwBufSize, DWORD pUser);

};

