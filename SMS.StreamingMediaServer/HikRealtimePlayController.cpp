#include "HikRealtimePlayController.h"
using namespace std;

//std::int64_t HikRealtimePlayController::PlayLive(string ipAddress, int port, string userName, string password, int channel)
//{
//	std::stringstream ss;
//	ss << __FUNCTION__;
//	if (m_LoginHandle < NULL)
//	{
//		return SMS_ERROR_HIK_NO_LOGIN;
//	}
//#if 0
//	NET_DVR_PREVIEWINFO net_dvr_previewinfo = { 0 };
//	net_dvr_previewinfo.lChannel = chn;
//	net_dvr_previewinfo.dwStreamType = out_replay_handle->stream_type;
//	net_dvr_previewinfo.dwLinkMode = 0;
//	net_dvr_previewinfo.hPlayWnd = NULL;//::GetConsoleWindow();
//	net_dvr_previewinfo.bBlocked = 0;
//	net_dvr_previewinfo.bPassbackRecord = 0;
//	net_dvr_previewinfo.byPreviewMode = 0;
//	//net_dvr_previewinfo.byStreamID[STREAM_ID_LEN];
//	net_dvr_previewinfo.byProtoType = 0;
//	//net_dvr_previewinfo.byRes1;
//	net_dvr_previewinfo.byVideoCodingType = 0;
//	//net_dvr_previewinfo.dwDisplayBufNum;
//	net_dvr_previewinfo.byRes[216];
//	auto hPlay = NET_DVR_RealPlay_V40(m_LoginHandle, &net_dvr_previewinfo/*, fOnRealPlayCallBack, &out_replay_handle*/);
//#else
//	NET_DVR_CLIENTINFO ClientInfo;
//	ClientInfo.hPlayWnd = NULL;
//	ClientInfo.lChannel = chn;
//	ClientInfo.lLinkMode = out_replay_handle->stream_type == 0 ? 0 : 1 << 31;
//	ClientInfo.sMultiCastIP = NULL;
//
//	auto hPlay = NET_DVR_RealPlay_V30(m_LoginHandle, &ClientInfo, NULL, NULL, TRUE);
//#endif // 0
//
//	if (hPlay >= 0)
//	{
//		out_replay_handle->hPlay = hPlay;
//		{
//			std::lock_guard<std::recursive_mutex> sync(m_live_play_lock);
//			auto it = m_map_live_play.find(hPlay);
//			if (it != m_map_live_play.end())
//			{
//				if (it->second != NULL)
//				{
//					delete it->second;
//					it->second = NULL;
//				}
//				m_map_live_play.erase(it);
//			}
//			else
//			{
//				m_map_live_play.insert(std::make_pair(hPlay, out_replay_handle));
//			}
//		}
//
//#if isSaveFile
//		std::stringstream filesName;
//		filesName << this << ".h265";
//		out_replay_handle->files = std::ofstream(filesName.str(), std::ios::binary);
//#endif // 0
//
//		OutPutDebug("NET_DVR_RealPlay_V40 ok");
//	}
//	else
//	{
//		auto lec = NET_DVR_GetLastError();
//		ss << " NET_DVR_RealPlay_V40 failed! errorc-" << lec << " chan-" << chn << " stream_tpye-" << out_replay_handle->stream_type << std::endl;
//		OutPutDebug(ss.str());
//		return SMS_ERROR_HIK_PLAYLIVE_FAILED;
//	}
//
//	return SMS_ERROR_NONE;
//}
//
//std::int64_t HikRealtimePlayController::PlayLiveSetStandardStream(std::int64_t hplay)
//{
//	int errcode = -1;
//	bool isFind = false;
//	LPPLAY_INSTANCE p = NULL;
//	if (m_LoginHandle < NULL)
//	{
//		return SMS_ERROR_HIK_NO_LOGIN;
//	}
//	{
//		std::lock_guard<std::recursive_mutex> sync(m_live_play_lock);
//		auto pi = m_map_live_play.find(hplay);
//		if (pi != m_map_live_play.end() && pi->second)
//		{
//			isFind = true;
//			p = pi->second;
//		}
//	}
//	if (isFind)
//	{
//#if 1
//		if (NET_DVR_SetRealDataCallBack(hplay, fOnRealPlayCallBack, (DWORD)p))
//		{
//			OutPutDebug("NET_DVR_SetStandardDataCallBack ok");
//			errcode = 0;
//		}
//		else
//		{
//			auto lec = NET_DVR_GetLastError();
//			std::stringstream log;
//			log << "NET_DVR_SetStandardDataCallBack failed ! errcode = " << lec;
//			OutPutDebug(log.str());
//		}
//#else
//		if (NET_DVR_SetESRealPlayCallBack(hplay, fOnRealPlayESCallBack, p))
//		{
//			OutPutDebug("NET_DVR_SetStandardDataCallBack Seccuss");
//			//NET_DVR_MakeKeyFrame(m_LoginHandle, p->chan);
//			//NET_DVR_MakeKeyFrameSub(m_LoginHandle, p->chan);
//			NET_DVR_I_FRAME net_dvr_i_frame = { 0 };
//			net_dvr_i_frame.byStreamType = 0;
//			net_dvr_i_frame.dwChan = p->chan;
//			net_dvr_i_frame.dwSize = sizeof(NET_DVR_I_FRAME);
//			if (NET_DVR_RemoteControl(m_LoginHandle, NET_DVR_MAKE_I_FRAME, &net_dvr_i_frame, sizeof(NET_DVR_I_FRAME)))
//			{
//				OutPutDebug("NET_DVR_RemoteControl MakeKeyFrame ok");
//			}
//			errcode = 0;
//		}
//		else
//		{
//			auto lec = NET_DVR_GetLastError();
//			std::stringstream log;
//			log << "NET_DVR_SetStandardDataCallBack failed ! errcode = " << lec;
//			OutPutDebug(log.str());
//		}
//
//#endif // 0
//
//
//	}
//	else
//	{
//		OutPutDebug("PlayLiveSetStandardStream not fund hplay handle!");
//		errcode = -1;
//	}
//	return errcode;
//
//}
//
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
//VOID HikRealtimePlayController::OnRealPlayCallBack(LONG lPlayHandle, DWORD dwDataType, BYTE* pBuffer, DWORD dwBufSize, DWORD pUser)
//{
//	std::stringstream ss;
//	LPPLAY_INSTANCE p = (LPPLAY_INSTANCE)pUser;
//
//	if (p != NULL && p->framehandler != NULL)
//	{
//#if 1
//		//std::cout << pPreviewCBMsg->dwDataLen << " byte"<< std::endl;
//		p->psAnalyzer.InputData((std::uint8_t*)pBuffer, dwBufSize);
//		std::string video;
//		while (p->psAnalyzer.ReadFrame(&video, NULL, FALSE))
//		{
//			if (video.size() > 0)
//			{
//				BYTE* pP = (BYTE*)video.c_str();
//				LONG n = video.size();
//				if (SMS_CODEC_TYPE_t::SMS_CODEC_TYPE_NONE == p->codec)
//				{
//					CodecProber::Codec cc = CodecProber::Probe(pP, n);
//
//					if (cc == CodecProber::H264)
//					{
//						p->codec = SMS_CODEC_TYPE_H264;
//						OutPutDebug("SMS_CODEC_TYPE_H264");
//					}
//					else if (cc == CodecProber::HEVC)
//					{
//						p->codec = SMS_CODEC_TYPE_H265;
//						OutPutDebug("SMS_CODEC_TYPE_H265");
//					}
//					else
//					{
//						//ss << p->frame_count++ << ".bin";
//						//std::ofstream f = std::ofstream(ss.str(),std::ios::binary);
//						//f.write((char *)pP, n);
//						//ss.str("");
//						//OutPutDebug("SMS_CODEC_TYPE_NONE");
//
//					}
//				}
//				pP = (BYTE*)video.c_str();
//				n = video.size();
//				auto key_frame_flag = CodecProber::IsKeyFrame(pP, n);
//#if 0
//				if (key_frame_flag)
//				{
//					pP = (BYTE*)video.c_str();
//					n = video.size();
//					auto l = 64;
//					for (size_t i = 0; i < l && n > l; i++)
//					{
//						printf("%02X ", pP[i]);
//					}
//					printf("\n");
//				}
//#endif // 0
//
//				SMS_FRAME_INFO_t f = DefaultFrameInfo();
//				f.media_type = SMS_MEDIA_TYPE_t::SMS_MEDIA_TYPE_VIDEO;
//				f.codec = p->codec;
//				f.frame_number = p->frame_count++;
//				f.frame_type = key_frame_flag ? SMS_FRAME_TYPE_KEY_FRAME : SMS_FRAME_TYPE_NON_KEY_FRAME;
//				f.frame_timestamp = f.frame_number * 40 * 1000;
//				p->framehandler(&f, (BYTE*)video.c_str(), video.size(), p->user);
//			}
//
//			/*if (false)
//			{
//				if (SMS_CODEC_TYPE_t::SMS_CODEC_TYPE_NONE == p->codec)
//				{
//					BYTE * pP = pBuffer;
//					LONG n = dwBufSize;
//
//					CodecProber::Codec cc = CodecProber::Probe(pP, n);
//
//					if (cc == CodecProber::H264)
//					{
//						p->codec = SMS_CODEC_TYPE_H264;
//						OutPutDebug("SMS_CODEC_TYPE_H264");
//					}
//					else if (cc == CodecProber::HEVC)
//					{
//						p->codec = SMS_CODEC_TYPE_H265;
//						OutPutDebug("SMS_CODEC_TYPE_H265");
//					}
//					else
//					{
//						ss << p->frame_count++ << ".bin";
//						std::ofstream f = std::ofstream(ss.str(), std::ios::binary);
//						f.write((char *)pP, n);
//						ss.str("");
//						OutPutDebug("SMS_CODEC_TYPE_NONE");
//
//					}
//
//				}
//				SMS_FRAME_INFO_t f = DefaultFrameInfo();
//				f.codec = p->codec;
//				f.frame_number = p->frame_count++;
//				f.frame_type = SMS_FRAME_TYPE_KEY_FRAME;
//				f.media_type = SMS_MEDIA_TYPE_t::SMS_MEDIA_TYPE_VIDEO;
//				p->framehandler(&f, (BYTE*)video.c_str(), video.size(), p->user);
//			}*/
//		}
//#else
//		SMS_FRAME_INFO_t s = DefaultFrameInfo();
//		p->framehandler(&s, (std::uint8_t*)pPreviewCBMsg->pRecvdata, pPreviewCBMsg->dwDataLen, p->user);
//#endif // 0
//	}
//}
