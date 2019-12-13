#pragma once

#include <cstdint>
#pragma pack(push, 1)

#if defined(_WIN32) || defined(_WIN64)
#define SMS_SDK_CALL	__stdcall
#else
#define	SMS_SDK_CALL
#endif


//===================================================================
//= �����붨��
//===================================================================
#define SMS_ERROR_NONE									0
#define	SMS_ERROR_REDIRECT								6000
#define	SMS_ERROR_INVALID_PARAMS						-1
#define SMS_ERROR_MEMORY_ALLOC							-2
#define	SMS_ERROR_INVALID_LIVE_ID			 			-3
#define	SMS_ERROR_INVALID_SERVER_ADDR					-4
#define	SMS_ERROR_INVALID_DEVICE_ID					-1000
#define	SMS_ERROR_INVALID_ARGUMENTS					-1001
#define	SMS_ERROR_INVALID_PLAY_ID						-1002
#define	SMS_ERROR_INVALID_PTZ_ID						-1003
#define	SMS_ERROR_NO_ENOUGH_BUFFER						-1004
#define	SMS_ERROR_NO_PROFILE							-1005
#define	SMS_ERROR_NETWORK								-1006
#define	SMS_ERROR_PACKET_INVALID						-1007
#define	SMS_ERROR_TIMEOUT								-1008
#define	SMS_ERROR_NOT_SUPPORTED						-1100	/* ��ǰ�Ự��֧�ָò���	*/
#define	SMS_ERROR_GET_POSITION_FAILED					-1101
#define	SMS_ERROR_CONNECT_LIVE_NODE_FAILED				-2000
#define	SMS_ERROR_OBJECT_NOT_FOUND						-2100
#define	SMS_ERROR_SAVE_IMAGE_FAILED					-2101

#define	SMS_ERROR_RECORD_NOT_FOUND						-3000
#define	SMS_ERROR_RECORD_END							-3001

#define	SMS_ERROR_NO_PLAY_NODE							-5000

#define	SMS_ERROR_AUTH_FAILED							-4000	/* �ͻ����ṩ����Ȩ��֤ʧ��	*/


#define	SMS_ERROR_DEVICE_AUTH_FAILED					-6000	/* �豸��¼��֤ʧ��		*/
#define	SMS_ERROR_DEVICE_MAX_CONNECT					-6001	/* �������������			*/
#define	SMS_ERROR_DEVICE_NETWORK						-6002	/* �豸�����ж�			*/
#define	SMS_ERROR_DEVICE_QUERY_RECORD_FAILED			-6003	/* ��ѯ¼��ʧ�ܣ������ҽӿڣ�*/
#define	SMS_ERROR_DEVICE_STREAM_ALREADY_OPEN			-6100	/* �豸�����Ѿ�����		*/
#define	SMS_ERROR_DEVICE_STREAM_DISCONNECTED			-6101	/* �豸�����ж�			*/
#define	SMS_ERROR_DEVICE_STREAM_REAVE					-6102	/* �豸���������߼��û���ռ	*/
#define	SMS_ERROR_DEVICE_STREAM_PLAY_FAILED			-6103	/* �豸��������ʧ�ܣ�����ʧ�ܣ�*/
#define	SMS_ERROR_DEVICE_STREAM_INVALID_PLAYTIME		-6104	/* �豸�����Ļط�ʱ�����Ч	*/
#define	SMS_ERROR_DEVICE_STREAM_NOT_OPEN				-6105	/* �豸������δ����		*/
#define	SMS_ERROR_DEVICE_STREAM_INVALID_POSITION		-6106	/* ��Ч���Ϸ�λ�ã�ʱ����Ч��*/
#define	SMS_ERROR_DEVICE_STREAM_SET_POSITION_FAILED	-6107	/* �Ϸ�ʧ�ܣ�����ʧ�ܣ�*/
#define	SMS_ERROR_DEVICE_STREAM_INVALID_SPEED			-6108	/* ��Ч���ٶ�ֵ*/
#define	SMS_ERROR_DEVICE_STREAM_SET_SPEED_FAILED		-6109	/* ���ò����ٶȣ�����ʧ�ܣ�*/
#define	SMS_ERROR_DEVICE_STREAM_PAUSE_FAILED			-6110	/* ��ͣʧ��*/
#define	SMS_ERROR_DEVICE_STREAM_RESUME_FAILED			-6111	/* ��ͣʧ��*/
#define	SMS_ERROR_DEVICE_PTZ_INVALID_TOKEN				-6200	/* ��Ч��PTZ Token		*/	
#define	SMS_ERROR_DEVICE_PTZ_MOVE_FAILED				-6201	/* ��̨ת��ʧ�ܣ�����ʧ�ܣ�	*/
#define	SMS_ERROR_DEVICE_PTZ_SPEED_INVALID				-6202	/* ��̨���Ƶ��ٶ�ֵ��Ч		*/	
#define	SMS_ERROR_DEVICE_PTZ_SET_PRESET_FAILED			-6203	/* ����Ԥ��λʧ�ܣ�����ʧ�ܣ�*/
#define	SMS_ERROR_DEVICE_UNSUPPORTED					-6204	/* ���ܲ�֧�� */
#define	SMS_ERROR_DEVICE_PTZ_GET_PRESET_LIST_FAILED	-6205	/* ��ȡԤ��λʧ�� */

