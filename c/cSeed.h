/*****************************************************************************/
/*                                                                           */
/*            DVLab (Data Visualization Lab) CORE version 1.0                */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*  File Name         : cSeed.h                                              */
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
#ifndef __CXSEED_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __CXSEED_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include "_xcrypt.h"

#define BLOCK_SIZE_SEED             16
#define BLOCK_SIZE_SEED_INT         4

#define SEED_128              BIT_128
#define SEED_256              BIT_256


/**
 * @brief seed ecb encryption routine
 * @param key input, seed key
 * @param a input, plain text
 * @param sz1 input, size of the a
 * @param b output, cipher text
 * @param sz2 out, size of the b
 * @return size of the b from processed
 */
_C_API_ __PFX__ int32_t seed_ecb_encode(uint8_t* key, int8_t* in, int32_t isz, int8_t* out);

/**
 * @brief seed ecb decryption routine
 * @param key input, seed key
 * @param a input, cipher text
 * @param sz1 input, size of the a
 * @param b output, plain text
 * @param sz2 out, size of the b
 * @return size of the b from processed
 */
_C_API_ __PFX__ int32_t seed_ecb_decode(uint8_t* key, int8_t* in, int32_t isz, int8_t* out);


/**
 * @brief seed ecb encryption routine
 * @param key input, seed key
 * @param iv input, initial vector
 * @param in input, input text
 * @param isz input, size of the isz
 * @param out output, output text
 * @param osz output, size of the out
 * @return size of the out from processed
 */
_C_API_ __PFX__ int32_t seed_cbc_encode(uint32_t* key, uint32_t* iv, uint8_t* in, int32_t isz, uint8_t* out);

/**
 * @brief seed ecb decryption routine
 * @param key input, seed key
 * @param iv input, initial vector
 * @param in input, input text
 * @param isz input, size of the isz
 * @param out output, output text
 * @param osz output, size of the out
 * @return size of the out from processed
 */
_C_API_ __PFX__ int32_t seed_cbc_decode(uint32_t* key, uint32_t* iv, uint8_t* in, int32_t isz, uint8_t* out);


/**
 * @brief seed ctr encryption routine
 * @param key input, user key
 * @param counter input, counter
 * @param iv input, initial vector
 * @param in input, input text
 * @param isz input, size of the isz
 * @param out output, output text
 * @param osz output, size of the out
 * @return size of the out from processed
 */
_C_API_ __PFX__ int32_t seed_ctr_encode(uint32_t* key, uint8_t* counter, uint8_t* in, int32_t isz, uint8_t* out);


/**
 * @brief seed ctr encryption routine
 * @param key input, user key
 * @param counter input, counter
 * @param iv input, initial vector
 * @param in input, input text
 * @param isz input, size of the isz
 * @param out output, output text
 * @param osz output, size of the out
 * @return size of the out from processed
 */
_C_API_ __PFX__ int32_t seed_ctr_decode(uint32_t* key, uint8_t* counter, uint8_t* in, int32_t isz, uint8_t* out);





#endif
