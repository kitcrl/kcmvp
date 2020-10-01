/*****************************************************************************/
/*                                                                           */
/*            DVLab (Data Visualization Lab) CORE version 1.0                */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*  File Name         : cHight.h                                             */
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
#ifndef __CHIGHT_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __CHIGHT_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include "_xcrypt.h"

#define BLOCK_SIZE_HIGHT                   8
#define BLOCK_SIZE_HIGHT_INT               2



// ECB
/**
 * @brief ECB Round key generation rountine
 * @param ukey input, user key
 * @param sz input, size of user key
 * @param rkey output, round key of the user key
 * @return always return 0.
 */
_C_API_ __PFX__ int32_t hight_key_schedule(uint8_t* ukey, uint32_t sz, uint8_t* rkey);

/**
 * @brief Encryption rountine
 * @param rkey input, round key
 * @param dat input and output, to be encrypted data
 * @return always return 0.
 */
_C_API_ __PFX__ int32_t hight_encrypt(uint8_t* rkey, uint8_t* dat);

/**
 * @brief Encryption rountine
 * @param rkey input, round key
 * @param dat input and output, to decrypted data
 * @return always return 0.
 */
_C_API_ __PFX__ int32_t hight_decrypt(uint8_t* rkey,uint8_t* dat);

/**
 * @brief ECB Encryption rountine
 * @param key input, user key
 * @param in input, plain text
 * @param isz input, plain text length
 * @param out output, cipher text
 * @param osz output, cipher text length
 * @return cipher text length
 */
_C_API_ __PFX__ int32_t hight_ecb_encode(uint8_t* key, uint8_t* in, int32_t isz, uint8_t* out);

/**
 * @brief ECB Decryption rountine
 * @param key input, user key
 * @param in input, cipher text
 * @param isz input, cipher text length
 * @param out output, plain text
 * @param osz output, plain text length
 * @return plain text length
 */
_C_API_ __PFX__ int32_t hight_ecb_decode(uint8_t* key, uint8_t* in, int32_t isz, uint8_t* out);



/**
 * @brief CBC Encryption rountine
 * @param key input, user key
 * @param iv input, initial vector
 * @param in input, plain text
 * @param isz input, plain text length
 * @param out output, cipher text
 * @param osz output, cipher text length
 * @return cipher text length
 */
_C_API_ __PFX__ int32_t hight_cbc_encode(uint8_t* key, uint8_t* iv, uint8_t* in, int32_t isz, uint8_t* out);

/**
 * @brief CBC Decryption rountine
 * @param key input, user key
 * @param iv input, initial vector
 * @param in input, cipher text
 * @param isz input, cipher text length
 * @param out output, plain text
 * @param osz output, plain text length
 * @return plain text length
 */
_C_API_ __PFX__ int32_t hight_cbc_decode(uint8_t* key, uint8_t* iv, uint8_t* in, int32_t isz, uint8_t* out);


/**
 * @brief Counter Encryption rountine
 * @param key input, user key
 * @param iv input, initial vector
 * @param counter input, counter
 * @param in input, plain text
 * @param isz input, plain text length
 * @param out output, cipher text
 * @return cipher text length
 */
_C_API_ __PFX__ int32_t hight_ctr_encode(uint32_t* key, uint8_t* iv, uint8_t* counter, uint8_t* in, int32_t isz, uint8_t* out);

/**
 * @brief Counter Encryption rountine
 * @param key input, user key
 * @param iv input, initial vector
 * @param counter input, counter
 * @param in input, cipher text
 * @param isz input, cipher text length
 * @param out output, plain text
 * @return plain text length
 */
_C_API_ __PFX__ int32_t hight_ctr_decode(uint32_t* key, uint8_t* iv, uint8_t* counter, uint8_t* in, int32_t isz, uint8_t* out);


#endif