// GB28181
#define	SMS_ERROR_GB28181_NO_MEMORY					-10001
#define	SMS_ERROR_GB28181_INSTANCE_NOT_OPEN			-10002
#define	SMS_ERROR_GB28181_INVALID_ARGUMENTS			-10003
#define	SMS_ERROR_GB28181_INVALID_PLAT_ARGS			-10004
#define	SMS_ERROR_GB28181_INVALID_PEER_ARGS			-10005
#define	SMS_ERROR_GB28181_INVALID_PROFILE_TOKEN		-10006
#define	SMS_ERROR_GB28181_LISTEN_ADDR_FAILED			-10007
#define	SMS_ERROR_GB28181_UNSUPPORTED					-10008

#define	SMS_ERROR_GB28181_REGISTER_BUILD_FAILED		-10021
#define	SMS_ERROR_GB28181_REGISTER_SEND_FAILED			-10022
#define	SMS_ERROR_GB28181_REGISTER_FAILED				-10023
#define	SMS_ERROR_GB28181_REGISTER_TIMEOUT				-10024
#define	SMS_ERROR_GB28181_UNREGISTER					-10025

#define	SMS_ERROR_GB28181_INVITE_BUILD_FAILED			-10031
#define	SMS_ERROR_GB28181_INVITE_SET_SUPPORTED_FAILED	-10032
#define	SMS_ERROR_GB28181_INVITE_SET_BODY_FAILED		-10033
#define	SMS_ERROR_GB28181_INVITE_SEND_FAILED			-10034
#define	SMS_ERROR_GB28181_INVITE_FAILED				-10035


#define	SMS_ERROR_GB28181_PTZ_CTRL_UNKNOWN_COMMAND		-10041
#define	SMS_ERROR_GB28181_PTZ_CMD_BUILD_FAILED			-10042
#define	SMS_ERROR_GB28181_PTZ_CMD_SET_BODY_FAILED		-10043
#define	SMS_ERROR_GB28181_PTZ_CMD_SEND_FAILED			-10044
#define	SMS_ERROR_GB28181_PTZ_CMD_FAILED				-10045

#define	SMS_ERROR_GB28181_STREAM_ALREADY_OPEN			-10051
#define	SMS_ERROR_GB28181_STREAM_INVITE_TIMEOUT		-10052
#define	SMS_ERROR_GB28181_STREAM_PLAY_FAILED			-10053

#define	SMS_ERROR_GB28181_ACK_BUILD_FAILED				-10061
#define	SMS_ERROR_GB28181_ACK_SEND_FAILED				-10064
#define	SMS_ERROR_GB28181_ACK_FAILED					-10065

#define	SMS_ERROR_GB28181_PB_CTRL_BUILD_FAILED			-10071
#define	SMS_ERROR_GB28181_PB_CTRL_SET_BODY_FAILED		-10072
#define	SMS_ERROR_GB28181_PB_CTRL_SET_CTYPE_FAILED		-10073
#define	SMS_ERROR_GB28181_PB_CTRL_SEND_FAILED			-10074

#define	SMS_ERROR_GB28181_QUERY_REC_BUILD_FAILED		-10081
#define	SMS_ERROR_GB28181_QUERY_REC_SET_CALL_FAILED	-10082
#define	SMS_ERROR_GB28181_QUERY_REC_SET_BODY_FAILED	-10083
#define	SMS_ERROR_GB28181_QUERY_REC_SET_CTYPE_FAILED	-10084
#define	SMS_ERROR_GB28181_QUERY_REC_SEND_FAILED		-10088
#define	SMS_ERROR_GB28181_QUERY_REC_ING_FAILED			-10089



// hik
#define	SMS_ERROR_HIK_NO_INIT							-20001
#define	SMS_ERROR_HIK_NO_LOGIN							-20002
#define	SMS_ERROR_HIK_REPLAYBYTIME_FAILED				-20003
#define	SMS_ERROR_HIK_GET_MONTHLY_RECORD_FAILED		-20006
#define	SMS_ERROR_HIK_GET_MONTHLY_RECORD_EXCEPTION		-20008
#define	SMS_ERROR_HIK_GET_MONTHLY_NO_RECORD			-20010
#define	SMS_ERROR_HIK_PLAYLIVE_FAILED					-20011
#define	SMS_ERROR_HIK_PTZCTRL_FAILED					-20012
#define	SMS_ERROR_HIK_ONLIYSTREAM_FAILED				-20013


