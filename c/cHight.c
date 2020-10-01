#include <cHight.h>

static uint8_t Delta[128] = {
    0x5A,0x6D,0x36,0x1B,0x0D,0x06,0x03,0x41,
    0x60,0x30,0x18,0x4C,0x66,0x33,0x59,0x2C,
    0x56,0x2B,0x15,0x4A,0x65,0x72,0x39,0x1C,
    0x4E,0x67,0x73,0x79,0x3C,0x5E,0x6F,0x37,
    0x5B,0x2D,0x16,0x0B,0x05,0x42,0x21,0x50,
    0x28,0x54,0x2A,0x55,0x6A,0x75,0x7A,0x7D,
    0x3E,0x5F,0x2F,0x17,0x4B,0x25,0x52,0x29,
    0x14,0x0A,0x45,0x62,0x31,0x58,0x6C,0x76,
    0x3B,0x1D,0x0E,0x47,0x63,0x71,0x78,0x7C,
    0x7E,0x7F,0x3F,0x1F,0x0F,0x07,0x43,0x61,
    0x70,0x38,0x5C,0x6E,0x77,0x7B,0x3D,0x1E,
    0x4F,0x27,0x53,0x69,0x34,0x1A,0x4D,0x26,
    0x13,0x49,0x24,0x12,0x09,0x04,0x02,0x01,
    0x40,0x20,0x10,0x08,0x44,0x22,0x11,0x48,
    0x64,0x32,0x19,0x0C,0x46,0x23,0x51,0x68,
    0x74,0x3A,0x5D,0x2E,0x57,0x6B,0x35,0x5A};

static uint8_t F0[256] = {
    0x00,0x86,0x0D,0x8B,0x1A,0x9C,0x17,0x91,
    0x34,0xB2,0x39,0xBF,0x2E,0xA8,0x23,0xA5,
    0x68,0xEE,0x65,0xE3,0x72,0xF4,0x7F,0xF9,
    0x5C,0xDA,0x51,0xD7,0x46,0xC0,0x4B,0xCD,
    0xD0,0x56,0xDD,0x5B,0xCA,0x4C,0xC7,0x41,
    0xE4,0x62,0xE9,0x6F,0xFE,0x78,0xF3,0x75,
    0xB8,0x3E,0xB5,0x33,0xA2,0x24,0xAF,0x29,
    0x8C,0x0A,0x81,0x07,0x96,0x10,0x9B,0x1D,
    0xA1,0x27,0xAC,0x2A,0xBB,0x3D,0xB6,0x30,
    0x95,0x13,0x98,0x1E,0x8F,0x09,0x82,0x04,
    0xC9,0x4F,0xC4,0x42,0xD3,0x55,0xDE,0x58,
    0xFD,0x7B,0xF0,0x76,0xE7,0x61,0xEA,0x6C,
    0x71,0xF7,0x7C,0xFA,0x6B,0xED,0x66,0xE0,
    0x45,0xC3,0x48,0xCE,0x5F,0xD9,0x52,0xD4,
    0x19,0x9F,0x14,0x92,0x03,0x85,0x0E,0x88,
    0x2D,0xAB,0x20,0xA6,0x37,0xB1,0x3A,0xBC,
    0x43,0xC5,0x4E,0xC8,0x59,0xDF,0x54,0xD2,
    0x77,0xF1,0x7A,0xFC,0x6D,0xEB,0x60,0xE6,
    0x2B,0xAD,0x26,0xA0,0x31,0xB7,0x3C,0xBA,
    0x1F,0x99,0x12,0x94,0x05,0x83,0x08,0x8E,
    0x93,0x15,0x9E,0x18,0x89,0x0F,0x84,0x02,
    0xA7,0x21,0xAA,0x2C,0xBD,0x3B,0xB0,0x36,
    0xFB,0x7D,0xF6,0x70,0xE1,0x67,0xEC,0x6A,
    0xCF,0x49,0xC2,0x44,0xD5,0x53,0xD8,0x5E,
    0xE2,0x64,0xEF,0x69,0xF8,0x7E,0xF5,0x73,
    0xD6,0x50,0xDB,0x5D,0xCC,0x4A,0xC1,0x47,
    0x8A,0x0C,0x87,0x01,0x90,0x16,0x9D,0x1B,
    0xBE,0x38,0xB3,0x35,0xA4,0x22,0xA9,0x2F,
    0x32,0xB4,0x3F,0xB9,0x28,0xAE,0x25,0xA3,
    0x06,0x80,0x0B,0x8D,0x1C,0x9A,0x11,0x97,
    0x5A,0xDC,0x57,0xD1,0x40,0xC6,0x4D,0xCB,
    0x6E,0xE8,0x63,0xE5,0x74,0xF2,0x79,0xFF};

