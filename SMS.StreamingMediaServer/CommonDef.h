#pragma once
#include <Windows.h>

typedef struct DateTime
{
	WORD wYear;		//!��
	WORD wMonth;		//!��
	WORD wDay;			//!��
	WORD wHour;		//!ʱ
	WORD wMinute;		//!��
	WORD wSecond;		//!��
	WORD wZoneTime;	//!ʱ�� 
	WORD wRes;			//!����
}SMS_DATE_TIME, * LPSMS_DATE_TIME;

typedef enum LogLevel
{
	NONE = 0,	// ��������־
	TRACE = 1,	// ����trace�����߼������־
	DEBUG = 2,	// ����debug�����߼������־
	INFO = 3,	// ����info �����߼������־
	WARN = 4,	// ����warn �����߼������־
	ERROR_LEVEL = 5,	// ����error�����߼������־
	CRITICAL = 6		// 
}SMS_LOG_LEVEL;
