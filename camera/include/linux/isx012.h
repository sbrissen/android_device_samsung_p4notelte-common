/* drivers/media/video/isx012.h
 *
 * Driver for isx012 (3MP Camera) from SEC(LSI), firmware EVT1.1
 *
 * Copyright (C) 2010, SAMSUNG ELECTRONICS
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * - change date: 2012.06.28
 */

#ifndef __ISX012_H__
#define __ISX012_H__


#define ISX012_DRIVER_NAME	"ISX012"

#define ISX012_DELAY		0xFFFF0000

/* result values returned to HAL */
enum af_result_status {
	AF_RESULT_NONE = 0x00,
	AF_RESULT_FAILED = 0x01,
	AF_RESULT_SUCCESS = 0x02,
	AF_RESULT_CANCELLED = 0x04,
	AF_RESULT_DOING = 0x08
};

enum af_operation_status {
	AF_NONE = 0,
	AF_START,
	AF_CANCEL,
};

enum preflash_status {
	PREFLASH_NONE = 0,
	PREFLASH_OFF,
	PREFLASH_ON,
};

enum isx012_oprmode {
	ISX012_OPRMODE_VIDEO = 0,
	ISX012_OPRMODE_IMAGE = 1,
};

enum stream_cmd {
	STREAM_STOP,
	STREAM_START,
};

enum wide_req_cmd {
	WIDE_REQ_NONE,
	WIDE_REQ_CHANGE,
	WIDE_REQ_RESTORE,
};

/* Preview Size List: refer to the belows. */
enum isx012_preview_frame_size {
	PREVIEW_SZ_QCIF = 0,	/* 176x144 */
	PREVIEW_SZ_320x240,	/* 320x240 */
	PREVIEW_SZ_CIF,		/* 352x288 */
	PREVIEW_SZ_528x432,	/* 528x432 */
	PREVIEW_SZ_VGA,		/* 640x480 */
	PREVIEW_SZ_D1,		/* 720x480 */
	PREVIEW_SZ_880x720,	/* 880x720 */
	PREVIEW_SZ_SVGA,	/* 800x600 */
	PREVIEW_SZ_1024x576,	/* 1024x576, 16:9 */
	PREVIEW_SZ_1024x616,	/* 1024x616, ? */
	PREVIEW_SZ_XGA,		/* 1024x768 */
	PREVIEW_SZ_PVGA,	/* 1280x720 */
	PREVIEW_SZ_SXGA,	/* 1280x1024 */
	PREVIEW_SZ_MAX,
};

/* Capture Size List: Capture size is defined as below.
 *
 *	CAPTURE_SZ_VGA:		640x480
 *	CAPTURE_SZ_WVGA:	800x480
 *	CAPTURE_SZ_SVGA:	800x600
 *	CAPTURE_SZ_WSVGA:	1024x600
 *	CAPTURE_SZ_1MP:		1280x960
 *	CAPTURE_SZ_W1MP:	1600x960
 *	CAPTURE_SZ_2MP:		UXGA - 1600x1200
 *	CAPTURE_SZ_W2MP:	35mm Academy Offset Standard 1.66
 *				2048x1232, 2.4MP
 *	CAPTURE_SZ_3MP:		QXGA  - 2048x1536
 *	CAPTURE_SZ_W4MP:	WQXGA - 2560x1536
 *	CAPTURE_SZ_5MP:		2560x1920
 */

enum isx012_capture_frame_size {
	CAPTURE_SZ_VGA = 0,	/* 640x480 */
	CAPTURE_SZ_960_720,
	CAPTURE_SZ_W1MP,	/* 1536x864. Samsung-defined */
	CAPTURE_SZ_2MP,		/* UXGA - 1600x1200 */
	CAPTURE_SZ_W2MP,	/* 2048x1152. Samsung-defined */
	CAPTURE_SZ_3MP,		/* QXGA  - 2048x1536 */
	CAPTURE_SZ_W4MP,	/* 2560x1440. Samsung-defined */
	CAPTURE_SZ_5MP,		/* 2560x1920 */
	CAPTURE_SZ_MAX,
};

#ifdef CONFIG_VIDEO_ISX012_P2
#define PREVIEW_WIDE_SIZE	PREVIEW_SZ_1024x552
#else
#define PREVIEW_WIDE_SIZE	PREVIEW_SZ_1024x576
#endif
#define CAPTURE_WIDE_SIZE	CAPTURE_SZ_W2MP

enum frame_ratio {
	FRMRATIO_QCIF   = 12,   /* 11 : 9 */
	FRMRATIO_VGA    = 13,   /* 4 : 3 */
	FRMRATIO_D1     = 15,   /* 3 : 2 */
	FRMRATIO_WVGA   = 16,   /* 5 : 3 */
	FRMRATIO_HD     = 17,   /* 16 : 9 */
};

enum isx012_fps_index {
	I_FPS_0,
	I_FPS_7,
	I_FPS_10,
	I_FPS_12,
	I_FPS_15,
	I_FPS_25,
	I_FPS_30,
	I_FPS_MAX,
};

enum ae_awb_lock {
	AEAWB_UNLOCK = 0,
	AEAWB_LOCK,
	AEAWB_LOCK_MAX,
};

