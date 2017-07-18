#ifndef NX_PDM_H
#define NX_PDM_H

#define AGCPDM_MAJOR_VER	(0)
#define AGCPDM_MINOR_VER	(10)
#define AGCPDM_REV			(1)


/*
 * API usage :
 *   pdm_Init --> pdm_GetVersion(option) --> pdm_SetParam(option) --> pdm_Run or pdm_Run_channel
 */


/*
 * parameter enumerate factor
 */
enum {
	PDM_PARAM_GAIN			= 0x00000001,
};
/*
 * PDM GAIN Parameter :
 *  This value controls the gain of the "PDM" output.
 *  The smaller the value, the larger the output output.
 *  The larger the value, the smaller the output output.
 */
#define	PARAM_GAIN_MIN		(2)
#define	PARAM_GAIN_MAX		(6)
#define	PARAM_GAIN_DEF		(4)

#if __cplusplus
extern "C" {
#endif

typedef struct {
	int GeneratedFilterBlock_states[256];
} pdmLPF_STATDEF;

typedef struct {
	int StatesBuff[256];
	int TapDelayIn;
	int PhaseIdx;
	int CoeffIdx;
	int OutIdx;
	int Sums;
} pdmHBF_STATDEF;

typedef struct {
	int frames;
	long int sum;
	int iGain;
	int IntpGain;
	int max1, max2, max3, max4;
	int dc_offset;
	int sum_table[20];
	pdmLPF_STATDEF lpf_st;
} agc_STATDEF;

typedef struct {
	agc_STATDEF agc_st[4];
	int Sigma1[4], Sigma2[4], Sigma3[4], Sigma4[4], Sigma5[4];
	int Delta1[4], Delta2[4], Delta3[4], Delta4[4];
	int OldDelta1[4], OldDelta2[4], OldDelta3[4], OldDelta4[4];
	int OldSigma5[4];
	int ScaleValue;
} pdm_STATDEF;

/*
 * pdm_Init - initialize pdm to pcm function
 * @pdm_STATDEF: address of the stativ variable structure
 */
void pdm_Init(pdm_STATDEF *pdm_STATDEF);

/**
 * pdm_Run - covert 4 channel pdm raw data to 4 channel pcm data
 *
 *
 * @pdm_st: pointer to an pdm_STATDEF structure
 *
 * @outbuf: converted pcm data, data buffer size must be 2048 bytes,
 *	    pcm out data format : 4 channel pcm
 *		L0[16B] / R0[16B]
 *		L1[16B] / R1[16B]
 *		.....
 *
 * @inbuf: pdm raw data, data buffer size must be 8192 bytes,
 *	    pdm raw input data format :
 *		L0[1B]/R0[1B]/L1[1B]/R1[1B]/......
 *		.....
 *
 * @agc_dB: pcm data output gain value
 *
 * Convert pdm raw data (8192bytes) to interleved pcm format data(2048bytes)
 * This function same as pdm_Run_channel( pdm_st, outbuf, inbuf, agc_dB, 4, 0, 0 ).
 */
void pdm_Run(pdm_STATDEF *pdm_st, short *outbuf, int *inbuf, int agc_dB);

/**
 * pdm_Run_channel - covert pdm raw data to pcm data with channel
 *
 * @pdm_st: pointer to an pdm_STATDEF structure
 *
 * @outbuf: converted pcm data
 *	    pcm out data format :
 *	    if channels == 4, data buffer size must be 2048 bytes
 *		L0[16B] / R0[16B]
 *		L1[16B] / R1[16B]
 *		.....
 *	    if channels == 3, data buffer size must be 2048 bytes
 *		L0[16B] / R0[16B]
 *		L1[16B] / NULL
 *		.....
 *	    if channels == 2, data buffer size must be 1024 bytes
 *		L0[16B] / R0[16B]
 *		.....
 *	    if channels == 1, data buffer size must be 1024 bytes
 *		L0[16B] / NULL
 *		.....
 *
 * @inbuf: pdm raw data, data buffer size must be 8192 bytes,
 *	    pdm raw input data format :
 *		L0[1B]/R0[1B]/L1[1B]/R1[1B]/......
 *		.....
 *
 * @agc_dB: pcm data output gain value
 *
 * @channels: pdm raw data channel count to convert pcm data, support 1 ~ 4 channel
 *
 * @be: swap to big-endian
 *
 * @fast: fast mode
 *
 * Convert pdm raw data (8192bytes) to interleved pcm format data(2048bytes)
 */
void pdm_Run_channel(pdm_STATDEF *pdm_st, short *outbuf, int *inbuf,
			int agc_dB, int ch, int swap, int fast);


/**
 * pdm_GetParam - This function is used to get various configuration information.
 *
 * @pdm_st: pointer to an pdm_STATDEF structure
 *
 * @param: PARAMETER enumeration value. (see parameter enumerate factor)
 *
 * @value: 
 *
 * @return : returns 0 on success and -1 on failure.
 */
int pdm_GetParam(pdm_STATDEF *pdm_st, int param, int *pValue );


/**
 * pdm_SetParam - This function is used to set various configuration information.
 *
 * @pdm_st: pointer to an pdm_STATDEF structure
 *
 * @param: PARAMETER enumeration value. (see parameter enumerate factor)
 *
 * @value: 
 * 
 * @return : returns 0 on success and negative on failure.
 */
int pdm_SetParam(pdm_STATDEF *pdm_st, int param, int value );


/**
 * pdm_SetParam - This function is used to set various configuration information.
 *
 * @major : major version number
 *
 * @minor : minor version number
 *
 * @rev : revision number
 *
 */
void pdm_GetVersion( int *major, int *minor, int *rev );

#if __cplusplus
}
#endif

#endif	/* NX_PDM_H */