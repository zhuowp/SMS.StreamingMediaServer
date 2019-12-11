#include "HikDevice.h"

HikDevice::HikDevice()
{
}

HikDevice::HikDevice(std::string addr, std::uint16_t port, std::string username, std::string pwd)
{
}

HikDevice::~HikDevice()
{
}

std::int64_t HikDevice::Init()
{
	return std::int64_t();
}

std::int64_t HikDevice::Cleanup()
{
	return std::int64_t();
}

std::int64_t HikDevice::Login(std::string arg)
{
	return std::int64_t();
}

std::int64_t HikDevice::Logout()
{
	return std::int64_t();
}

std::int64_t HikDevice::DeviceArgumentNormalize(std::string arguments, std::string& normalize_arguments)
{
	return std::int64_t();
}

std::int64_t HikDevice::StreamArgumentNormalize(std::string arguments, std::string& normalize_arguments)
{
	return std::int64_t();
}

//std::int64_t HikDevice::ArgumentNormalize(std::string arguments, std::string& normalize_arguments, Json::Value normalize_template)
//{
//	return std::int64_t();
//}

std::int64_t HikDevice::PlayLive(LPPLAY_INSTANCE& out_replay_handle, std::uint16_t chn)
{
	return std::int64_t();
}

std::int64_t HikDevice::PlayLiveSetStandardStream(std::int64_t hplay)
{
	return std::int64_t();
}

std::int64_t HikDevice::StopLive(std::int64_t hplay)
{
	return std::int64_t();
}

std::int64_t HikDevice::PlayBackbyTime(LPPLAY_INSTANCE& out_replay_handle, std::uint16_t chn, std::uint64_t start_time, std::uint64_t end_time, std::uint64_t user)
{
	return std::int64_t();
}

std::int64_t HikDevice::PlayBackSetStandardStream(std::int64_t hreplay)
{
	return std::int64_t();
}

std::int64_t HikDevice::PlayBackStop(std::int64_t hreplay)
{
	return std::int64_t();
}

std::int64_t HikDevice::PlayBackSetSpeed(std::int64_t hreplay, double speed)
{
	return std::int64_t();
}

std::int64_t HikDevice::PlayBackGetSpeed(std::int64_t hreplay, int& out_speed)
{
	return std::int64_t();
}

std::int64_t HikDevice::PlayBackPause(std::int64_t hreplay)
{
	return std::int64_t();
}

std::int64_t HikDevice::PlayBackResume(std::int64_t hreplay)
{
	return std::int64_t();
}

std::int64_t HikDevice::PlayBackSeekTime(std::int64_t hreplay, std::uint64_t seek_time)
{
	return std::int64_t();
}

std::int64_t HikDevice::FindIsFileByMon(std::uint32_t chan, std::uint64_t start_time, std::uint64_t end_time, std::uint8_t* retsult)
{
	return std::int64_t();
}

std::int64_t HikDevice::FindIsFileByDay(std::uint32_t chan, std::uint64_t start_time, std::uint64_t end_time, std::string& retsult)
{
	return std::int64_t();
}

std::int64_t HikDevice::FindIsFileByDay(std::uint32_t chan, std::uint16_t year, std::uint16_t month, std::uint16_t day, std::uint16_t hour, std::uint16_t minute, std::uint16_t second, SMS_24HOURS_RECORD_STATE_t* record)
{
	return std::int64_t();
}

int HikDevice::SetFrameHandler(SMS_FRAME_HANDLER_t handler, std::int64_t hreplay, bool isLive, const void* user)
{
	return 0;
}

VOID HikDevice::fOnPlayBackESCallBack(LONG lPlayHandle, NET_DVR_PACKET_INFO_EX* struPackInfo, void* pUser)
{
	return VOID();
}

VOID HikDevice::fOnRealPlayESCallBack(LONG lPreviewHandle, NET_DVR_PACKET_INFO_EX* pstruPackInfo, void* pUser)
{
	return VOID();
}

VOID HikDevice::fOnRealPlayCallBack(LONG lPlayHandle, DWORD dwDataType, BYTE* pBuffer, DWORD dwBufSize, DWORD pUser)
{
	return VOID();
}

VOID HikDevice::fOnExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void* pUser)
{
	return VOID();
}

int HikDevice::PTZGetProfileToken(std::string arguments, std::string& token)
{
	return 0;
}

int HikDevice::PTZContinuousMove(std::string token, double pan_speed, double tilt_speed, double zoom_speed)
{
	return 0;
}

int HikDevice::PTZStop(std::string token, bool pan_tilt, bool zoom)
{
	return 0;
}

int HikDevice::PTZSetPreset(std::string token, std::string preset_token, std::string preset_name)
{
	return 0;
}

int HikDevice::PTZGetPresets(std::string token, SMS_PRESET_INFO_t preset_list[], int max_preset_num, int* preset_num)
{
	return 0;
}

int HikDevice::PTZGoToPreset(std::string token, std::string preset_token, double pan_speed, double tilt_speed, double zoom_speed)
{
	return 0;
}

int HikDevice::GetArgumentInfo(std::string arguments, int* channel, int* stream, std::int64_t* beg_time, std::int64_t* end_time)
{
	return 0;
}

void HikDevice::delay()
{
}

bool HikDevice::IsPlay(std::int64_t hreplay)
{
	return false;
}

bool HikDevice::Islogin()
{
	return false;
}
