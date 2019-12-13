#pragma once

#include <cstdint>
#pragma pack(push, 1)

#if defined(_WIN32) || defined(_WIN64)
#define SMS_SDK_CALL	__stdcall
#else
#define	SMS_SDK_CALL
#endif


//===================================================================
//= 错误码定义
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
#define	SMS_ERROR_NOT_SUPPORTED						-1100	/* 当前会话不支持该操作	*/
#define	SMS_ERROR_GET_POSITION_FAILED					-1101
#define	SMS_ERROR_CONNECT_LIVE_NODE_FAILED				-2000
#define	SMS_ERROR_OBJECT_NOT_FOUND						-2100
#define	SMS_ERROR_SAVE_IMAGE_FAILED					-2101

#define	SMS_ERROR_RECORD_NOT_FOUND						-3000
#define	SMS_ERROR_RECORD_END							-3001

#define	SMS_ERROR_NO_PLAY_NODE							-5000

#define	SMS_ERROR_AUTH_FAILED							-4000	/* 客户端提供的授权认证失败	*/


#define	SMS_ERROR_DEVICE_AUTH_FAILED					-6000	/* 设备登录认证失败		*/
#define	SMS_ERROR_DEVICE_MAX_CONNECT					-6001	/* 超过最大连接数			*/
#define	SMS_ERROR_DEVICE_NETWORK						-6002	/* 设备网络中断			*/
#define	SMS_ERROR_DEVICE_QUERY_RECORD_FAILED			-6003	/* 查询录像失败（调厂家接口）*/
#define	SMS_ERROR_DEVICE_STREAM_ALREADY_OPEN			-6100	/* 设备码流已经创建		*/
#define	SMS_ERROR_DEVICE_STREAM_DISCONNECTED			-6101	/* 设备码流中断			*/
#define	SMS_ERROR_DEVICE_STREAM_REAVE					-6102	/* 设备码流被更高级用户抢占	*/
#define	SMS_ERROR_DEVICE_STREAM_PLAY_FAILED			-6103	/* 设备码流播放失败（调用失败）*/
#define	SMS_ERROR_DEVICE_STREAM_INVALID_PLAYTIME		-6104	/* 设备码流的回放时间段无效	*/
#define	SMS_ERROR_DEVICE_STREAM_NOT_OPEN				-6105	/* 设备码流的未播放		*/
#define	SMS_ERROR_DEVICE_STREAM_INVALID_POSITION		-6106	/* 无效的拖放位置（时间无效）*/
#define	SMS_ERROR_DEVICE_STREAM_SET_POSITION_FAILED	-6107	/* 拖放失败（调用失败）*/
#define	SMS_ERROR_DEVICE_STREAM_INVALID_SPEED			-6108	/* 无效的速度值*/
#define	SMS_ERROR_DEVICE_STREAM_SET_SPEED_FAILED		-6109	/* 设置播放速度（调用失败）*/
#define	SMS_ERROR_DEVICE_STREAM_PAUSE_FAILED			-6110	/* 暂停失败*/
#define	SMS_ERROR_DEVICE_STREAM_RESUME_FAILED			-6111	/* 暂停失败*/
#define	SMS_ERROR_DEVICE_PTZ_INVALID_TOKEN				-6200	/* 无效的PTZ Token		*/	
#define	SMS_ERROR_DEVICE_PTZ_MOVE_FAILED				-6201	/* 云台转动失败（调用失败）	*/
#define	SMS_ERROR_DEVICE_PTZ_SPEED_INVALID				-6202	/* 云台控制的速度值无效		*/	
#define	SMS_ERROR_DEVICE_PTZ_SET_PRESET_FAILED			-6203	/* 设置预置位失败（调用失败）*/
#define	SMS_ERROR_DEVICE_UNSUPPORTED					-6204	/* 功能不支持 */
#define	SMS_ERROR_DEVICE_PTZ_GET_PRESET_LIST_FAILED	-6205	/* 获取预置位失败 */

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


#define AVFORMAT_OPEN_INPUT_FAILED						-30002			//打开文件失败
#define AVFORMAT_FIND_STREAM_INFO_FALIED				-30003			//查找流信息失败
#define CAN_NOT_FIND_VIDEO_STREAM						-30004			//无法找到视频流
#define AV_BSF_ALLOC_FAILED								-30005			//申请过滤器失败
#define AV_BSF_INIT_FAILED								-30006			//初始化过滤器失败
#define AV_BSF_GET_BY_NAME_FAILED						-30007			//不支持的编码

