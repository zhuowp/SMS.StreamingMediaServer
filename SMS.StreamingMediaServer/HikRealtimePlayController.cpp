#include "HikRealtimePlayController.h"
#include "HikDeviceRegisterManager.h"
#include "PublicDef.h"
#include "CodecProber.h"
#include "PsAnalyzer.h"
using namespace std;

std::int64_t HikRealtimePlayController::PlayLive(string ipAddress, int port, string userName, string password, int channel, int streamType)
{
	HikDeviceRegisterManager hikDevRegisterManager;
	int loginId = hikDevRegisterManager.DeviceRegister(ipAddress, port, userName, password);
	if (loginId < 0)
	{
		return -1;
	}

	NET_DVR_CLIENTINFO ClientInfo;
	ClientInfo.hPlayWnd = NULL;
	ClientInfo.lChannel = channel;
	ClientInfo.lLinkMode = streamType == 0 ? 0 : 1 << 31;
	ClientInfo.sMultiCastIP = NULL;

	LONG playHandle = NET_DVR_RealPlay_V30(loginId, &ClientInfo, NULL, NULL, TRUE);
	if (playHandle < 0)
	{
		DWORD errorCode = NET_DVR_GetLastError();
		return -1;
	}

	DevRealtimePlayStatus playStatus;
	playStatus.playHandle = playHandle;
	playStatus.loginId = loginId;

	realtimePlayStatusMap.insert(pair<LONG, DevRealtimePlayStatus>(playHandle, playStatus));
}

