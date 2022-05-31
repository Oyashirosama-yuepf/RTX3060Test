#ifndef __APP_STREAM_H_
#define __APP_STREAM_H_

#include <TI/tivx.h>

#include <sys/stat.h>
#include <semaphore.h>

//#define NUM_CAPT_CHANNELS    (4)
//#define NUM_ENCODE_CHANNEL   (4)

typedef struct
{
    uint8_t* mem;
    uint8_t  valid;
    uint32_t datalen;
}EncodeStreamInfo;

typedef struct{
	uint8_t *Luma_ptr;
	uint32_t Luma_size;
	uint8_t *Cbcr_ptr;
	uint32_t Cbcr_size;
}Nv12OutBuf;

vx_status app_stream_init();
vx_status app_stream_run();
vx_status app_stream_stop();
void app_stream_deinit();

vx_status app_get_streambuf(EncodeStreamInfo *info, uint8_t channel);
vx_status app_get_nv12buf(Nv12OutBuf *buf, uint8_t channel);

#endif
