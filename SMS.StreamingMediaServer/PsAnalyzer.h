#ifndef __PS_ANALYZER_H__
#define	__PS_ANALYZER_H__

#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <Windows.h>

class PsAnalyzer
{
public:
	enum AudioType { UNKNOWN_AUDIO, AAC, G711, G722_1, G723_1, G729 };
	enum VideoType { UNKNOWN_VIDEO, H264, MPEG4 };

	PsAnalyzer();

	virtual ~PsAnalyzer();

	virtual BYTE  GetVideoType();
	virtual BYTE  GetAudioType();

	virtual LONG Clear();
	virtual LONG InputData(LPCVOID pData, LONG nSize);
	virtual LONG InputData(LPCVOID pData, LONG nSize, BOOL& bContinue);
	virtual BOOL ReadFrame(std::string* video, std::string* audio, BOOL bUntilNoBuf);
	virtual LONG BufSize();
	virtual BOOL BufSize(LONG nSize);
	virtual BOOL LoadFrame(std::string* video, std::string* audio, LONG64* pts, BOOL* iframe);
protected:

	BOOL LoadNextFrame(std::string* video, std::string* audio, BOOL bUntilNoBuf);

	VOID PrintMark(UINT32 mark);
	BOOL ResetStreamMap(BYTE* p, LONG n);

	INT64 GetPTS(BYTE* p, LONG n);
	LONG  GetFrameType(BYTE* pData, LONG nSize);

protected:
	std::string				m_Buffer;
	std::map<BYTE, BYTE>	m_StreamMap;
	CRITICAL_SECTION		m_CriticalSection;
	LONG					m_MaxBufSize;
	BYTE					m_VideoType = 0;
	BYTE					m_AudioType = 0;
};



#endif // !__PS_ANALYZER_H__
