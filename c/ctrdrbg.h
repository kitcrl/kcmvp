/*****************************************************************************/
/*                                                                           */
/*            DVLab (Data Visualization Lab) CORE version 1.0                */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*  File Name         : ctrdrbg.h                                            */
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
#ifndef __CTRDRBG_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __CTRDRBG_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include "_xcrypt.h"


#define ALGO_SEED                 1
#define ALGO_ARIA128              2
#define ALGO_ARIA192              3
#define ALGO_ARIA256              4
//------------------------------------------------
// The following values define either using derivation-function or not
// when KISA_CTR_DRBG_Instantiate(..., unsigned char derivation_function_flag) is called.
#define NON_DERIVATION_FUNCTION					0x00
#define USE_DERIVATION_FUNCTION					0xFF


_C_API_ __PFX__ int ctrdrbg_init(void** hdl, unsigned char algorithm, unsigned char* a, int asz, unsigned char* b, int bsz, unsigned char* c, int csz, unsigned char flg);
_C_API_ __PFX__ int ctrdrbg_release(void** hdl);
_C_API_ __PFX__ int ctrdrbg_generate(void* hdl, unsigned char* output, int requested_num_of_bits, unsigned char* addtional_input, int addlen);
_C_API_ __PFX__ int ctrdrbg_reseed(void* hdl, unsigned char* entropy_input, int entropylen, unsigned char* additional_input, int addlen);

#endif
