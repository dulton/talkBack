#ifndef TALKBACKRTSPDEF_H
#define TALKBACKRTSPDEF_H

#ifdef __cplusplus
extern "C"{
#endif

#define RTSP_SOCK_TIMEOUT       (8000)
#define RTSP_BUF_SIZE			(1024*8)

#define RTSP_VERSION            "RTSP/1.0"
#define RTSP_USER_AGENT         "talkbackRtsp 2.1 (by sunday)"

#define RTSP_INTERLEAVED_MAGIC	'$'//0X24
#define RTSP_VERSION            "RTSP/1.0"
#define SDP_MEDIA_TYPE			"application/sdp"

#define RTSP_RET_OK				(0)
#define RTSP_RET_FAIL			(-1)
// stream type
#define RTSP_STREAM_VIDEO	(0x01)
#define RTSP_STREAM_AUDIO	(0x02)

#define RTSP_CLIENT				(0)
#define RTSP_SERVER				(1)

#define RTSP_MODE_PLAY		(0)
#define RTSP_MODE_RECORD	(1)

#if 0
#define TALKBACK_RTCP_ENABLE          (0)
#endif
typedef struct _RStatusCode{
    int code;
    const char *info;
}RStatusCode_t;
typedef enum
{
    RTP_AUTO,
    RTP_UDP,
    RTP_TCP,
}enRTP_TRANSPORT;
#ifndef uint8_t
typedef unsigned char uint8_t;
#endif
#ifndef uint16_t
typedef unsigned short uint16_t;
#endif
#ifndef uint32_t
typedef unsigned int 	uint32_t;
#endif
#ifndef uint64_t
#ifdef _WIN32
typedef unsigned __int64 uint64_t;
#else
typedef unsigned long long uint64_t;
#endif
#endif



#ifdef __cplusplus
}
#endif




#endif // TALKBACKRTSPDEF_H