enum runmode {
	RUNMODE_NOTREADY,
	RUNMODE_INIT,
	/*RUNMODE_IDLE,*/
	RUNMODE_RUNNING,	/* previewing */
	RUNMODE_RUNNING_STOP,
	RUNMODE_CAPTURING,
	RUNMODE_CAPTURING_STOP,
	RUNMODE_RECORDING,	/* camcorder mode */
	RUNMODE_RECORDING_STOP,
};

enum isx012_stby_type {
	ISX012_STBY_HW,
	ISX012_STBY_SW,
};

/* EXIF - flash filed */
#define EXIF_FLASH_FIRED		(0x01)
#define EXIF_FLASH_MODE_FIRING		(0x01 << 3)
#define EXIF_FLASH_MODE_SUPPRESSION	(0x02 << 3)
#define EXIF_FLASH_MODE_AUTO		(0x03 << 3)

#if !defined(CONFIG_CAM_YUV_CAPTURE)
/* JPEG MEMORY SIZE */
#define SENSOR_JPEG_OUTPUT_MAXSIZE	0x29999A /*2726298bytes, 2.6M */
#define EXTRA_MEMSIZE			(0 * SZ_1K)
#define SENSOR_JPEG_SNAPSHOT_MEMSIZE \
	(((SENSOR_JPEG_OUTPUT_MAXSIZE + EXTRA_MEMSIZE  + SZ_16K-1) / SZ_16K) * SZ_16K)
#endif

/*********** Sensor specific ************/
#define ISX012_INTSRC_VINT		(0x01 << 5)

#define POLL_TIME_MS		10
#define CAPTURE_POLL_TIME_MS    1000

/* maximum time for one frame in norma light */
#define ONE_FRAME_DELAY_MS_NORMAL		66
/* maximum time for one frame in low light: minimum 10fps. */
#define ONE_FRAME_DELAY_MS_LOW			100
/* maximum time for one frame in night mode: 6fps */
#define ONE_FRAME_DELAY_MS_NIGHTMODE		166

/* level at or below which we need to enable flash when in auto mode */
#define LUX_LEVEL_MAX			0x00 /* the brightest */
#define LUX_LEVEL_LOW			0x3D /* low light */
#define LUX_LEVEL_FLASH_ON		0x2B

/* Count for loop */
#define ISX012_CNT_CAPTURE_FRM		330
#define ISX012_CNT_CLEAR_VINT		20
#define ISX012_CNT_AE_STABLE		100 /* for checking MODESEL_FIX */
#define ISX012_CNT_CAPTURE_AWB		3 /* 8 -> 3 */
#define ISX012_CNT_OM_CHECK		30
#define ISX012_CNT_CM_CHECK		280 /* 160 -> 180 */
#define ISX012_CNT_STREAMOFF		300

#define AF_SEARCH_COUNT			550 /* about 6s */
#define AE_STABLE_SEARCH_COUNT		7

/* Sensor AF first,second window size.
 * we use constant values intead of reading sensor register */
#define DEFAULT_WINDOW_WIDTH		80
#define DEFAULT_WINDOW_HEIGHT		80
#define AF_PRECISION	100

/* diff value fior fast AE in preview */
#define AESCL_DIFF_FASTAE		1000

/*
 * Register Address Definition
 */
#define REG_INTSTS			0x000E
#define REG_INTCLR			0x0012
#define REG_ESD				0x005E

#define REG_MODESEL_FIX			0x0080
#define REG_MODESEL			0x0081
#define REG_HSIZE_MONI			0x0090
#define REG_HSIZE_CAP			0x0092
#define REG_VSIZE_MONI			0x0096
#define REG_VSIZE_CAP			0x0098
#define REG_CAPNUM			0x00B6

#define REG_CAP_GAINOFFSET		0x0186
#define REG_ISOSENS_OUT			0x019A
#define REG_SHT_TIME_OUT_L		0x019C
#define REG_SHT_TIME_OUT_H		0x019E

#define REG_USER_GAINLEVEL_NOW		0x01A5
#define REG_HALF_MOVE_STS		0x01B0
#define REG_ERRSCL_AUTO			0x01CA
#define REG_ERRSCL_NOW			0x01CC
#define REG_USER_AESCL_AUTO		0x01CE
#define REG_USER_AESCL_NOW		0x01D0

#define REG_AWB_SN1			0x0282
#define REG_AE_SN1			0x0294
#define REG_AE_SN4			0x0297
#define REG_AE_SN7			0x029A
#define REG_AE_SN11			0x029E

#define REG_CPUEXT			0x5000
#define REG_MANOUTGAIN			0x5E02
#define REG_VPARA_TRG			0x8800
#define REG_AWBSTS			0x8A24
#define REG_AF_STATE			0x8B8A
#define REG_AF_RESUNT			0x8B8B
#define REG_AESCL			0x8BC0

/*
 * Bit definition of register
 */
/* CPUEXT register */
#define REG_CPUEXT_AE_HOLD		(0x01 << 1)
#define REG_CPUEXT_AWB_HOLD		(0x01 << 2)

/* interrupt register */
#define REG_INTBIT_OM			(0x01 << 0)
#define REG_INTBIT_CM			(0x01 << 1)
#define REG_INTBIT_CAPNUM_END		(0x01 << 3)
#define REG_INTBIT_VINT			(0x01 << 5)

#endif /* __ISX012_H__ */