#define AVFORMAT_OPEN_INPUT_FAILED						-30002			//���ļ�ʧ��
#define AVFORMAT_FIND_STREAM_INFO_FALIED				-30003			//��������Ϣʧ��
#define CAN_NOT_FIND_VIDEO_STREAM						-30004			//�޷��ҵ���Ƶ��
#define AV_BSF_ALLOC_FAILED								-30005			//���������ʧ��
#define AV_BSF_INIT_FAILED								-30006			//��ʼ��������ʧ��
#define AV_BSF_GET_BY_NAME_FAILED						-30007			//��֧�ֵı���

#define AV_END_OF_FILE_CODE								-30108			//��ȡ�ļ�����





enum SMS_MEDIA_TYPE_t
{
	SMS_MEDIA_TYPE_MIXED = 0,	// 
	SMS_MEDIA_TYPE_VIDEO = 1,	// video
	SMS_MEDIA_TYPE_AUDIO = 2,	// audio
	SMS_MEDIA_TYPE_DATA = 3,	// Opaque data information usually continuous
	SMS_MEDIA_TYPE_SUBTITLE = 4,	// subtitle
	SMS_MEDIA_TYPE_ATTACHMENT = 5,	// Opaque data information usually sparse
	SMS_MEDIA_TYPE_GIS = 6,	// gis
	SMS_MEDIA_TYPE_UNKNOWN = 1000	// unknown
};

enum SMS_CODEC_TYPE_t
{
	SMS_CODEC_TYPE_NONE = 0,	// ����ȷ
	SMS_CODEC_TYPE_H264 = 1,	// h264
	SMS_CODEC_TYPE_H265 = 2,	// h265
	SMS_CODEC_TYPE_AAC = 3,	// avc
	SMS_CODEC_TYPE_PCMA = 4,	// pcm alaw
	SMS_CODEC_TYPE_PCMU = 5,	// pcm ulaw
	SMS_CODEC_TYPE_UNK = 1000	// unknown
};

enum SMS_MUXER_TYPE_t
{
	SMS_MUXER_NONE = 0,	// �Ǹ��ã���������
	SMS_MUXER_MPEG_PS = 1,	// ps
	SMS_MUXER_MPEG_TS = 2,	// ts
	SMS_MUXER_MPEG_UNK = 1000	// unknown
};

enum SMS_FRAME_TYPE_t
{
	SMS_FRAME_TYPE_NONE = 0,	// ��ȷ��
	SMS_FRAME_TYPE_KEY_FRAME = 1,	// �ؼ�֡
	SMS_FRAME_TYPE_NON_KEY_FRAME = 2		// �ǹؼ�֡
};

//enum SMS_LOG_LEVEL_t
//{
//	SMS_LOG_QUIET = 0,	// ��������־
//	SMS_LOG_TRACE = 1,	// ����trace�����߼������־
//	SMS_LOG_DEBUG = 2,	// ����debug�����߼������־
//	SMS_LOG_INFO = 3,	// ����info �����߼������־
//	SMS_LOG_WARN = 4,	// ����warn �����߼������־
//	SMS_LOG_ERROR = 5,	// ����error�����߼������־
//	SMS_LOG_CRITICAL = 6		// 
//};


struct SMS_FRAME_INFO_t
{
	std::int32_t		stream_id;				// �����

	SMS_MEDIA_TYPE_t	media_type;				// ý������
	SMS_CODEC_TYPE_t	codec;					// �����ʽ

	SMS_MUXER_TYPE_t	muxer;					// ��װ��ʽ
	SMS_CODEC_TYPE_t	muxer_audio_codec;		// ���������е���Ƶ��������
	SMS_CODEC_TYPE_t	muxer_video_codec;		// ���������е���Ƶ��������

	SMS_FRAME_TYPE_t	frame_type;				// ֡����

	std::int32_t		video_width;			// ��Ƶˮƽ�ֱ���
	std::int32_t		video_height;			// ��Ƶ��ֱ�ֱ���
	std::int32_t		video_frame_rate;		// ��Ƶ֡�ʣ���һ�������ã�

	std::int16_t		audio_channels;			// ��Ƶͨ������
	std::int32_t		audio_sample_rate;		// ��Ƶ������
	std::int16_t		audio_bits_per_sample;	// ��Ƶ����λ��

	std::int32_t		bitrate;				// ���ʣ���һ�������ã�����λbps
	std::int64_t		display_time;			// Ԥ������ʱ��ʹ�ã�������0���

