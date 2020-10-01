/*****************************************************************************/
/*                                                                           */
/*            DVLab (Data Visualization Lab) CORE version 1.0                */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*  File Name         : lea.h                                                */
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
#ifndef __LEA_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __LEA_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include "_xcrypt.h"

/**
 * @brief leakey, round info generation rountine
 * @param leakey output, leakey
 * @param round output, round info
 * @param key input, user key
 * @param sz input, key size
 * @return round info
 */
_C_API_ __PFX__ int32_t lea_setup( uint32_t* leakey, uint32_t* round, uint8_t* key, int32_t sz);

/**
 * @brief ecb encryption rountine
 * @param leakey input, leakey
 * @param round input, round info
 * @param in input, plain text
 * @param sz input, length of plain text
 * @param out output, cipher text
 * @param osz output, length of cipher text
 * @return always return 0
 */
_C_API_ __PFX__ int32_t lea_ecb_encode(uint32_t* leakey, uint32_t round, uint8_t* in, int32_t sz, uint32_t* out);
/**
 * @brief ecb decryption rountine
 * @param leakey input, leakey
 * @param round input, round info
 * @param in input, cipher text
 * @param sz input, length of cipher text
 * @param out output, plain text
 * @param osz output, length of plain text
 * @return always return 0
 */
_C_API_ __PFX__ int32_t lea_ecb_decode(uint32_t* leakey, uint32_t round, uint8_t* in, int32_t sz, uint32_t* out);

/**
 * @brief cbc encryption rountine
 * @param leakey input, leakey
 * @param round input, round info
 * @param iv input, initial vector
 * @param in input, plain text
 * @param sz input, length of plain text
 * @param out output, cipher text
 * @param osz output, length of cipher text
 * @return always return 0
 */
_C_API_ __PFX__ int32_t lea_cbc_encode(uint32_t* leakey, uint32_t round, uint8_t* iv, uint8_t* in, int32_t sz, uint32_t* out);
/**
 * @brief cbc decryption rountine
 * @param leakey input, leakey
 * @param round input, round info
 * @param iv input, initial vector
 * @param in input, cipher text
 * @param sz input, length of cipher text
 * @param out output, plain text
 * @param osz output, length of plain text
 * @return always return 0
 */
_C_API_ __PFX__ int32_t lea_cbc_decode(uint32_t* leakey, uint32_t round, uint8_t* iv, uint8_t* in, int32_t sz, uint32_t* out);

/**
 * @brief counter encryption rountine
 * @param leakey input, leakey
 * @param round input, round info
 * @param ctr input, counter
 * @param in input, plain text
 * @param sz input, length of plain text
 * @param out output, cipher text
 * @param osz output, length of cipher text
 * @return always return 0
 */
_C_API_ __PFX__ int32_t lea_ctr_encode(uint32_t* leakey, uint32_t round, uint8_t* ctr, uint8_t* in, int32_t sz, uint32_t* out);
/**
 * @brief counter decryption rountine
 * @param leakey input, leakey
 * @param round input, round info
 * @param iv input, initial vector
 * @param in input, cipher text
 * @param sz input, length of cipher text
 * @param out output, plain text
 * @param osz output, length of plain text
 * @return always return 0
 */
_C_API_ __PFX__ int32_t lea_ctr_decode(uint32_t* leakey, uint32_t round, uint8_t* ctr, uint8_t* in, int32_t sz, uint32_t* out);



#endif
