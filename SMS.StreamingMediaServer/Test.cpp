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

LONG lPort; //ȫ�ֵĲ��ſ�port ��

void CALLBACK g_RealDataCallBack_V30(LONG lRealHandle, DWORD dwDataType, BYTE* pBuffer, DWORD dwBufSize, void* dwUser)
{
	HWND hWnd = GetConsoleWindow();
	switch (dwDataType)
	{
	case NET_DVR_SYSHEAD: //ϵͳͷ

		//OutPutDebug("NET_DVR_SYSHEAD");
		//break;

		if (!PlayM4_GetPort(&lPort)) //��ȡ���ſ�δʹ�õ�ͨ����
		{
			break;
		}

		//m_iPort = lPort;
		//��һ�λص�����ϵͳͷ������ȡ�Ĳ��ſ�port �Ÿ�ֵ��ȫ��port���´λص�����ʱ��ʹ�ô�port �Ų���
		if (dwBufSize > 0)
		{
			if (!PlayM4_SetStreamOpenMode(lPort, STREAME_REALTIME)) //����ʵʱ������ģʽ
			{
				break;
			}

			if (!PlayM4_OpenStream(lPort, pBuffer, dwBufSize, 1024 * 1024)) //�����ӿ�
			{
				break;
			}

			if (!PlayM4_Play(lPort, hWnd)) //���ſ�ʼ
			{
				break;
			}
		}
		break;
	case NET_DVR_STREAMDATA: //��������

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
	default: //��������

		OutPutDebug("��������");
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
	case EXCEPTION_RECONNECT: //Ԥ��ʱ����
		printf("----------reconnect-------- % d\n", time(NULL));
		break;
	default:
		break;
	}
}

int StartPlay()
{
	NET_DVR_Init();
	//��������ʱ��������ʱ��
	NET_DVR_SetConnectTime(2000, 1);
	NET_DVR_SetReconnect(10000, true);
	//---------------------------------------
	// ��ȡ����̨���ھ��
	//HMODULE hKernel32 = GetModuleHandle("kernel32");
	//GetConsoleWindow = (PROCGETCONSOLEWINDOW)GetProcAddress(hKernel32, "GetConsoleWindow");
	//---------------------------------------
	// ע���豸
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
	//�����쳣��Ϣ�ص�����
	NET_DVR_SetExceptionCallBack_V30(0, NULL, g_ExceptionCallBack, NULL);
	//---------------------------------------
	//����Ԥ�������ûص�������
	LONG lRealPlayHandle;
	NET_DVR_PREVIEWINFO struPlayInfo = { 0 };
	HWND hWnd = GetConsoleWindow();
	//struPlayInfo.hPlayWnd = hWnd; //��ҪSDK ����ʱ�����Ϊ��Чֵ����ȡ��������ʱ����Ϊ��
	struPlayInfo.lChannel = 1; //Ԥ��ͨ����
	struPlayInfo.dwStreamType = 0; //0-��������1-��������2-����3��3-����4���Դ�����
	struPlayInfo.dwLinkMode = 0; //0- TCP ��ʽ��1- UDP ��ʽ��2- �ಥ��ʽ��3- RTP ��ʽ��4-RTP/RTSP��5-RSTP/HTTP
	struPlayInfo.bBlocked = 1; //0- ������ȡ����1- ����ȡ��
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
	//�ر�Ԥ��
	NET_DVR_StopRealPlay(lRealPlayHandle);

	//ע���û�
	NET_DVR_Logout(lUserID);
	NET_DVR_Cleanup();
	return 0;
}