	std::int64_t		frame_timestamp;		// ʱ���(΢��)
	std::int64_t		frame_number;			// ֡��ţ����stream_id���ԣ�
};


#define SMS_MAX_PRESET_NAME_LEN	128
#define	SMS_MAX_PRESET_TOKEN_LEN	128
struct SMS_PRESET_INFO_t
{
	char    token[SMS_MAX_PRESET_TOKEN_LEN];
	char	name[SMS_MAX_PRESET_NAME_LEN];
	double  p_pos;	// pan
	double  t_pos;	// tilt
	double  z_pos;	// zoom
};


struct SMS_AUDIO_STATE_t
{
	std::int32_t		stream_id;			// = -1;
	SMS_CODEC_TYPE_t	codec;				// = SMS_CODEC_TYPE_t::SMS_CODEC_TYPE_NONE;
	std::int32_t		channels;			// = 0;							// ��Ƶͨ������
	std::int32_t		sample_rate;		// = 0;							// ��Ƶ������
	std::int32_t		bits_per_sample;	// = 0;							// ��Ƶ����λ��

	std::int64_t		frame_cnt;			// = 0;
	std::int64_t		total_bytes;		// = 0;
	std::int64_t		update_time;		// = 0;
	std::int64_t		bit_rate;			// = 0;
	std::int64_t		frame_loss;			// = 0;
	std::int64_t		latest_frame_num;	// = 0;
};

struct SMS_VIDEO_STATE_t
{
	std::int32_t		stream_id;			// = -1;
	SMS_CODEC_TYPE_t	codec;				// = SMS_CODEC_TYPE_t::SMS_CODEC_TYPE_NONE;
	std::int32_t		width;				// = 0;							// ��Ƶˮƽ�ֱ���
	std::int32_t		height;				// = 0;							// ��Ƶ��ֱ�ֱ���
	std::int32_t		frame_rate;			// = 0;							// ��Ƶ֡�ʣ���һ�������ã�

	std::int64_t		frame_cnt;			// = 0;
	std::int64_t		total_bytes;		// = 0;
	std::int64_t		update_time;		// = 0;
	std::int64_t		bit_rate;			// = 0;
	std::int64_t		frame_loss;			// = 0;
	std::int64_t		latest_frame_num;	// = 0;
};

struct SMS_MIXED_STATE_t
{
	std::int32_t		stream_id;			// = -1;							// �����
	SMS_CODEC_TYPE_t	audio_codec;		// = SMS_CODEC_TYPE_t::SMS_CODEC_TYPE_NONE;		// �����ʽ
	SMS_CODEC_TYPE_t	video_codec;		// = SMS_CODEC_TYPE_t::SMS_CODEC_TYPE_NONE;		// �����ʽ
	SMS_MUXER_TYPE_t	muxer;				// = SMS_MUXER_TYPE_t::SMS_MUXER_NONE;		// ��װ��ʽ

	std::int64_t		frame_cnt;			// = 0;
	std::int64_t		total_bytes;		// = 0;
	std::int64_t		update_time;		// = 0;
	std::int64_t		bit_rate;			// = 0;
	std::int64_t		frame_loss;			// = 0;
	std::int64_t		latest_frame_num;	// = 0;
};

struct SMS_STREAM_STATE_t
{
	std::int64_t		start_time;			// = 0;
	SMS_MIXED_STATE_t	mixed;				// = 0;
	SMS_AUDIO_STATE_t	audio;				// = 0;
	SMS_VIDEO_STATE_t	video;				// = 0;
	std::int64_t		frame_loss;			// = 0;
};

struct SMS_24HOURS_RECORD_STATE_t
{
	std::uint8_t		second[3600 * 24];
};

struct SMS_MONTHLY_RECORD_STATE_t
{
	std::uint8_t		day[32];
};

struct SMS_DATE_TIME_t
{
	std::uint16_t		year;
	std::uint16_t		month;
	std::uint16_t		day;
	std::uint16_t		hour;
	std::uint16_t		minute;
	std::uint16_t		second;
	std::uint16_t		millsecond;
};

typedef int (SMS_SDK_CALL* SMS_ERROR_HANDLER_t)(int error_code, const void* user);
typedef int (SMS_SDK_CALL* SMS_FRAME_HANDLER_t)(const SMS_FRAME_INFO_t* frame, const std::uint8_t* data, std::int32_t size, const void* user);
typedef int (SMS_SDK_CALL* SMS_MESSAGE_HANDLER_t)(std::uint64_t msg_type, const std::uint8_t* msg_data, std::int32_t msg_size, const void* msg_user);
typedef int (SMS_SDK_CALL* SMS_OBJECT_HANDLER_t)(std::uint64_t object_id, double x, double y, const void* msg_user);

#pragma pack(pop)