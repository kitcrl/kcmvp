/*****************************************************************************/
/*                                                                           */
/*            DVLab (Data Visualization Lab) CORE version 1.0                */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*  File Name         : sifrkiterr.h                                         */
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
#ifndef __SIFRKITERR_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __SIFRKITERR_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#define E_SUCCESS                           0
#define ERROR                               0x80000000

#define E_FAIL                              0x00000001
#define E_SIZE                              0x00000002
#define E_NULL                              0x0000000F

#define E_INPUT                             0x00000010
#define E_OUTPUT                            0x00000020
#define E_ENCODE                            0x00000030
#define E_DECODE                            0x00000040
#define E_BUFFER                            0x00000050
#define E_KEY                               0x00000060
#define E_IV                                0x00000070
#define E_COUNTER                           0x00000080

#define E_ECB                               0x01000000
#define E_CBC                               0x02000000
#define E_CTR                               0x03000000
#define E_CCM                               0x04000000
#define E_GCM                               0x05000000
#define E_OFB                               0x06000000


#define E_ARIA                              (ERROR|0x10000000)
#define E_HIGHT                             (ERROR|0x20000000)
#define E_LEA                               (ERROR|0x30000000)
#define E_LSH256                            (ERROR|0x40000000)
#define E_SEED                              (ERROR|0x50000000)
#define E_SHA256                            (ERROR|0x60000000)







#endif
