#pragma once
#include <Windows.h>

typedef struct DateTime
{
	WORD wYear;		//!年
	WORD wMonth;		//!月
	WORD wDay;			//!日
	WORD wHour;		//!时
	WORD wMinute;		//!分
	WORD wSecond;		//!秒
	WORD wZoneTime;	//!时区 
	WORD wRes;			//!保留
}SMS_DATE_TIME, * LPSMS_DATE_TIME;

typedef enum LogLevel
{
	NONE = 0,	// 不生成日志
	TRACE = 1,	// 生成trace及更高级别的日志
	DEBUG = 2,	// 生成debug及更高级别的日志
	INFO = 3,	// 生成info 及更高级别的日志
	WARN = 4,	// 生成warn 及更高级别的日志
	ERROR_LEVEL = 5,	// 生成error及更高级别的日志
	CRITICAL = 6		// 
}SMS_LOG_LEVEL;
