/*****************************************************************************/
/*                                                                           */
/*            DVLab (Data Visualization Lab) CORE version 1.0                */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*  File Name         : cAria.h                                              */
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
#ifndef __CARIA_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __CARIA_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include "_xcrypt.h"

/**
 * @brief Encryption round key generation rountine
 * @param w0 input, master key
 * @param e output, encryption round key
 * @param keyBits input, a number of bits of the master key
 * @return a number of round
 */
_C_API_ __PFX__ int32_t ekey_setup(const uint8_t *w0, uint8_t *e, int32_t keyBits);


/**
 * @brief Decryption round key generation rountine
 * @param w0 input, master key
 * @param e output, decryption round key
 * @param keyBits input, a number of bits of the master key
 * @return a number of round
 */
_C_API_ __PFX__ int32_t dkey_setup(const uint8_t *w0, uint8_t *d, int32_t keyBits);



/**
 * @brief Encryption and decryption rountine
 * @param p input, plain text,
 * @param R input, a number of round of encryption or decryption
 * @param e output, round keys
 * @param c output, cipher text
 */
_C_API_ __PFX__ void aria_crypt(const uint8_t *p, int32_t R, const uint8_t *e, uint8_t *c);

//extern uint8_t S[4][256];
//extern const uint8_t KRK[3][16];

#endif