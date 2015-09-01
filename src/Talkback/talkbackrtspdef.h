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

typedef struct _rtsp_interleaved_header
{
    unsigned char magic;	//'$'
    unsigned char channel;
    unsigned short length;
}RtspInterHeader_t;

#ifdef __cplusplus
}
#endif




#endif // TALKBACKRTSPDEF_H

