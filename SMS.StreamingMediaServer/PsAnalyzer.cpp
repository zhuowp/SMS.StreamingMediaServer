#include "PsAnalyzer.h"
#include <process.h>

PsAnalyzer::PsAnalyzer()
{
	m_MaxBufSize = 1024 * 1024 * 5;
}

PsAnalyzer::~PsAnalyzer()
{
}

BYTE PsAnalyzer::GetVideoType()
{
	return m_VideoType;
}

BYTE PsAnalyzer::GetAudioType()
{
	return m_AudioType;
}

LONG PsAnalyzer::Clear()
{
	m_Buffer.clear();
	return 0;
}

LONG PsAnalyzer::BufSize()
{
	LONG n = m_Buffer.size();
	return n;
}

BOOL PsAnalyzer::BufSize(LONG nSize)
{
	if (nSize > 0)
	{
		m_MaxBufSize = nSize;
	}

	return (nSize > 0) ? TRUE : FALSE;
}

LONG PsAnalyzer::InputData(LPCVOID pData, LONG nSize)
{
	if (nSize <= 0 || pData == NULL)
	{
		return -1;
	}

	if (m_Buffer.size() > 1024 * 1024 * 5)
	{
		m_Buffer.clear();
	}

	m_Buffer.append(reinterpret_cast<LPCSTR>(pData), nSize);
	return 0;
}

LONG PsAnalyzer::InputData(LPCVOID pData, LONG nSize, BOOL& bContinue)
{
	if (nSize <= 0 || pData == NULL)
	{
		return -1;
	}

	while (bContinue && LONG(m_Buffer.size()) > m_MaxBufSize)
	{
		Sleep(10);
	}

	m_Buffer.append(reinterpret_cast<LPCSTR>(pData), nSize);
	return 0;
}

BOOL PsAnalyzer::ReadFrame(std::string* video, std::string* audio, BOOL bUntilNoBuf)
{
	BOOL r = LoadNextFrame(video, audio, bUntilNoBuf);

	return r;
}

VOID PsAnalyzer::PrintMark(UINT32 mark)
{
	union
	{
		UINT32 value;
		BYTE   v[4];
	}m;
	m.value = mark;
	printf("[%02X %02X %02X %02X]\n", m.v[0], m.v[1], m.v[2], m.v[3]);
}

BOOL PsAnalyzer::LoadNextFrame(std::string* video, std::string* audio, BOOL bUntilNoBuf)
{
	if (video) video->clear();
	if (audio) audio->clear();

	BYTE* p = (BYTE*)m_Buffer.c_str();
	LONG  n = m_Buffer.size();

	LONG skip = 0;
	BOOL isHeaderFound = FALSE;

	BYTE* p_bak = p;
	LONG  n_bak = n;
	BOOL  copy = bUntilNoBuf;

	while (n >= 4)
	{
		UINT32 m = *reinterpret_cast<UINT32*>(p);

		if (m == 'HKMI')
		{
			p += 40;
			n -= 40;
		}
		else if (m == 0xBA010000)
		{
			if (isHeaderFound)
			{
				if (!copy)
				{
					isHeaderFound = FALSE;
					copy = TRUE;
					p = p_bak;
					n = n_bak;
					skip = 0;
					continue;
				}

				memmove(&m_Buffer[0], p, n);
				m_Buffer.resize(n);
				return TRUE;
			}
			isHeaderFound = TRUE;

			LONG skip = 14 + ((n >= 14) ? (p[13] & 0x07) : 0);
			p += skip;
			n -= skip;
		}
		else if (m == 0xBB010000 || m == 0xBC010000 || m == 0xBD010000 || m == 0xBF010000 || m == 0xFF010000 || ((m & 0xE0FFFFFF) == 0xC0010000) || ((m & 0xF0FFFFFF) == 0xE0010000))
		{
			bool is_audio = ((m & 0xE0FFFFFF) == 0xC0010000);
			bool is_video = ((m & 0xF0FFFFFF) == 0xE0010000);

			UINT16 size = (n >= 6) ? (p[4] << 8) + p[5] : 0;
			if (n < 6 + size)
			{
				return FALSE;
			}

			if (is_audio || is_video)
			{
				LONG skip = 4/*m*/ + 2/*size*/ + 3/*info*/ + p[8]/*pts|dts*/;
				std::string* frame = is_video ? video : audio;
				if (copy && 6 + size - skip > 0 && frame)// && (m_StreamMap.find(p[3]) != m_StreamMap.end()))
				{
					frame->append(reinterpret_cast<char*>(p + skip), 6 + size - skip);
				}
			}
			else if (m == 0xBC010000 && n >= 12)
			{
				ResetStreamMap(p, n);
			}

			p += size + 6;
			n -= size + 6;

			if (bUntilNoBuf && n == 0)
			{
				return TRUE;
			}
		}
		else
		{
			skip++;
			p++;
			n--;
		}
	}

	if (skip > 0)
	{
		char msg[128] = { 0 };
		sprintf_s(msg, "Skip = %d\n", skip);
		OutputDebugStringA(msg);
	}

	return FALSE;
}