bool HikRealtimePlayController::PlayLiveSetStandardStream(DevRealtimePlayStatus realtimePlayInfo)
{
	if (NET_DVR_SetESRealPlayCallBack(realtimePlayInfo.playHandle, OnRealPlayESCallBack, &realtimePlayInfo))
	{
		NET_DVR_I_FRAME net_dvr_i_frame = { 0 };
		net_dvr_i_frame.byStreamType = 0;
		net_dvr_i_frame.dwChan = realtimePlayInfo.channel;
		net_dvr_i_frame.dwSize = sizeof(NET_DVR_I_FRAME);
		if (NET_DVR_RemoteControl(realtimePlayInfo.loginId, NET_DVR_MAKE_I_FRAME, &net_dvr_i_frame, sizeof(NET_DVR_I_FRAME)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		auto lec = NET_DVR_GetLastError();
		return false;
	}
}

//std::int64_t HikRealtimePlayController::StopLive(std::int64_t hplay)
//{
//	std::lock_guard<std::recursive_mutex> sync(m_live_play_lock);
//	auto pi = m_map_live_play.find(hplay);
//	if (pi != m_map_live_play.end() && pi->second)
//	{
//		if (NET_DVR_StopRealPlay(pi->first))
//		{
//			errcode = 0;
//		}
//		else
//		{
//			auto lec = NET_DVR_GetLastError();
//			std::stringstream log;
//			log << "NET_DVR_StopRealPlay failed ! errcode = " << lec;
//			OutPutDebug(log.str());
//		}
//#if isSaveFile
//		//if (pi->second->files.is_open())
//		{
//			pi->second->files.close();
//		}
//#endif // 0
//
//		delete pi->second;
//		pi->second = nullptr;
//		m_map_live_play.erase(pi);
//	}
//}
//
//VOID HikRealtimePlayController::OnRealPlayESCallBack(LONG lPreviewHandle, NET_DVR_PACKET_INFO_EX* pstruPackInfo, void* pUser)
//{
//	std::stringstream ss;
//	LPPLAY_INSTANCE p = (LPPLAY_INSTANCE)pUser;
//	if (!pstruPackInfo)
//	{
//		return;
//	}
//	if (!p->is_print)
//	{
//		p->is_print = true;
//		ss << " Onframe First Frame Time  = " << GetTickCount64() << " Sub Time = " << GetTickCount64() - p->getstream_time << std::endl;
//
//
//		OutPutDebug(p->getstream_time_ss + ss.str());
//	}
//	auto frame_type = pstruPackInfo->dwPacketType;
//	if (0 == frame_type || 10 == frame_type || 11 == frame_type)
//	{//Ë½ÓÐ°ü¡¢ÒôÆµ
//		//if (0 == frame_type)
//		//{
//		//	ss << "frame_type0" << ".bin";
//		//	std::ofstream f = std::ofstream(ss.str(), std::ios::binary);
//		//	f.write((char*)pstruPackInfo->pPacketBuffer, pstruPackInfo->dwPacketSize);
//		//	ss.str("");
//		//}
//		return;
//	}
//#if isSaveFile
//	p->files.write((char*)pstruPackInfo->pPacketBuffer, pstruPackInfo->dwPacketSize);
//#endif // 0
//	if (SMS_CODEC_TYPE_t::SMS_CODEC_TYPE_NONE == p->codec)
//	{
//		BYTE* pP = pstruPackInfo->pPacketBuffer;
//		LONG n = pstruPackInfo->dwPacketSize;
//
//		CodecProber::Codec cc = CodecProber::Probe(pP, n);
//
//		if (cc == CodecProber::H264)
//		{
//			p->codec = SMS_CODEC_TYPE_H264;
//			OutPutDebug("SMS_CODEC_TYPE_H264");
//		}
//		else if (cc == CodecProber::HEVC)
//		{
//			p->codec = SMS_CODEC_TYPE_H265;
//			OutPutDebug("SMS_CODEC_TYPE_H265");
//		}
//		else
//		{
//			//ss << p->frame_count++ << ".bin";
//			//std::ofstream f = std::ofstream(ss.str(),std::ios::binary);
//			//f.write((char *)pP, n);
//			//ss.str("");
//			//OutPutDebug("SMS_CODEC_TYPE_NONE");
//
//		}
//
//	}
//#if 0
//	if (frame_type == 1)
//	{
//		BYTE* pP = pstruPackInfo->pPacketBuffer;
//		int N = min(pstruPackInfo->dwPacketSize, 16);
//		for (int i = 0; i < N; ++i)
//		{
//			printf("%02X ", pP[i]);
//		}
//		printf("\n");
//	}
//#endif 
//	if (p != NULL && p->framehandler != NULL)
//	{
//		char s_ctime[64] = { 0 };
//		sprintf(s_ctime, "%d-%d-%dT%d:%d:%d", pstruPackInfo->dwYear, pstruPackInfo->dwMonth, pstruPackInfo->dwDay, pstruPackInfo->dwHour, pstruPackInfo->dwMinute, pstruPackInfo->dwSecond);
//		auto s_itime = standard_to_stamp(s_ctime);
//		SMS_FRAME_INFO_t f = DefaultFrameInfo();
//		f.media_type = SMS_MEDIA_TYPE_t::SMS_MEDIA_TYPE_VIDEO;
//		f.codec = p->codec;
//		if ((p->frame_count + 1) != pstruPackInfo->dwFrameNum)
//		{
//			ss << "DROP FRAME COUT = " << pstruPackInfo->dwFrameNum - p->frame_count << " PREVIOUS FRAME = " << p->frame_count << "  CURRENT FRAME = " << pstruPackInfo->dwFrameNum << std::endl;
//			OutPutDebug(ss.str());
//		}
//		p->frame_count = pstruPackInfo->dwFrameNum;
//		f.frame_number = p->frame_count;
//		f.frame_type = (1 == frame_type ? SMS_FRAME_TYPE_KEY_FRAME : SMS_FRAME_TYPE_NON_KEY_FRAME);
//		f.frame_timestamp = s_itime * 1000 * 1000;
//		p->framehandler(&f, (BYTE*)pstruPackInfo->pPacketBuffer, pstruPackInfo->dwPacketSize, p->user);
//
//	}
//}
//

VOID HikRealtimePlayController::OnRealPlayCallBack(LONG lPlayHandle, DWORD dwDataType, BYTE* pBuffer, DWORD dwBufSize, DWORD pUser)
{
	LPSMS_DEV_REALTIME_PLAY_STATUS p = (LPSMS_DEV_REALTIME_PLAY_STATUS)pUser;

	PsAnalyzer psAnalyzer;
	if (p != NULL)
	{
		psAnalyzer.InputData((std::uint8_t*)pBuffer, dwBufSize);
		std::string video;
		while (psAnalyzer.ReadFrame(&video, NULL, FALSE))
		{
			if (video.size() > 0)
			{
				BYTE* pP = (BYTE*)video.c_str();
				LONG n = video.size();
				if (SMS_CODEC_TYPE_t::SMS_CODEC_TYPE_NONE == p->codec)
				{
					CodecProber::Codec cc = CodecProber::Probe(pP, n);

					if (cc == CodecProber::H264)
					{
						p->codec = SMS_CODEC_TYPE_H264;
					}
					else if (cc == CodecProber::HEVC)
					{
						p->codec = SMS_CODEC_TYPE_H265;
					}
				}
				pP = (BYTE*)video.c_str();
				n = video.size();
				auto key_frame_flag = CodecProber::IsKeyFrame(pP, n);

				SMS_FRAME_INFO_t f = DefaultFrameInfo();
				f.media_type = SMS_MEDIA_TYPE_t::SMS_MEDIA_TYPE_VIDEO;
				f.codec = p->codec;
				f.frame_number = p->frame_count++;
				f.frame_type = key_frame_flag ? SMS_FRAME_TYPE_KEY_FRAME : SMS_FRAME_TYPE_NON_KEY_FRAME;
				f.frame_timestamp = f.frame_number * 40 * 1000;
				p->framehandler(&f, (BYTE*)video.c_str(), video.size(), p->user);
			}
		}
	}
}