static uint8_t F1[256] = {
    0x00,0x58,0xB0,0xE8,0x61,0x39,0xD1,0x89,
    0xC2,0x9A,0x72,0x2A,0xA3,0xFB,0x13,0x4B,
    0x85,0xDD,0x35,0x6D,0xE4,0xBC,0x54,0x0C,
    0x47,0x1F,0xF7,0xAF,0x26,0x7E,0x96,0xCE,
    0x0B,0x53,0xBB,0xE3,0x6A,0x32,0xDA,0x82,
    0xC9,0x91,0x79,0x21,0xA8,0xF0,0x18,0x40,
    0x8E,0xD6,0x3E,0x66,0xEF,0xB7,0x5F,0x07,
    0x4C,0x14,0xFC,0xA4,0x2D,0x75,0x9D,0xC5,
    0x16,0x4E,0xA6,0xFE,0x77,0x2F,0xC7,0x9F,
    0xD4,0x8C,0x64,0x3C,0xB5,0xED,0x05,0x5D,
    0x93,0xCB,0x23,0x7B,0xF2,0xAA,0x42,0x1A,
    0x51,0x09,0xE1,0xB9,0x30,0x68,0x80,0xD8,
    0x1D,0x45,0xAD,0xF5,0x7C,0x24,0xCC,0x94,
    0xDF,0x87,0x6F,0x37,0xBE,0xE6,0x0E,0x56,
    0x98,0xC0,0x28,0x70,0xF9,0xA1,0x49,0x11,
    0x5A,0x02,0xEA,0xB2,0x3B,0x63,0x8B,0xD3,
    0x2C,0x74,0x9C,0xC4,0x4D,0x15,0xFD,0xA5,
    0xEE,0xB6,0x5E,0x06,0x8F,0xD7,0x3F,0x67,
    0xA9,0xF1,0x19,0x41,0xC8,0x90,0x78,0x20,
    0x6B,0x33,0xDB,0x83,0x0A,0x52,0xBA,0xE2,
    0x27,0x7F,0x97,0xCF,0x46,0x1E,0xF6,0xAE,
    0xE5,0xBD,0x55,0x0D,0x84,0xDC,0x34,0x6C,
    0xA2,0xFA,0x12,0x4A,0xC3,0x9B,0x73,0x2B,
    0x60,0x38,0xD0,0x88,0x01,0x59,0xB1,0xE9,
    0x3A,0x62,0x8A,0xD2,0x5B,0x03,0xEB,0xB3,
    0xF8,0xA0,0x48,0x10,0x99,0xC1,0x29,0x71,
    0xBF,0xE7,0x0F,0x57,0xDE,0x86,0x6E,0x36,
    0x7D,0x25,0xCD,0x95,0x1C,0x44,0xAC,0xF4,
    0x31,0x69,0x81,0xD9,0x50,0x08,0xE0,0xB8,
    0xF3,0xAB,0x43,0x1B,0x92,0xCA,0x22,0x7A,
    0xB4,0xEC,0x04,0x5C,0xD5,0x8D,0x65,0x3D,
    0x76,0x2E,0xC6,0x9E,0x17,0x4F,0xA7,0xFF};


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                              ECB                                  //////
//////                                                                   //////
//////                                                                   //////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*****************************************************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*****************************                ********************************/
/*******************************            **********************************/
/*********************************        ************************************/
/************************************   **************************************/
/************************************* ***************************************/
/*****************************************************************************/
int32_t hight_key_schedule(uint8_t* ukey, uint32_t sz, uint8_t* rkey)
{
  int32_t i, j;

  for( i=0; i<4; i++)
  {
    rkey[i  ] = ukey[i+12];
    rkey[i+4] = ukey[i   ];
  }

  for( i=0; i<8; i++)
  {
    for( j=0; j<8; j++)
      rkey[8+16*i+j  ] = (uint8_t) (ukey[(j-i)&7    ] + Delta[16*i+j  ]);	
    // Use "&7"  instead of the "%8" for Performance

    for( j=0; j<8; j++)
      rkey[8+16*i+j+8] = (uint8_t) (ukey[((j-i)&7)+8] + Delta[16*i+j+8]);
  }
  return 0;
}

int32_t hight_encrypt(uint8_t* rkey, uint8_t* dat)
{
    uint32_t   XX[8];

    // First Round
    XX[1] = dat[1];
    XX[3] = dat[3];
    XX[5] = dat[5];
    XX[7] = dat[7];

    XX[0] = (dat[0] + rkey[0]) & 0xFF;
    XX[2] = (dat[2] ^ rkey[1]);
    XX[4] = (dat[4] + rkey[2]) & 0xFF;
    XX[6] = (dat[6] ^ rkey[3]);

  // Encryption Round 
  #define HIGHT_ENC(k, i0,i1,i2,i3,i4,i5,i6,i7) {                   \
    XX[i0] = (XX[i0] ^ (F0[XX[i1]] + rkey[4*k+3])) & 0xFF;    \
    XX[i2] = (XX[i2] + (F1[XX[i3]] ^ rkey[4*k+2])) & 0xFF;    \
    XX[i4] = (XX[i4] ^ (F0[XX[i5]] + rkey[4*k+1])) & 0xFF;    \
    XX[i6] = (XX[i6] + (F1[XX[i7]] ^ rkey[4*k+0])) & 0xFF;    \
  }

  HIGHT_ENC( 2,  7,6,5,4,3,2,1,0);
  HIGHT_ENC( 3,  6,5,4,3,2,1,0,7);
  HIGHT_ENC( 4,  5,4,3,2,1,0,7,6);
  HIGHT_ENC( 5,  4,3,2,1,0,7,6,5);
  HIGHT_ENC( 6,  3,2,1,0,7,6,5,4);
  HIGHT_ENC( 7,  2,1,0,7,6,5,4,3);
  HIGHT_ENC( 8,  1,0,7,6,5,4,3,2);
  HIGHT_ENC( 9,  0,7,6,5,4,3,2,1);
  HIGHT_ENC(10,  7,6,5,4,3,2,1,0);
  HIGHT_ENC(11,  6,5,4,3,2,1,0,7);
  HIGHT_ENC(12,  5,4,3,2,1,0,7,6);
  HIGHT_ENC(13,  4,3,2,1,0,7,6,5);
  HIGHT_ENC(14,  3,2,1,0,7,6,5,4);
  HIGHT_ENC(15,  2,1,0,7,6,5,4,3);
  HIGHT_ENC(16,  1,0,7,6,5,4,3,2);
  HIGHT_ENC(17,  0,7,6,5,4,3,2,1);
  HIGHT_ENC(18,  7,6,5,4,3,2,1,0);
  HIGHT_ENC(19,  6,5,4,3,2,1,0,7);
  HIGHT_ENC(20,  5,4,3,2,1,0,7,6);
  HIGHT_ENC(21,  4,3,2,1,0,7,6,5);
  HIGHT_ENC(22,  3,2,1,0,7,6,5,4);
  HIGHT_ENC(23,  2,1,0,7,6,5,4,3);
  HIGHT_ENC(24,  1,0,7,6,5,4,3,2);
  HIGHT_ENC(25,  0,7,6,5,4,3,2,1);
  HIGHT_ENC(26,  7,6,5,4,3,2,1,0);
  HIGHT_ENC(27,  6,5,4,3,2,1,0,7);
  HIGHT_ENC(28,  5,4,3,2,1,0,7,6);
  HIGHT_ENC(29,  4,3,2,1,0,7,6,5);
  HIGHT_ENC(30,  3,2,1,0,7,6,5,4);
  HIGHT_ENC(31,  2,1,0,7,6,5,4,3);
  HIGHT_ENC(32,  1,0,7,6,5,4,3,2);
  HIGHT_ENC(33,  0,7,6,5,4,3,2,1);

  // Final Round
  dat[1] = (uint8_t) XX[2];
  dat[3] = (uint8_t) XX[4];
  dat[5] = (uint8_t) XX[6];
  dat[7] = (uint8_t) XX[0];
  dat[0] = (uint8_t) (XX[1] + rkey[4]);
  dat[2] = (uint8_t) (XX[3] ^ rkey[5]);
  dat[4] = (uint8_t) (XX[5] + rkey[6]);
  dat[6] = (uint8_t) (XX[7] ^ rkey[7]);
  return 0;
}

