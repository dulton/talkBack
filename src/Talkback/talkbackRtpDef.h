#ifndef TALKBACKRTPDEF_H
#define TALKBACKRTPDEF_H

#ifdef __cplusplus
extern "C" {
#endif
#define RTP_MAX_FRAGMENTATION	(800) /*we must configure this manually*/
#define RTP_MTU_SIZE 			(1258)
#define RTP_PACKET_SIZE			(RTP_MTU_SIZE + 18 + 4)//max header size: 4(rtsp_interleaved_header)+
            //12(rtp_header)+1(FU_indicator)+1(FU_header) + paddingsize(1~3)(4bytes align)
typedef enum{
    RTP_TYPE_PCMU = 0,
    RTP_TYPE_RESERVED1,
    RTP_TYPE_RESERVED2,
    RTP_TYPE_GSM,
    RTP_TYPE_G723,
    RTP_TYPE_DVI4_8000,
    RTP_TYPE_DVI4_16000,
    RTP_TYPE_LPC,
    RTP_TYPE_PCMA,
    RTP_TYPE_G722,
    RTP_TYPE_L161,//44.1khz ,2 channels  //10
    RTP_TYPE_L162,//44.1khz, 1 channel
    RTP_TYPE_QCELP,
    RTP_TYPE_CN,
    RTP_TYPE_MPA,
    RTP_TYPE_G728,
    RTP_TYPE_DVI4_11025,
    RTP_TYPE_DVI4_22050,
    RTP_TYPE_G729, //18
    //
    RTP_TYPE_CEIB =25,
    RTP_TYPE_JPEG =26,
    RTP_TYPE_H261 =31,
    RTP_TYPE_MPV =32,
    RTP_TYPE_MP2T =33,
    RTP_TYPE_H263=34,
    //
    //
    RTP_TYPE_DYNAMIC = 96,//~127
}RtpType_t;

#define RTP_TYPE_PS		(128)
#define RTP_TYPE_TS		(129)
#define RTP_TYPE_MPEG	(130)
#define RTP_TYPE_H264  	(131)
#define RTP_TYPE_H265	(132)
#define RTP_TYPE_AAC	(150)


#define RTP_VERSION				(2)
#define RTP_TRANSPORT_UDP	(0)
#define RTP_TRANSPORT_TCP	(1)

#define RTSP_RTP_OVER_UDP	(false)
#define RTSP_RTP_OVER_RTSP	(true)// interleaved mode
#define RTSP_RTP_DEF_TRANSPORT (RTSP_RTP_OVER_UDP)


#define RTP_UNICAST		(0)
#define	RTP_MULTICAST		(1)
#define RTP_MAX_FRAGMENTATION	(800) /*we must configure this manually*/

#define RTP_CLIENT 0
#define RTP_SERVER 1
typedef struct _rtp_header
{
// 0                   1                   2                   3
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |V=2|P|X| CC|M|     PT      |       sequence number         |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |                           timestamp                           |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |           synchronization source (SSRC) identifier            |
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// |            contributing source (CSRC) identifiers             |
// |                             ....                              |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    unsigned char csrc_cnt:4;
    unsigned char extension:1;
    unsigned char padding:1;
    unsigned char version : 2;
    unsigned char payload_type:7;
    unsigned char marker:1;
    unsigned short sequence_number;
    unsigned int timestamp;
    unsigned int ssrc;
    // ignore the csrc id
}RtpHeader_t;

typedef struct _rtppacket
{
    int cnt;
    void *buffer;
    unsigned int malloc_size;
    unsigned int buf_size[RTP_MAX_FRAGMENTATION];
    char trunk_buf[10000];
    unsigned int trunk_readed;
    //
    int iFrameCnt; //  frame count
}RtpPacket_t;

typedef struct _rtsp_interleaved_header
{
    unsigned char magic;	//'$'
    unsigned char channel;
    unsigned short length;
}RtspInterHeader_t;

typedef struct __rtp
{
    int role;
    int buffertime;
    // transport
    int interleaved;
    int sock;
    int peer_chn_port;
    int protocal;
    char peername[20];
    //
    unsigned int ssrc;
    //int payload_type;
    int payloadType;
    int mediaType; // detailed media type; sometime is equal to payloadtype; but if payloadtype is dynamic , it is no longer
    unsigned int base_seq;
    unsigned int seq;// max seq
    unsigned int timestamp;
    unsigned int packet_cnt;// sended number of packets
    unsigned int octet_cnt;// sended number of bytes
    int cycle_cnt;// when seq exceed 65536 ,this increase
    unsigned int comulative_lost;
    int fraction_lost;
    //
    int raw_data;
    RtpHeader_t header;
    RtspInterHeader_t interHeader;
    //
    RtpPacket_t packet;
}Rtp_t;

#ifdef __cplusplus
}
#endif

#endif // TALKBACKRTPDEF_H
