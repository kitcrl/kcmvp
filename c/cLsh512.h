/*****************************************************************************/
/*                                                                           */
/*            DVLab (Data Visualization Lab) CORE version 1.0                */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*  File Name         : lsh512.h                                             */
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
#ifndef __LSH512_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __LSH512_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include "_xcrypt.h"

#define LSH_SUCCESS					0x0
#define LSH_ERR_NULL_PTR			0x2401
#define LSH_ERR_INVALID_ALGTYPE		0x2402
#define LSH_ERR_INVALID_DATABITLEN	0x2403
#define LSH_ERR_INVALID_STATE		0x2404

#define LSH_TYPE_512_512				0x0010040
#define LSH_TYPE_512_384				0x0010030
#define LSH_TYPE_512_256				0x0010020
#define LSH_TYPE_512_224				0x001001C

#define LSH_TYPE_384					LSH_TYPE_512_384
#define LSH_TYPE_512					LSH_TYPE_512_512

/**
 * @brief lsh handle creation rountine
 * @param hdl output, double pointer of a handle
 * @return always return 0
 */
_C_API_ __PFX__ uint32_t lsh512_create(void** hdl);

/**
 * @brief lsh handle destroy rountine
 * @param hdl input, double pointer of a handle
 * @return always return 0
 */
_C_API_ __PFX__ uint32_t lsh512_destroy(void** hdl);

/**
 * @brief lsh initialize rountine
 * @param hdl input, pointer of a handle
 * @param algtype input, a type of algorithms
 * @return always return 0
 */
_C_API_ __PFX__ uint32_t lsh512_init(void* hdl, const uint32_t algtype);

/**
 * @brief lsh update rountine
 * @param hdl input, pointer of a handle
 * @param data input, vector
 * @param databitlen input, a length of data
 * @return always return 0
 */
_C_API_ __PFX__ uint32_t lsh512_update(void* hdl, const uint8_t* data, unsigned long long databitlen);

/**
 * @brief lsh fianlize rountine
 * @param hdl input, pointer of a handle
 * @param hashval output, hash value
 * @return always return 0
 */
_C_API_ __PFX__ uint32_t lsh512_final(void* hdl, uint8_t* hashval);

_C_API_ __PFX__ uint32_t lsh512_digest(const uint32_t algtype, const uint8_t* data, unsigned long long databitlen, uint8_t* hashval);

#endif