int32_t hight_decrypt(uint8_t* rkey,uint8_t* dat)
{
  uint32_t   XX[8];

  XX[2] = (uint8_t) dat[1];
  XX[4] = (uint8_t) dat[3];
  XX[6] = (uint8_t) dat[5];
  XX[0] = (uint8_t) dat[7];

  XX[1] = (uint8_t) (dat[0] - rkey[4]);
  XX[3] = (uint8_t) (dat[2] ^ rkey[5]);
  XX[5] = (uint8_t) (dat[4] - rkey[6]);
  XX[7] = (uint8_t) (dat[6] ^ rkey[7]);

  #define HIGHT_DEC(k, i0,i1,i2,i3,i4,i5,i6,i7) {                   \
    XX[i1] = (XX[i1] - (F1[XX[i2]] ^ rkey[4*k+2])) & 0xFF;    \
    XX[i3] = (XX[i3] ^ (F0[XX[i4]] + rkey[4*k+1])) & 0xFF;    \
    XX[i5] = (XX[i5] - (F1[XX[i6]] ^ rkey[4*k+0])) & 0xFF;    \
    XX[i7] = (XX[i7] ^ (F0[XX[i0]] + rkey[4*k+3])) & 0xFF;    \
  }

  HIGHT_DEC(33,  7,6,5,4,3,2,1,0);
  HIGHT_DEC(32,  0,7,6,5,4,3,2,1);
  HIGHT_DEC(31,  1,0,7,6,5,4,3,2);
  HIGHT_DEC(30,  2,1,0,7,6,5,4,3);
  HIGHT_DEC(29,  3,2,1,0,7,6,5,4);
  HIGHT_DEC(28,  4,3,2,1,0,7,6,5);
  HIGHT_DEC(27,  5,4,3,2,1,0,7,6);
  HIGHT_DEC(26,  6,5,4,3,2,1,0,7);
  HIGHT_DEC(25,  7,6,5,4,3,2,1,0);
  HIGHT_DEC(24,  0,7,6,5,4,3,2,1);
  HIGHT_DEC(23,  1,0,7,6,5,4,3,2);
  HIGHT_DEC(22,  2,1,0,7,6,5,4,3);
  HIGHT_DEC(21,  3,2,1,0,7,6,5,4);
  HIGHT_DEC(20,  4,3,2,1,0,7,6,5);
  HIGHT_DEC(19,  5,4,3,2,1,0,7,6);
  HIGHT_DEC(18,  6,5,4,3,2,1,0,7);
  HIGHT_DEC(17,  7,6,5,4,3,2,1,0);
  HIGHT_DEC(16,  0,7,6,5,4,3,2,1);
  HIGHT_DEC(15,  1,0,7,6,5,4,3,2);
  HIGHT_DEC(14,  2,1,0,7,6,5,4,3);
  HIGHT_DEC(13,  3,2,1,0,7,6,5,4);
  HIGHT_DEC(12,  4,3,2,1,0,7,6,5);
  HIGHT_DEC(11,  5,4,3,2,1,0,7,6);
  HIGHT_DEC(10,  6,5,4,3,2,1,0,7);
  HIGHT_DEC( 9,  7,6,5,4,3,2,1,0);
  HIGHT_DEC( 8,  0,7,6,5,4,3,2,1);
  HIGHT_DEC( 7,  1,0,7,6,5,4,3,2);
  HIGHT_DEC( 6,  2,1,0,7,6,5,4,3);
  HIGHT_DEC( 5,  3,2,1,0,7,6,5,4);
  HIGHT_DEC( 4,  4,3,2,1,0,7,6,5);
  HIGHT_DEC( 3,  5,4,3,2,1,0,7,6);
  HIGHT_DEC( 2,  6,5,4,3,2,1,0,7);

  dat[1] = (uint8_t) (XX[1]);
  dat[3] = (uint8_t) (XX[3]);
  dat[5] = (uint8_t) (XX[5]);
  dat[7] = (uint8_t) (XX[7]);

  dat[0] = (uint8_t) (XX[0] - rkey[0]);
  dat[2] = (uint8_t) (XX[2] ^ rkey[1]);
  dat[4] = (uint8_t) (XX[4] - rkey[2]);
  dat[6] = (uint8_t) (XX[6] ^ rkey[3]);

  return 0;
}