BOOL PsAnalyzer::LoadFrame(std::string* video, std::string* audio, LONG64* pts, BOOL* iframe)
{
	if (video) video->clear();
	if (audio) audio->clear();
	if (pts)    *pts = 0;
	if (iframe) *iframe = FALSE;

	BYTE* p = (BYTE*)m_Buffer.c_str();
	LONG  n = m_Buffer.size();

	LONG skip = 0;
	BOOL isHeaderFound = FALSE;

	BYTE* p_bak = p;
	LONG  n_bak = n;
	BOOL  copy = FALSE;

	BYTE* pts_pkt_ptr = NULL;
	LONG  pts_pkt_len = 0;

	LONG  iFrameType = -1;

	while (n >= 4)
	{
		UINT32 m = *reinterpret_cast<UINT32*>(p);

		if (m == 'HKMI')
		{
			p += 40;
			n -= 40;
		}
		else if (m == 0xBA010000)
		{
			if (isHeaderFound)
			{
				if (!copy)
				{
					isHeaderFound = FALSE;
					copy = TRUE;
					p = p_bak;
					n = n_bak;
					skip = 0;
					continue;
				}

				if (pts)
				{
					*pts = GetPTS(pts_pkt_ptr, pts_pkt_len);
				}
				if (iframe)
				{
					*iframe = (iFrameType == 1) ? TRUE : FALSE;
				}

				memmove(&m_Buffer[0], p, n);
				m_Buffer.resize(n);
				return TRUE;
			}

			isHeaderFound = TRUE;

			LONG skip = 14 + ((n >= 14) ? (p[13] & 0x07) : 0);
			p += skip;
			n -= skip;
		}
		else if (m == 0xBB010000 || m == 0xBC010000 || m == 0xBD010000 || m == 0xBF010000 || m == 0xFF010000 || ((m & 0xE0FFFFFF) == 0xC0010000) || ((m & 0xF0FFFFFF) == 0xE0010000))
		{
			bool is_audio = ((m & 0xE0FFFFFF) == 0xC0010000);
			bool is_video = ((m & 0xF0FFFFFF) == 0xE0010000);

			UINT16 size = (n >= 6) ? (p[4] << 8) + p[5] : 0;
			if (n < 6 + size)
			{
				return FALSE;
			}

			if (is_audio || is_video)
			{
				LONG skip = 4/*m*/ + 2/*size*/ + 3/*info*/ + p[8]/*pts|dts*/;
				std::string* frame = is_video ? video : audio;
				if (copy && 6 + size - skip > 0 && frame)// && (m_StreamMap.find(p[3]) != m_StreamMap.end()))
				{
					frame->append(reinterpret_cast<char*>(p + skip), 6 + size - skip);
				}

				if (is_video && iFrameType == -1 && 6 + size - skip > 0)
				{
					iFrameType = GetFrameType(p + skip, 6 + size - skip);
				}
			}
			else if (m == 0xBC010000 && n >= 12)
			{
				ResetStreamMap(p, n);
			}

			if (is_video && (p[7] & 0x80) && isHeaderFound && !pts_pkt_ptr)
			{
				pts_pkt_ptr = p + 9;
				pts_pkt_len = n - 9;
			}

			p += size + 6;
			n -= size + 6;
		}
		else
		{
			skip++;
			p++;
			n--;
		}
	}

	if (skip > 0)
	{
		char msg[128] = { 0 };
		sprintf_s(msg, "Skip = %d\n", skip);
		//OutputDebugStringA(msg);
	}

	return FALSE;
}

BOOL PsAnalyzer::ResetStreamMap(BYTE* p, LONG n)
{
	//return TRUE; // !!!!!!!!!!!!!!!!!!!

	if (!p || n < 12)
	{
		return FALSE;
	}

	UINT32 m = *reinterpret_cast<UINT32*>(p);
	if (m != 0xBC010000)
	{
		return FALSE;
	}

	//m_StreamMap.clear();

	LONG jn = 10 + (p[8] << 8) + p[9];
	LONG mn = (p[jn] << 8) + p[jn + 1];

	BOOL find_video = FALSE;
	BOOL find_audio = FALSE;

	jn += 2;

	while (mn >= 4)
	{
		BYTE type = p[jn];
		BYTE id = p[jn + 1];

		if (((id & 0xE0) == 0xC0) && !find_audio)
		{
			m_AudioType = type;
			//m_StreamMap[id] = type;
			find_audio = TRUE;
		}
		if (((id & 0xF0) == 0xE0) && !find_video)
		{
			m_VideoType = type;
			//m_StreamMap[id] = type;
			find_video = TRUE;
		}

		UINT16 k = (p[jn + 2] << 8) + p[jn + 3];
		jn += 4 + k;
		mn -= 4 + k;
	}

	return TRUE;
}

INT64 PsAnalyzer::GetPTS(BYTE* p, LONG n)
{
	// 0011xxx1 xxxxxxxx xxxxxxx1 xxxxxxxx xxxxxxx1
	if (!p || n < 5)
	{
		return 0;
	}

	INT64 t = 0;

	// 0011xxx1
	BYTE b = p[0];
	b <<= 4;
	for (int i = 0; i < 3; ++i)
	{
		t <<= 1;
		t |= (0x80 & b);
		b <<= 1;
	}

	t <<= 8;
	t |= p[1];

	t <<= 7;
	t |= (p[2] >> 1);

	t <<= 8;
	t |= p[3];

	t <<= 7;
	t |= (p[4] >> 1);

	return t;
}

LONG PsAnalyzer::GetFrameType(BYTE* pData, LONG nSize)
{
	if (!pData || nSize < 5)
	{
		return -1;
	}

	BYTE* p = (BYTE*)pData;
	UINT32 v = *((UINT32*)p);
	if (v == 0x01000000 || (v & 0xFFFFFF) == 0x010000)
	{
		BYTE m = ((v == 0x01000000) ? p[4] : p[3]) & 0x1F;
		if (m == 9)
		{
			return -1;
		}

		if (m == 7 || m == 5)
		{
			return 1;
		}
	}

	return 0;
}
