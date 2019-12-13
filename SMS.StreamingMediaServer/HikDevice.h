#pragma once
#include "windows.h"
#include <string>
#include <mutex>
#include <map>
#include <atomic>
#include "PublicDef.h"
#include "PsAnalyzer.h"
#include "HCNetSDK.h"

typedef struct tagPlayInstance
{
	tagPlayInstance()
	{
		getstream_time_ss.resize(1024);
	}
	std::int64_t				hPlay = NULL;			//���ž��
	bool						isLive = true;			//�Ƿ�Ϊʵʱ���� 1��ʾʵʱ���ţ�2��ʾ��ʱ��ط�
	std::int32_t				stream_type = 0;		//������������
	std::int32_t				chan = 1;				//ͨ��
	time_t						start_time;				//��ʼʱ��
	time_t						end_time;				//����ʱ��
	std::uint64_t				play_pos = 0;			//�طŽ���
	double  					play_speed = 0;			//�����ݴ����ٶȣ������ٶ�
	std::uint64_t				device = NULL;			//
	SMS_FRAME_HANDLER_t		framehandler = NULL;	//���ݻص�����
	const void* user = NULL;			//�û�����
	HANDLE						hEvent = NULL;			//������ͣ���ָ�
	std::atomic_uint64_t		tick_count = 0;			//��¼��ǰʱ��̶�
	std::atomic_uint64_t		abs_count = 0;			//���ʱ��̶�
	std::atomic_uint64_t		send_count = 0;			//��¼����ÿ������ʱ��
	std::atomic_uint64_t		frame_count = 0;		//֡������
	std::atomic_uint64_t		temp_time = 0;			//��¼��һ֡����ʱ���
	PsAnalyzer					psAnalyzer;
	SMS_CODEC_TYPE_t			codec = SMS_CODEC_TYPE_t::SMS_CODEC_TYPE_NONE;
	std::ofstream				files;
	std::int64_t				getstream_time = GetTickCount64();
	std::string					getstream_time_ss = "";
	bool						is_print = false;

}PLAY_INSTANCE, * LPPLAY_INSTANCE;

class HikDevice
{
public:
	HikDevice();
	HikDevice(std::string addr, std::uint16_t port, std::string username, std::string pwd);
	~HikDevice();

	static std::int64_t Init();
	static std::int64_t Cleanup();

	virtual std::int64_t Login(std::string arg);
	virtual std::int64_t Logout();

	static  std::int64_t DeviceArgumentNormalize(std::string arguments, std::string& normalize_arguments);
	static  std::int64_t StreamArgumentNormalize(std::string arguments, std::string& normalize_arguments);
	//static  std::int64_t ArgumentNormalize(std::string arguments, std::string& normalize_arguments, Json::Value normalize_template);

	virtual std::int64_t PlayLive(LPPLAY_INSTANCE& out_replay_handle, std::uint16_t chn);
	virtual std::int64_t PlayLiveSetStandardStream(std::int64_t hplay);
	virtual std::int64_t StopLive(std::int64_t hplay);

	virtual std::int64_t PlayBackbyTime(LPPLAY_INSTANCE& out_replay_handle, std::uint16_t chn, std::uint64_t start_time, std::uint64_t end_time, std::uint64_t user);
	virtual std::int64_t PlayBackSetStandardStream(std::int64_t hreplay);
	virtual std::int64_t PlayBackStop(std::int64_t hreplay);

	virtual std::int64_t PlayBackSetSpeed(std::int64_t hreplay, double speed);
	virtual std::int64_t PlayBackGetSpeed(std::int64_t hreplay, int& out_speed);

	virtual std::int64_t PlayBackPause(std::int64_t hreplay);
	virtual std::int64_t PlayBackResume(std::int64_t hreplay);

	virtual std::int64_t PlayBackSeekTime(std::int64_t hreplay, std::uint64_t seek_time);
	virtual std::int64_t FindIsFileByMon(std::uint32_t  chan, std::uint64_t start_time, std::uint64_t end_time, std::uint8_t* retsult);
	virtual std::int64_t FindIsFileByDay(std::uint32_t  chan, std::uint64_t start_time, std::uint64_t end_time, std::string& retsult);
	virtual std::int64_t FindIsFileByDay(std::uint32_t  chan, std::uint16_t year, std::uint16_t month, std::uint16_t day, std::uint16_t hour, std::uint16_t minute, std::uint16_t second, SMS_24HOURS_RECORD_STATE_t* record);

	//static VOID CALLBACK fPlayDataCallBack_V40(LONG lPlayHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser);

	static VOID CALLBACK fOnPlayBackESCallBack(LONG lPlayHandle, NET_DVR_PACKET_INFO_EX* struPackInfo, void* pUser);

	static VOID CALLBACK fOnRealPlayESCallBack(LONG lPreviewHandle, NET_DVR_PACKET_INFO_EX* pstruPackInfo, void* pUser);

	static VOID CALLBACK fOnRealPlayCallBack(LONG lPlayHandle, DWORD dwDataType, BYTE* pBuffer, DWORD dwBufSize, DWORD/*void**/ pUser);

	static VOID CALLBACK fOnExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void* pUser);


	int SetFrameHandler(SMS_FRAME_HANDLER_t handler, std::int64_t hreplay, bool isLive, const void* user);

	virtual int PTZGetProfileToken(std::string arguments, std::string& token);

	virtual int PTZContinuousMove(std::string token, double pan_speed, double tilt_speed, double zoom_speed);

	virtual int PTZStop(std::string token, bool pan_tilt, bool zoom);

	virtual int PTZSetPreset(std::string token, std::string preset_token, std::string preset_name);

	virtual int PTZGetPresets(std::string token, SMS_PRESET_INFO_t preset_list[], int max_preset_num, int* preset_num);

	virtual int PTZGoToPreset(std::string token, std::string preset_token, double pan_speed, double tilt_speed, double zoom_speed);

	static  int GetArgumentInfo(std::string arguments, int* channel, int* stream, std::int64_t* beg_time, std::int64_t* end_time);

	void delay();

	bool IsPlay(std::int64_t hreplay);

	bool Islogin();

private:

	std::string						m_Addr = "";
	std::uint16_t					m_Port = 0;
	std::string						m_username = "";
	std::string						m_pass = "";
	bool							m_Islogin = false;
	long							m_LoginHandle = 0;

	static bool						s_isInit;
	std::recursive_mutex			m_replay_lock;
	std::map <std::int64_t, LPPLAY_INSTANCE> m_map_replay;
	std::recursive_mutex			m_live_play_lock;
	std::map <std::int64_t, LPPLAY_INSTANCE> m_map_live_play;

};