#define AV_END_OF_FILE_CODE								-30108			//读取文件结束





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
	SMS_CODEC_TYPE_NONE = 0,	// 不明确
	SMS_CODEC_TYPE_H264 = 1,	// h264
	SMS_CODEC_TYPE_H265 = 2,	// h265
	SMS_CODEC_TYPE_AAC = 3,	// avc
	SMS_CODEC_TYPE_PCMA = 4,	// pcm alaw
	SMS_CODEC_TYPE_PCMU = 5,	// pcm ulaw
	SMS_CODEC_TYPE_UNK = 1000	// unknown
};

enum SMS_MUXER_TYPE_t
{
	SMS_MUXER_NONE = 0,	// 非复用（纯净流）
	SMS_MUXER_MPEG_PS = 1,	// ps
	SMS_MUXER_MPEG_TS = 2,	// ts
	SMS_MUXER_MPEG_UNK = 1000	// unknown
};

enum SMS_FRAME_TYPE_t
{
	SMS_FRAME_TYPE_NONE = 0,	// 不确定
	SMS_FRAME_TYPE_KEY_FRAME = 1,	// 关键帧
	SMS_FRAME_TYPE_NON_KEY_FRAME = 2		// 非关键帧
};

//enum SMS_LOG_LEVEL_t
//{
//	SMS_LOG_QUIET = 0,	// 不生成日志
//	SMS_LOG_TRACE = 1,	// 生成trace及更高级别的日志
//	SMS_LOG_DEBUG = 2,	// 生成debug及更高级别的日志
//	SMS_LOG_INFO = 3,	// 生成info 及更高级别的日志
//	SMS_LOG_WARN = 4,	// 生成warn 及更高级别的日志
//	SMS_LOG_ERROR = 5,	// 生成error及更高级别的日志
//	SMS_LOG_CRITICAL = 6		// 
//};


struct SMS_FRAME_INFO_t
{
	std::int32_t		stream_id;				// 流编号

	SMS_MEDIA_TYPE_t	media_type;				// 媒体类型
	SMS_CODEC_TYPE_t	codec;					// 编码格式

	SMS_MUXER_TYPE_t	muxer;					// 封装格式
	SMS_CODEC_TYPE_t	muxer_audio_codec;		// 复合码流中的音频编码类型
	SMS_CODEC_TYPE_t	muxer_video_codec;		// 复合码流中的视频编码类型

	SMS_FRAME_TYPE_t	frame_type;				// 帧类型

	std::int32_t		video_width;			// 视频水平分辨率
	std::int32_t		video_height;			// 视频垂直分辨率
	std::int32_t		video_frame_rate;		// 视频帧率（不一定会设置）

	std::int16_t		audio_channels;			// 音频通道数量
	std::int32_t		audio_sample_rate;		// 音频采样率
	std::int16_t		audio_bits_per_sample;	// 音频采样位率

	std::int32_t		bitrate;				// 码率（不一定会设置），单位bps
	std::int64_t		display_time;			// 预留（暂时不使用），请用0填充

	std::int64_t		frame_timestamp;		// 时间戳(微秒)
	std::int64_t		frame_number;			// 帧编号（相对stream_id而言）
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
	std::int32_t		channels;			// = 0;							// 音频通道数量
	std::int32_t		sample_rate;		// = 0;							// 音频采样率
	std::int32_t		bits_per_sample;	// = 0;							// 音频采样位率

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
	std::int32_t		width;				// = 0;							// 视频水平分辨率
	std::int32_t		height;				// = 0;							// 视频垂直分辨率
	std::int32_t		frame_rate;			// = 0;							// 视频帧率（不一定会设置）

	std::int64_t		frame_cnt;			// = 0;
	std::int64_t		total_bytes;		// = 0;
	std::int64_t		update_time;		// = 0;
	std::int64_t		bit_rate;			// = 0;
	std::int64_t		frame_loss;			// = 0;
	std::int64_t		latest_frame_num;	// = 0;
};

struct SMS_MIXED_STATE_t
{
	std::int32_t		stream_id;			// = -1;							// 流编号
	SMS_CODEC_TYPE_t	audio_codec;		// = SMS_CODEC_TYPE_t::SMS_CODEC_TYPE_NONE;		// 编码格式
	SMS_CODEC_TYPE_t	video_codec;		// = SMS_CODEC_TYPE_t::SMS_CODEC_TYPE_NONE;		// 编码格式
	SMS_MUXER_TYPE_t	muxer;				// = SMS_MUXER_TYPE_t::SMS_MUXER_NONE;		// 封装格式

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