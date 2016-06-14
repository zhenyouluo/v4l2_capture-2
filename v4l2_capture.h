
#ifndef V4L2_CAPTURE_H
#define V4L2_CAPTURE_H

#include "tinylib/linux/net/loop.h"

#include <stdint.h>

typedef enum pixelformat{
	PIXEL_FORMAT_YUYV,
	PIXEL_FORMAT_YUV422P,	/* YUV422 Planar */
	/* more pixel format */
}pixelformat_e;

typedef struct imageformat{
	pixelformat_e pixel_format;
	uint32_t width;
	uint32_t height;
	uint32_t bytesperline;
	uint32_t image_size;
}imageformat_t;

typedef struct captured_image{
	imageformat_t format;
	uint8_t *data;
	uint32_t len;
}captured_image_t;

#ifdef __cplusplus
extern "C" {
#endif

struct v4l2_capture;
typedef struct v4l2_capture v4l2_capture_t;

v4l2_capture_t* v4l2_capture_open(const char *device);
void v4l2_capture_close(v4l2_capture_t *capture);

const imageformat_t* v4l2_capture_get_imageformat(v4l2_capture_t *capture);
const captured_image_t* v4l2_capture(v4l2_capture_t *capture);

int v4l2_capture_start(v4l2_capture_t *capture, loop_t* loop, void(*image_sink)(const captured_image_t* image, void* userdata), void* userdata);
void v4l2_capture_stop(v4l2_capture_t *capture);

#ifdef __cplusplus
}
#endif

#endif /* !V4L2_CAPTURE_H */
