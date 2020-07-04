#pragma once

#include <stdio.h>
#include <iostream>
#include "Windows.h" 
#include "HCNetSDK.h"
#include "plaympeg4.h"
#include <time.h>
#include "Log.h"

using namespace std;

typedef HWND(WINAPI* PROCGETCONSOLEWINDOW)();

//PROCGETCONSOLEWINDOW GetConsoleWindow;

LONG lPort; //全局的播放库port 号

void CALLBACK g_RealDataCallBack_V30(LONG lRealHandle, DWORD dwDataType, BYTE* pBuffer, DWORD dwBufSize, void* dwUser)
{
	HWND hWnd = GetConsoleWindow();
	switch (dwDataType)
	{
	case NET_DVR_SYSHEAD: //系统头

		//OutPutDebug("NET_DVR_SYSHEAD");
		//break;

		if (!PlayM4_GetPort(&lPort)) //获取播放库未使用的通道号
		{
			break;
		}

		//m_iPort = lPort;
		//第一次回调的是系统头，将获取的播放库port 号赋值给全局port，下次回调数据时即使用此port 号播放
		if (dwBufSize > 0)
		{
			if (!PlayM4_SetStreamOpenMode(lPort, STREAME_REALTIME)) //设置实时流播放模式
			{
				break;
			}

			if (!PlayM4_OpenStream(lPort, pBuffer, dwBufSize, 1024 * 1024)) //打开流接口
			{
				break;
			}

			if (!PlayM4_Play(lPort, hWnd)) //播放开始
			{
				break;
			}
		}
		break;
	case NET_DVR_STREAMDATA: //码流数据

		//OutPutDebug("NET_DVR_STREAMDATA");
		//break;

		if (dwBufSize > 0 && lPort != -1)
		{
			if (!PlayM4_InputData(lPort, pBuffer, dwBufSize))
			{
				break;
			}
		}
		break;
	default: //其他数据

		OutPutDebug("其他数据");
		break;
		if (dwBufSize > 0 && lPort != -1)
		{
			if (!PlayM4_InputData(lPort, pBuffer, dwBufSize))
			{
				break;
			}
		}
		break;
	}
}

void CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void* pUser)
{
	char tempbuf[256] = { 0 };
	switch (dwType)
	{
	case EXCEPTION_RECONNECT: //预览时重连
		printf("----------reconnect-------- % d\n", time(NULL));
		break;
	default:
		break;
	}
}

int StartPlay()
{
	NET_DVR_Init();
	//设置连接时间与重连时间
	NET_DVR_SetConnectTime(2000, 1);
	NET_DVR_SetReconnect(10000, true);
	//---------------------------------------
	// 获取控制台窗口句柄
	//HMODULE hKernel32 = GetModuleHandle("kernel32");
	//GetConsoleWindow = (PROCGETCONSOLEWINDOW)GetProcAddress(hKernel32, "GetConsoleWindow");
	//---------------------------------------
	// 注册设备
	LONG lUserID;
	NET_DVR_DEVICEINFO_V30 struDeviceInfo;
	lUserID = NET_DVR_Login_V30("192.168.28.130", 8000, "admin", "admin888", &struDeviceInfo);
	if (lUserID < 0)
	{
		printf("Login error, % d\n", NET_DVR_GetLastError());
		NET_DVR_Cleanup();
		return -1;
	}

	//---------------------------------------
	//设置异常消息回调函数
	NET_DVR_SetExceptionCallBack_V30(0, NULL, g_ExceptionCallBack, NULL);
	//---------------------------------------
	//启动预览并设置回调数据流
	LONG lRealPlayHandle;
	NET_DVR_PREVIEWINFO struPlayInfo = { 0 };
	HWND hWnd = GetConsoleWindow();
	//struPlayInfo.hPlayWnd = hWnd; //需要SDK 解码时句柄设为有效值，仅取流不解码时可设为空
	struPlayInfo.lChannel = 1; //预览通道号
	struPlayInfo.dwStreamType = 0; //0-主码流，1-子码流，2-码流3，3-码流4，以此类推
	struPlayInfo.dwLinkMode = 0; //0- TCP 方式，1- UDP 方式，2- 多播方式，3- RTP 方式，4-RTP/RTSP，5-RSTP/HTTP
	struPlayInfo.bBlocked = 1; //0- 非阻塞取流，1- 阻塞取流
	lRealPlayHandle = NET_DVR_RealPlay_V40(lUserID, &struPlayInfo, g_RealDataCallBack_V30, NULL);
	if (lRealPlayHandle < 0)
	{
		printf("NET_DVR_RealPlay_V40 error\n");
		NET_DVR_Logout(lUserID);
		NET_DVR_Cleanup();
		return 0;
	}

	Sleep(100000);

	//---------------------------------------
	//关闭预览
	NET_DVR_StopRealPlay(lRealPlayHandle);

	//注销用户
	NET_DVR_Logout(lUserID);
	NET_DVR_Cleanup();
	return 0;
}
