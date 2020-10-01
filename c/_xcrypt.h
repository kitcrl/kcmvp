/*****************************************************************************/
/*                                                                           */
/*            DVLab (Data Visualization Lab) CORE version 1.0                */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*  File Name         : xcrypt.h                                             */
/*                                                                           */
/*  Description       :                                                      */
/*                                                                           */
/*                                                                           */
/*  Issues / Problems : None                                                 */
/*                                                                           */
/*  Revision History  :                                                      */
/*                                                                           */
/*        DD MM YYYY   Author(s)        Changes (Describe the changes made)  */
/*        25 02 2019   Shin Seunghyeok  Draft                                */
/*                                                                           */
/*****************************************************************************/
#ifndef __XCRYPT_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __XCRYPT_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <stdarg.h>
#include <stdint.h>

#if defined __cplusplus
#define _C_API_ extern "C"
#else
#define _C_API_
#endif

#if defined LINUX
#define __PFX__
#elif (defined XWIN32 || defined WINCE) && defined XEXPORT
#define __PFX__ __declspec(dllexport)
#elif (defined XWIN32 || defined WINCE)  && defined XIMPORT
#define __PFX__ __declspec(dllimport)
#else
#define __PFX__
#endif

#define _BIG_ENDIAN_            1


#define sizeof_char_to_int32(a)      ((a%sizeof(int32_t))?(a/sizeof(int32_t))+1:(a/sizeof(int32_t)))
#define sizeof_int32_to_char(a)      ( a*sizeof(int32_t))
#define CHANGE_SEQ(a)                ( ((a&0xFF000000)>>24) | ((a&0x00FF0000)>>8) | ((a&0x0000FF00)<<8) | ((a&0x000000FF)<<24) )

#define PROCESSING_BLOCK_SIZE_8                8
#define PROCESSING_BLOCK_SIZE_16               16
#define PROCESSING_BLOCK_SIZE_32               32
#define BIT_128               PROCESSING_BLOCK_SIZE_16
#define BIT_256               PROCESSING_BLOCK_SIZE_32
#define BIT_512               PROCESSING_BLOCK_SIZE_64


#define BLOCK_XOR_16(x, y, z) {                   \
	x[0] = y[0] ^ z[0];                             \
	x[1] = y[1] ^ z[1];                             \
	x[2] = y[2] ^ z[2];                             \
	x[3] = y[3] ^ z[3];                             \
}

#define BLOCK_XOR_8(x, y, z) {                    \
	x[0] = y[0] ^ z[0];                             \
	x[1] = y[1] ^ z[1];                             \
}



#define BYTE0(A)  ( (uint8_t)(((A)    )&0x000000FF) )
#define BYTE1(A)  ( (uint8_t)(((A)>> 8)&0x000000FF) )
#define BYTE2(A)  ( (uint8_t)(((A)>>16)&0x000000FF) )
#define BYTE3(A)  ( (uint8_t)(((A)>>24)&0x000000FF) )


typedef enum _NONCE_TYPE
{
	NONCE_NONE,
	NONCE_OR,
	NONCE_AND,
	NONCE_XOR,
}NONCE_TYPE;


#endif
