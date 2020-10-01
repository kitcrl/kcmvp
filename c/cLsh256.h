/*****************************************************************************/
/*                                                                           */
/*            DVLab (Data Visualization Lab) CORE version 1.0                */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*  File Name         : lsh256.h                                             */
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
#ifndef __LSH256_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __LSH256_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include "_xcrypt.h"

#define LSH_SUCCESS					0x0
#define LSH_ERR_NULL_PTR			0x2401
#define LSH_ERR_INVALID_ALGTYPE		0x2402
#define LSH_ERR_INVALID_DATABITLEN	0x2403
#define LSH_ERR_INVALID_STATE		0x2404

#define LSH_TYPE_256_256				0x0000020
#define LSH_TYPE_256_224				0x000001C

#define LSH_TYPE_224					LSH_TYPE_256_224
#define LSH_TYPE_256					LSH_TYPE_256_256



/**
 * @brief lsh handle creation rountine
 * @param hdl output, double pointer of a handle
 * @return always return 0
 */
_C_API_ __PFX__ int32_t lsh256_create(void** hdl);

/**
 * @brief lsh handle destroy rountine
 * @param hdl input, double pointer of a handle
 * @return always return 0
 */
_C_API_ __PFX__ int32_t lsh256_destroy(void** hdl);


/**
 * @brief lsh initialize rountine
 * @param hdl input, pointer of a handle
 * @param algtype input, a type of algorithms
 * @return always return 0
 */
_C_API_ __PFX__ int32_t lsh256_init (void* hdl, const uint32_t algtype);

/**
 * @brief lsh update rountine
 * @param hdl input, pointer of a handle
 * @param data input, vector
 * @param databitlen input, a length of data
 * @return always return 0
 */
_C_API_ __PFX__ int32_t lsh256_update(void* hdl, const uint8_t * data, uint32_t databitlen);//lsh_update(&ctx, g_lsh_testvector_data, g_lsh256_testvector_step[i]);

/**
 * @brief lsh fianlize rountine
 * @param hdl input, pointer of a handle
 * @param hashval output, hash value
 * @return always return 0
 */
_C_API_ __PFX__ int32_t lsh256_final(void* hdl, uint8_t * hashval);//lsh_final(&ctx, hashval);

_C_API_ __PFX__ int32_t lsh256_digest(const uint32_t algtype, const uint8_t * data, uint32_t databitlen, uint8_t * hashval);

#endif