#ifndef TALKBACKRTCPDEF_H
#define TALKBACKRTCPDEF_H
#ifdef __cplusplus
extern "C" {
#endif

#include "talkbackrtspdef.h"
#include "talkbackRtpDef.h"


#define RTCP_MAX_PACKETS 		(3)
typedef struct __rtcp_packets
{
    int cnt;
    //char buffer[RTCP_MAX_PACKETS][RTCP_ONE_PACKET_SIZE];
    void *buffer;
    unsigned int malloc_size;
    int buf_size[RTCP_MAX_PACKETS];
    char trunk_buf[4000];
    int trunk_readed;
}RtcpPacketEx_t;


typedef struct __rtcp
{
    int role;
    int bAlive;
    // transport
    int interleaved;
    int sock;
    int chn_port_c;
    int chn_port_s;
    char peername[20];
    //
    uint32_t ssrc;
    uint32_t src_id[1];
    //
    Rtp_t *rtp;
    uint32_t last_sr_ts;  		// to mark the sender report's timestamp
                                // use to compute the round-trip time
    //MillisecondTimer_t rtt_timer; // to mark the time of received SR(receiver)
                                // or to mark the time to sending SR(sender)
                                // use for compute the round-trip time
    //MilliSecond_t last_recv_sr_ts;	// to mark the time  received SR(receiver)
                                    // use for compute jitter
    //MillisecondTimer_t jitter_timer; // use for compute  jitter
                                // to mark the time between two SR(sender)
                                // to mark the time between receiving two SR(reiceiver)
    uint32_t jitter;
    //MillisecondTimer_t trans_timer; // use to control the rtcp packet transmission interval
    //
    RtcpPacketEx_t packet;
}Rtcp_t;

#ifdef __cplusplus
}
#endif

#endif // TALKBACKRTCPDEF_H