int32_t hight_ecb_encode(uint8_t* key, uint8_t* in, int32_t isz, uint8_t* out)
{
  uint8_t hightkey[256];
  int32_t i=0;
  int32_t bsz;
  int32_t rsz;
  uint32_t block[2];

	hight_key_schedule( key, 16, hightkey );
	uint32_t osz;
  for ( i=0 ; i< isz; )
  {
		hight_encrypt(hightkey, in+i);
		memcpy(out+i, in+i, BLOCK_SIZE_HIGHT);
    i+= BLOCK_SIZE_HIGHT;
  }

  return i;
}


int32_t hight_ecb_decode(uint8_t* key, uint8_t* in, int32_t isz, uint8_t* out)
{
  int32_t i=0;
  int32_t bsz;
  int32_t rsz;
  int32_t pad;
  uint8_t hightkey[256];
  uint32_t block[2];

	hight_key_schedule( key, 16, hightkey );
	uint32_t osz;
  for ( i=0 ; i< isz; )
  {
		hight_decrypt(hightkey, in+i);
		memcpy(out+i, in+i, BLOCK_SIZE_HIGHT);
    i+= BLOCK_SIZE_HIGHT;
  }

  return i;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                              CBC                                  //////
//////                                                                   //////
//////                                                                   //////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*****************************************************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*****************************                ********************************/
/*******************************            **********************************/
/*********************************        ************************************/
/************************************   **************************************/
/************************************* ***************************************/
/*****************************************************************************/
#define EncIni_Transformation(x0,x2,x4,x6,mk0,mk1,mk2,mk3)	\
	t0 = x0 + mk0;										\
	t2 = x2 ^ mk1;										\
	t4 = x4 + mk2;										\
	t6 = x6 ^ mk3; 

#define EncFin_Transformation(x0,x2,x4,x6,mk0,mk1,mk2,mk3)	\
	out[0] = x0 + mk0;										\
	out[2] = x2 ^ mk1;										\
	out[4] = x4 + mk2;										\
	out[6] = x6 ^ mk3; 

#define Round(x7,x6,x5,x4,x3,x2,x1,x0)				\
	x1 += (F1[x0] ^ key[0]);				\
	x3 ^= (F0[x2] + key[1]);				\
	x5 += (F1[x4] ^ key[2]);				\
	x7 ^= (F0[x6] + key[3]);

void hight_ecb_encrypt_for_cbc(uint8_t* key128, uint8_t* usrkey, const uint8_t *in, uint8_t *out )
{
	register uint8_t t0, t1, t2, t3, t4, t5, t6, t7;
	uint8_t *key, *key2;

	key = key128;
	key2 = usrkey;

	t1 = in[1]; t3 = in[3]; t5 = in[5]; t7 = in[7];
	EncIni_Transformation( in[0], in[2], in[4], in[6], key2[12], key2[13], key2[14], key2[15] );

	Round(t7,t6,t5,t4,t3,t2,t1,t0);key += 4;		// 1
	Round(t6,t5,t4,t3,t2,t1,t0,t7);key += 4;		// 2
	Round(t5,t4,t3,t2,t1,t0,t7,t6);key += 4;		// 3
	Round(t4,t3,t2,t1,t0,t7,t6,t5);key += 4;		// 4
	Round(t3,t2,t1,t0,t7,t6,t5,t4);key += 4;		// 5
	Round(t2,t1,t0,t7,t6,t5,t4,t3);key += 4;		// 6
	Round(t1,t0,t7,t6,t5,t4,t3,t2);key += 4;		// 7
	Round(t0,t7,t6,t5,t4,t3,t2,t1);key += 4;		// 8
	Round(t7,t6,t5,t4,t3,t2,t1,t0);key += 4;		// 9
	Round(t6,t5,t4,t3,t2,t1,t0,t7);key += 4;		// 10
	Round(t5,t4,t3,t2,t1,t0,t7,t6);key += 4;		// 11
	Round(t4,t3,t2,t1,t0,t7,t6,t5);key += 4;		// 12
	Round(t3,t2,t1,t0,t7,t6,t5,t4);key += 4;		// 13
	Round(t2,t1,t0,t7,t6,t5,t4,t3);key += 4;		// 14
	Round(t1,t0,t7,t6,t5,t4,t3,t2);key += 4;		// 15
	Round(t0,t7,t6,t5,t4,t3,t2,t1);key += 4;		// 16
	Round(t7,t6,t5,t4,t3,t2,t1,t0);key += 4;		// 17
	Round(t6,t5,t4,t3,t2,t1,t0,t7);key += 4;		// 18
	Round(t5,t4,t3,t2,t1,t0,t7,t6);key += 4;		// 19
	Round(t4,t3,t2,t1,t0,t7,t6,t5);key += 4;		// 20
	Round(t3,t2,t1,t0,t7,t6,t5,t4);key += 4;		// 21
	Round(t2,t1,t0,t7,t6,t5,t4,t3);key += 4;		// 22
	Round(t1,t0,t7,t6,t5,t4,t3,t2);key += 4;		// 23
	Round(t0,t7,t6,t5,t4,t3,t2,t1);key += 4;		// 24
	Round(t7,t6,t5,t4,t3,t2,t1,t0);key += 4;		// 25
	Round(t6,t5,t4,t3,t2,t1,t0,t7);key += 4;		// 26
	Round(t5,t4,t3,t2,t1,t0,t7,t6);key += 4;		// 27
	Round(t4,t3,t2,t1,t0,t7,t6,t5);key += 4;		// 28
	Round(t3,t2,t1,t0,t7,t6,t5,t4);key += 4;		// 29
	Round(t2,t1,t0,t7,t6,t5,t4,t3);key += 4;		// 30
	Round(t1,t0,t7,t6,t5,t4,t3,t2);key += 4;		// 31
	Round(t0,t7,t6,t5,t4,t3,t2,t1);					// 32

	EncFin_Transformation( t1, t3, t5, t7, key2[0], key2[1], key2[2], key2[3] );

	out[1] = t2; out[3] = t4; out[5] = t6; out[7] = t0;
}

#define DecIni_Transformation(x0,x2,x4,x6,mk0,mk1,mk2,mk3)	\
	t0 = x0 - mk0;										\
	t2 = x2 ^ mk1;										\
	t4 = x4 - mk2;										\
	t6 = x6 ^ mk3; 

#define DecFin_Transformation(x0,x2,x4,x6,mk0,mk1,mk2,mk3)	\
	out[0] = x0 - mk0;										\
	out[2] = x2 ^ mk1;										\
	out[4] = x4 - mk2;										\
	out[6] = x6 ^ mk3; 


#define DRound(x7,x6,x5,x4,x3,x2,x1,x0)				\
	x1 = x1 - (F1[x0] ^ key[0]);				\
	x3 = x3 ^ (F0[x2] + key[1]);				\
	x5 = x5 - (F1[x4] ^ key[2]);				\
	x7 = x7 ^ (F0[x6] + key[3]); 

void hight_ecb_decrypt_for_cbc( uint8_t *key128, uint8_t *usrkey, const uint8_t *in, uint8_t *out )
{
	register uint8_t t0, t1, t2, t3, t4, t5, t6, t7;
	uint8_t *key, *key2;

	key = &(key128[124]);
	key2 = usrkey;

	t1 = in[1]; t3 = in[3]; t5 = in[5]; t7 = in[7];
	DecIni_Transformation( in[0], in[2], in[4], in[6], key2[0], key2[1], key2[2], key2[3] );

	DRound(t7,t6,t5,t4,t3,t2,t1,t0);key -= 4;
	DRound(t0,t7,t6,t5,t4,t3,t2,t1);key -= 4;
	DRound(t1,t0,t7,t6,t5,t4,t3,t2);key -= 4;
	DRound(t2,t1,t0,t7,t6,t5,t4,t3);key -= 4;
	DRound(t3,t2,t1,t0,t7,t6,t5,t4);key -= 4;
	DRound(t4,t3,t2,t1,t0,t7,t6,t5);key -= 4;
	DRound(t5,t4,t3,t2,t1,t0,t7,t6);key -= 4;
	DRound(t6,t5,t4,t3,t2,t1,t0,t7);key -= 4;
	DRound(t7,t6,t5,t4,t3,t2,t1,t0);key -= 4;
	DRound(t0,t7,t6,t5,t4,t3,t2,t1);key -= 4;
	DRound(t1,t0,t7,t6,t5,t4,t3,t2);key -= 4;
	DRound(t2,t1,t0,t7,t6,t5,t4,t3);key -= 4;
	DRound(t3,t2,t1,t0,t7,t6,t5,t4);key -= 4;
	DRound(t4,t3,t2,t1,t0,t7,t6,t5);key -= 4;
	DRound(t5,t4,t3,t2,t1,t0,t7,t6);key -= 4;
	DRound(t6,t5,t4,t3,t2,t1,t0,t7);key -= 4;
	DRound(t7,t6,t5,t4,t3,t2,t1,t0);key -= 4;
	DRound(t0,t7,t6,t5,t4,t3,t2,t1);key -= 4;
	DRound(t1,t0,t7,t6,t5,t4,t3,t2);key -= 4;
	DRound(t2,t1,t0,t7,t6,t5,t4,t3);key -= 4;
	DRound(t3,t2,t1,t0,t7,t6,t5,t4);key -= 4;
	DRound(t4,t3,t2,t1,t0,t7,t6,t5);key -= 4;
	DRound(t5,t4,t3,t2,t1,t0,t7,t6);key -= 4;
	DRound(t6,t5,t4,t3,t2,t1,t0,t7);key -= 4;
	DRound(t7,t6,t5,t4,t3,t2,t1,t0);key -= 4;
	DRound(t0,t7,t6,t5,t4,t3,t2,t1);key -= 4;
	DRound(t1,t0,t7,t6,t5,t4,t3,t2);key -= 4;
	DRound(t2,t1,t0,t7,t6,t5,t4,t3);key -= 4;
	DRound(t3,t2,t1,t0,t7,t6,t5,t4);key -= 4;
	DRound(t4,t3,t2,t1,t0,t7,t6,t5);key -= 4;
	DRound(t5,t4,t3,t2,t1,t0,t7,t6);key -= 4;
	DRound(t6,t5,t4,t3,t2,t1,t0,t7);

	DecFin_Transformation(t7, t1, t3, t5,key2[12],key2[13],key2[14],key2[15]);

	out[1] = t0; out[3] = t2; out[5] = t4; out[7] = t6;
}

int32_t hight_cbc_init( uint8_t* usrkey, uint8_t* iv, uint8_t* hkey)
{
	uint8_t i, j;

	for(i=0 ; i < BLOCK_SIZE_HIGHT ; i++)
	{
		for(j=0 ; j < BLOCK_SIZE_HIGHT ; j++)
			*(hkey + 16*i + j)= usrkey[(j-i)&7    ] + Delta[ 16*i + j ];

		for(j=0 ; j < BLOCK_SIZE_HIGHT ; j++)
			*(hkey + 16*i + j + 8 ) = usrkey[((j-i)&7)+8] + Delta[ 16*i + j + 8 ];
	}
	return 1;
}

int32_t hight_cbc_crypt(uint8_t* hightkey, uint8_t* usrkey,  uint32_t* iv, uint32_t* blck, uint32_t* in, int32_t isz, uint32_t* out, int32_t* osz, uint8_t mode)
{
	int32_t nCurrentCount = BLOCK_SIZE_HIGHT;
  int32_t _sz = isz - nCurrentCount;
	uint32_t *pdwXOR;

	if( mode == 'E' )
	{
		pdwXOR = iv;

		while( nCurrentCount <= isz )
		{
			BLOCK_XOR_8( out, in, pdwXOR );
			hight_ecb_encrypt_for_cbc( hightkey, usrkey, (uint8_t *)out, (uint8_t *)out );
			pdwXOR = out;
			nCurrentCount += BLOCK_SIZE_HIGHT;
			in += BLOCK_SIZE_HIGHT_INT;
			out += BLOCK_SIZE_HIGHT_INT;
		}
		
		*osz = nCurrentCount - BLOCK_SIZE_HIGHT;
		_sz = isz - *osz;

		memcpy( iv, pdwXOR, BLOCK_SIZE_HIGHT );
		memcpy( blck, in, _sz );
	}
	else
	{
		pdwXOR = iv;

		while( nCurrentCount <= isz )
		{
			hight_ecb_decrypt_for_cbc( hightkey, usrkey, (uint8_t *)in, (uint8_t *)out );
			
			BLOCK_XOR_8( out, out, pdwXOR );

			pdwXOR = in;

			nCurrentCount += BLOCK_SIZE_HIGHT;
			in += BLOCK_SIZE_HIGHT_INT;
			out += BLOCK_SIZE_HIGHT_INT;
		}
			
		_sz = *osz = nCurrentCount - BLOCK_SIZE_HIGHT;
		memcpy( iv, pdwXOR, BLOCK_SIZE_HIGHT );
		memcpy( blck, out - BLOCK_SIZE_HIGHT_INT, BLOCK_SIZE_HIGHT );
	}

	return _sz;
}

int32_t hight_cbc_release(uint8_t* hightkey, uint8_t* usrkey, uint32_t* iv,uint32_t* blck,int32_t sz, uint32_t *out,int32_t *osz,uint8_t mode )
{
	int32_t i;
	uint8_t *pout = (uint8_t *)(out);
	uint32_t pad;

	*osz = 0;

	if( mode == 'E' )
	{
		pad = BLOCK_SIZE_HIGHT - sz;
		for( i = sz; i<BLOCK_SIZE_HIGHT; i++ ) ((uint8_t *)blck)[i] = (uint8_t)pad;

		BLOCK_XOR_8( blck, blck, iv );
		hight_ecb_encrypt_for_cbc( hightkey, usrkey, (uint8_t *)blck, pout );

		out += BLOCK_SIZE_HIGHT_INT;
		*osz = BLOCK_SIZE_HIGHT;
	}
	else
	{
		pad = ((uint8_t*)blck)[BLOCK_SIZE_HIGHT-1];
		if( pad > 0 && pad <= BLOCK_SIZE_HIGHT )
		{
			for (i = pad; i>0; i--)
			{
				*(pout - i) = (uint8_t)0x00;
			}
			*osz = pad;
		}
		else 
			return 0;
	}

	return 1;
}


int32_t hight_cbc_encode(uint8_t* key, uint8_t* iv, uint8_t* in, int32_t isz, uint8_t* out)
{
  uint8_t hightkey[128];
  int32_t i=0;
  int32_t bsz;
  int32_t rsz;
  uint32_t block[2];

	hight_cbc_init( key, iv, hightkey );
	uint32_t osz;
  for ( i=0 ; i< isz; )
  {
    bsz = hight_cbc_crypt(hightkey, key, iv, block, (uint32_t*)(in+i), PROCESSING_BLOCK_SIZE_8, (uint32_t*)(out+i), &osz, 'E');
    i+= PROCESSING_BLOCK_SIZE_8;
  }
  //hight_cbc_release(hightkey, key, iv, block, bsz, (uint32_t*)(out+i),&osz, 'E');

  return i;
}


int32_t hight_cbc_decode(uint8_t* key, uint8_t* iv, uint8_t* in, int32_t isz, uint8_t* out)
{
  int32_t i=0;
  int32_t bsz;
  int32_t rsz;
  int32_t pad;
  uint8_t hightkey[128];
  uint32_t block[2];
	uint32_t osz;

	hight_cbc_init( key, iv, hightkey );
  for ( i=0 ; i< isz ; )
  {
    bsz = hight_cbc_crypt(hightkey, key, iv, block, (uint32_t*)(in+i), PROCESSING_BLOCK_SIZE_8, (uint32_t*)(out+i), &osz, 'D');
    i+= PROCESSING_BLOCK_SIZE_8;
  }

  return i;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                              CTR                                  //////
//////                                                                   //////
//////                                                                   //////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*****************************************************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*****************************                ********************************/
/*******************************            **********************************/
/*********************************        ************************************/
/************************************   **************************************/
/************************************* ***************************************/
/*****************************************************************************/

void hight_update_counter(uint8_t* out, int32_t incv, int32_t min ) 
{
	uint8_t bszBackup = 0;												
	int32_t i;															
																	
	if( 0 > min )												
		return ;													
																	
	if( 0 < min )												
	{																
		bszBackup = out[min];							
		out[min] += incv;						
	}																
																	
	for( i=min; i>1; --i )									
	{																
		if( bszBackup <= out[i] )							
			return;													
		else														
		{															
			bszBackup = out[i-1];							
			out[i-1] += 1;									
		}															
	}																
																	
	bszBackup = out[0];										
	out[0] += incv;									
}
#define EncIni_Transformation(x0,x2,x4,x6,mk0,mk1,mk2,mk3)	\
	t0 = x0 + mk0;											\
	t2 = x2 ^ mk1;											\
	t4 = x4 + mk2;											\
	t6 = x6 ^ mk3;											

#define EncFin_Transformation(x0,x2,x4,x6,mk0,mk1,mk2,mk3)	\
	out[0] = x0 + mk0;										\
	out[2] = x2 ^ mk1;										\
	out[4] = x4 + mk2;										\
	out[6] = x6 ^ mk3; 

#define Round(x7,x6,x5,x4,x3,x2,x1,x0)						\
	x1 += (F1[x0] ^ key[0]);								\
	x3 ^= (F0[x2] + key[1]);								\
	x5 += (F1[x4] ^ key[2]);								\
	x7 ^= (F0[x6] + key[3]);

void hight_ctr_block( uint8_t* key, uint8_t* usrkey, const uint8_t *in, uint8_t *out )
{
	register uint8_t t0, t1, t2, t3, t4, t5, t6, t7;

	t1 = in[1]; t3 = in[3]; t5 = in[5]; t7 = in[7];
	EncIni_Transformation(in[0],in[2],in[4],in[6],usrkey[12],usrkey[13],usrkey[14],usrkey[15]);

	Round(t7,t6,t5,t4,t3,t2,t1,t0);key += 4;		// 1
	Round(t6,t5,t4,t3,t2,t1,t0,t7);key += 4;		// 2
	Round(t5,t4,t3,t2,t1,t0,t7,t6);key += 4;		// 3
	Round(t4,t3,t2,t1,t0,t7,t6,t5);key += 4;		// 4
	Round(t3,t2,t1,t0,t7,t6,t5,t4);key += 4;		// 5
	Round(t2,t1,t0,t7,t6,t5,t4,t3);key += 4;		// 6
	Round(t1,t0,t7,t6,t5,t4,t3,t2);key += 4;		// 7
	Round(t0,t7,t6,t5,t4,t3,t2,t1);key += 4;		// 8
	Round(t7,t6,t5,t4,t3,t2,t1,t0);key += 4;		// 9
	Round(t6,t5,t4,t3,t2,t1,t0,t7);key += 4;		// 10
	Round(t5,t4,t3,t2,t1,t0,t7,t6);key += 4;		// 11
	Round(t4,t3,t2,t1,t0,t7,t6,t5);key += 4;		// 12
	Round(t3,t2,t1,t0,t7,t6,t5,t4);key += 4;		// 13
	Round(t2,t1,t0,t7,t6,t5,t4,t3);key += 4;		// 14
	Round(t1,t0,t7,t6,t5,t4,t3,t2);key += 4;		// 15
	Round(t0,t7,t6,t5,t4,t3,t2,t1);key += 4;		// 16
	Round(t7,t6,t5,t4,t3,t2,t1,t0);key += 4;		// 17
	Round(t6,t5,t4,t3,t2,t1,t0,t7);key += 4;		// 18
	Round(t5,t4,t3,t2,t1,t0,t7,t6);key += 4;		// 19
	Round(t4,t3,t2,t1,t0,t7,t6,t5);key += 4;		// 20
	Round(t3,t2,t1,t0,t7,t6,t5,t4);key += 4;		// 21
	Round(t2,t1,t0,t7,t6,t5,t4,t3);key += 4;		// 22
	Round(t1,t0,t7,t6,t5,t4,t3,t2);key += 4;		// 23
	Round(t0,t7,t6,t5,t4,t3,t2,t1);key += 4;		// 24
	Round(t7,t6,t5,t4,t3,t2,t1,t0);key += 4;		// 25
	Round(t6,t5,t4,t3,t2,t1,t0,t7);key += 4;		// 26
	Round(t5,t4,t3,t2,t1,t0,t7,t6);key += 4;		// 27
	Round(t4,t3,t2,t1,t0,t7,t6,t5);key += 4;		// 28
	Round(t3,t2,t1,t0,t7,t6,t5,t4);key += 4;		// 29
	Round(t2,t1,t0,t7,t6,t5,t4,t3);key += 4;		// 30
	Round(t1,t0,t7,t6,t5,t4,t3,t2);key += 4;		// 31
	Round(t0,t7,t6,t5,t4,t3,t2,t1);					// 32

	EncFin_Transformation(t1,t3,t5,t7,usrkey[0],usrkey[1],usrkey[2],usrkey[3]);

	out[1] = t2; out[3] = t4; out[5] = t6; out[7] = t0;
} 



void hight_init_nonce(NONCE_TYPE type,uint8_t* iv,uint8_t* counter, uint8_t* nonce )
{
	switch( type )
	{
	case NONCE_OR:
		{
			nonce[0] = iv[0] | counter[0];
			nonce[1] = iv[1] | counter[1];
			nonce[2] = iv[2] | counter[2];
			nonce[3] = iv[3] | counter[3];
			nonce[4] = iv[4] | counter[4];
			nonce[5] = iv[5] | counter[5];
			nonce[6] = iv[6] | counter[6];
			nonce[7] = iv[7] | counter[7];
		}
		break;
	case NONCE_AND:
		{
			nonce[0] = iv[0] & counter[0];
			nonce[1] = iv[1] & counter[1];
			nonce[2] = iv[2] & counter[2];
			nonce[3] = iv[3] & counter[3];
			nonce[4] = iv[4] & counter[4];
			nonce[5] = iv[5] & counter[5];
			nonce[6] = iv[6] & counter[6];
			nonce[7] = iv[7] & counter[7];
		}
		break;
	case NONCE_XOR:
		{
			nonce[0] = iv[0] ^ counter[0];
			nonce[1] = iv[1] ^ counter[1];
			nonce[2] = iv[2] ^ counter[2];
			nonce[3] = iv[3] ^ counter[3];
			nonce[4] = iv[4] ^ counter[4];
			nonce[5] = iv[5] ^ counter[5];
			nonce[6] = iv[6] ^ counter[6];
			nonce[7] = iv[7] ^ counter[7];
		}
		break;
	}
}


void hight_ctr_init(uint8_t* usrkey,uint8_t *iv,uint8_t* hightkey)
{
	uint8_t i, j;

	for(i=0 ; i < BLOCK_SIZE_HIGHT ; i++)
	{
		for(j=0 ; j < BLOCK_SIZE_HIGHT ; j++)
			hightkey[ 16*i + j ] = usrkey[(j-i)&7    ] + Delta[ 16*i + j ];

		for(j=0 ; j < BLOCK_SIZE_HIGHT ; j++)
			hightkey[ 16*i + j + 8 ] = usrkey[((j-i)&7)+8] + Delta[ 16*i + j + 8 ];
	}
}

int32_t hight_ctr_crypt(uint8_t* hightkey, uint8_t* usrkey, uint8_t* counter, uint32_t* in, int32_t isz, uint32_t* out, int32_t* osz)
{
	int32_t i = 0;

	while( i < isz )
	{
		hight_ctr_block( hightkey, usrkey, counter, (uint8_t *)out );
		BLOCK_XOR_8( out, in, out );

		hight_update_counter( counter, 1, (BLOCK_SIZE_HIGHT-1) );

		i += BLOCK_SIZE_HIGHT;
		in += BLOCK_SIZE_HIGHT_INT;
		out += BLOCK_SIZE_HIGHT_INT;
	}

	*osz = i;
	return isz - *osz;
}

int32_t hight_ctr_release(uint32_t* out,int32_t *osz, int32_t rsz )
{
  uint8_t* p = (uint8_t*)out;
	uint32_t r;
	int32_t i;
	
	r = -(rsz);

	for (i = r; i>0; i--) *(p-i) = 0;

	return *osz = r;
}


int32_t hight_ctr_encode(uint32_t* key, uint8_t* iv, uint8_t* counter, uint8_t* in, int32_t isz, uint8_t* out)
{
  uint32_t hightkey[128] = {0, };
  int32_t rsz = 0;
  int32_t bsz = 0;
  int32_t pad = 0;
  int32_t i= 0;

  hight_ctr_init(key, iv, hightkey);

  uint32_t osz;
  for ( i=0 ; i< isz-PROCESSING_BLOCK_SIZE_8 ; )
  {
    bsz = hight_ctr_crypt(hightkey, key, counter, (uint32_t*)(in+i), PROCESSING_BLOCK_SIZE_8, (uint32_t*)(out+i), &osz);
    i+= osz;
  }
  rsz = (isz%PROCESSING_BLOCK_SIZE_8)?(isz%PROCESSING_BLOCK_SIZE_8):PROCESSING_BLOCK_SIZE_8;

  bsz = hight_ctr_crypt(hightkey, key, counter, (uint32_t*)(in+i), rsz, (uint32_t*)(out+i), &osz);
  i+= osz;

  hight_ctr_release( (out+i), &pad, bsz);

  return (osz = i-pad);
}

int32_t hight_ctr_decode(uint32_t* key, uint8_t* iv, uint8_t* counter, uint8_t* in, int32_t isz, uint8_t* out)
{
  uint32_t hightkey[128] = {0, };
  int32_t rsz = 0;
  int32_t bsz = 0;
  int32_t pad = 0;
  int32_t i= 0;

  hight_ctr_init(key, iv, hightkey);

  int32_t osz;
  for ( i=0 ; i< isz-PROCESSING_BLOCK_SIZE_8 ; )
  {
    bsz = hight_ctr_crypt(hightkey, key, counter, (uint32_t*)(in+i), PROCESSING_BLOCK_SIZE_8, (uint32_t*)(out+i), &osz);
    i+= osz;
  }
  rsz = (isz%PROCESSING_BLOCK_SIZE_8)?(isz%PROCESSING_BLOCK_SIZE_8):PROCESSING_BLOCK_SIZE_8;

  bsz = hight_ctr_crypt(hightkey, key, counter, (uint32_t*)(in+i), rsz, (uint32_t*)(out+i), &osz);
  i+= osz;

  hight_ctr_release((out+i), &pad, bsz);

  return (osz = i-pad);
}

