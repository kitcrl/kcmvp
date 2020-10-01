#include <ctrdrbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cSeed.h>

//------------------------------------------------
#define ALGO_SEED_OUTLEN_IN_BYTES				16
#define ALGO_ARIA128_OUTLEN_IN_BYTES			16
#define ALGO_ARIA192_OUTLEN_IN_BYTES			16
#define ALGO_ARIA256_OUTLEN_IN_BYTES			16

//------------------------------------------------
#define ALGO_SEED_KEYLEN_IN_BYTES				16
#define ALGO_ARIA128_KEYLEN_IN_BYTES			16
#define ALGO_ARIA192_KEYLEN_IN_BYTES			24
#define ALGO_ARIA256_KEYLEN_IN_BYTES			32

//------------------------------------------------
#define ALGO_SEED_SECURITY_STRENGTH_IN_BYTES	16
#define ALGO_ARIA128_SECURITY_STRENGTH_IN_BYTES	16
#define ALGO_ARIA192_SECURITY_STRENGTH_IN_BYTES	24
#define ALGO_ARIA256_SECURITY_STRENGTH_IN_BYTES	32

//------------------------------------------------
#define ALGO_SEED_SEEDLEN_IN_BYTES				(ALGO_SEED_OUTLEN_IN_BYTES + ALGO_SEED_KEYLEN_IN_BYTES)
#define ALGO_ARIA128_SEEDLEN_IN_BYTES			(ALGO_ARIA128_OUTLEN_IN_BYTES + ALGO_ARIA128_KEYLEN_IN_BYTES)
#define ALGO_ARIA192_SEEDLEN_IN_BYTES			(ALGO_ARIA192_OUTLEN_IN_BYTES + ALGO_ARIA192_KEYLEN_IN_BYTES)
#define ALGO_ARIA256_SEEDLEN_IN_BYTES			(ALGO_ARIA256_OUTLEN_IN_BYTES + ALGO_ARIA256_KEYLEN_IN_BYTES)


#define MAX_V_LEN_IN_BYTES						16
#define MAX_Key_LEN_IN_BYTES					32
#define MAX_SEEDLEN_IN_BYTES					ALGO_ARIA256_SEEDLEN_IN_BYTES

#define MIN_ENTROPY_INPUT_LEN_IN_BYTES			// Depends on SECURITY_STRENGTH of each algorithm

//------------------------------------------------
#define MAX_NUM_INPUT_OF_BYTES_PER_REQUEST		0x10000			// 2^19 bits

//------------------------------------------------
// The following values are too huge to apply on the current architectures,
// thus we do not consider the maximum length of either input or entropy.
#define MAX_ENTROPY_INPUT_LEN_IN_BYTES			0x100000000		// 2^35 bits
#define MAX_PERSONALIZED_STRING_LEN_IN_BYTES	0x100000000		// 2^35 bits
#define MAX_ADDITIONAL_INPUT_LEN_IN_BYTES		0x100000000		// 2^35 bits
#define NUM_OF_REQUESTS_BETWEEN_RESEEDS			0x1000000000000UL// 2^48 bits

#define STATE_INITIALIZED_FLAG					0xFE12DC34





#if defined XWIN32
#pragma pack(1)
#endif
typedef struct ctr_drbg
{
	uint8_t   algorithm; /*!< ALGO_SEED / ALGO_ARIA128 / ALGO_ARIA192 / ALGO_ARIA256 */
	uint8_t   V[MAX_V_LEN_IN_BYTES];
	int32_t   Vlen;
	uint8_t   Key[MAX_Key_LEN_IN_BYTES];
	int32_t   Keylen;
	int32_t   seedlen;
	int32_t   security_strength;		
	int32_t   initialized_flag;		  // If initialized_flag = STATE_INITIALIZED_FLAG, p is already initialized.
	uint8_t   der_ivation_function_flag; // 0x00 : non-df ,  0xFF : use df
	unsigned long long  reseed_counter;

	uint32_t seedkey[32];
}
#if defined PACKED
__attribute__((packed))
#endif
CTR_DRBG;
#if defined XWIN32
#pragma pack()
#endif



#define MAX_NUM_OF_BYTES_TO_RETURN 64
#define BLOCK_SIZE MAX_V_LEN_IN_BYTES
#define SIZE_INT	4

#define SEED_BLOCK_SIZE 16			/*!< SEED ???? ???*/
#define SEED_ENCRYPT	1			/*!< SEED ???? ???*/
#define SEED_DECRYPT	0			/*!< SEED ???? ???*/



#define octet_to_int(os) (((uint32_t)(os)[0] << 24) ^ ((uint32_t)(os)[1] << 16) ^ ((uint32_t)(os)[2] <<  8) ^ ((uint32_t)(os)[3]))
#define int_to_octet(os, i) { (os)[0] = (uint8_t)((i) >> 24); (os)[1] = (uint8_t)((i) >> 16); (os)[2] = (uint8_t)((i) >>  8); (os)[3] = (uint8_t)(i); }


static void __ctr_increase(uint8_t *counter)
{
	uint32_t c_byte;

  #if 1
	c_byte = octet_to_int(counter + 12);
	c_byte++;
	c_byte &= 0xFFFFFFFF;
	int_to_octet(counter + 12, c_byte);
	if (c_byte)
		return;

	c_byte = octet_to_int(counter +  8);
	c_byte++;	
	c_byte &= 0xFFFFFFFF;
	int_to_octet(counter +  8, c_byte);

	if (c_byte)
		return;

	c_byte = octet_to_int(counter +  4);
	c_byte++;
	c_byte &= 0xFFFFFFFF;
	int_to_octet(counter +  4, c_byte);

	if (c_byte)
		return;


	c_byte = octet_to_int(counter +  0);
	c_byte++;
	c_byte &= 0xFFFFFFFF;
	int_to_octet(counter +  0, c_byte);

  #endif
}

void __bcc(uint32_t* seedkey, int8_t algorithm,uint8_t* K,uint8_t* data, int32_t datalen,uint8_t* output_block, int32_t outlen)
{
  #if 1
	//ARIA_KEY ariakey;
	int32_t n = datalen/outlen;
	int32_t i,j,idx;
	uint8_t inputblock[MAX_V_LEN_IN_BYTES];
	memset(inputblock,0x00,MAX_V_LEN_IN_BYTES);
	memset(output_block,0x00,outlen);
	
	
	switch(algorithm){
		case ALGO_SEED:
			__seed_cbc_init(K, seedkey);

			for(j=1; j <= n; j++)
			{				
				for(i=0; i<outlen; i++)
				{
					inputblock[i] = output_block[i] ^ data[i];
				}
        __seed_cbc_encrypt((uint32_t*)inputblock, (uint32_t*)output_block, seedkey);
				data		 += SEED_BLOCK_SIZE;				
			}
			break;

    #if 0
		case ALGO_ARIA128:
			KISA_ARIA_encrypt_init(K,128,&ariakey);

			for(j=1; j <= n; j++)
			{
				for(i=0; i<outlen; i++)
				{
					inputblock[i] = output_block[i] ^ data[i];
				}
				KISA_ARIA_process_block(inputblock,output_block,&ariakey);				
				data		 += ARIA_BLOCK_SIZE;
			}
			break;
		case ALGO_ARIA192:
			KISA_ARIA_encrypt_init(K,192,&ariakey);

			for(j=1; j <= n; j++)
			{
				for(i=0; i<outlen; i++)
				{
					inputblock[i] = output_block[i] ^ data[i];
				}
				KISA_ARIA_process_block(inputblock,output_block,&ariakey);				
				data		 += ARIA_BLOCK_SIZE;
			}
			break;
		case ALGO_ARIA256:
			KISA_ARIA_encrypt_init(K,256,&ariakey);

			for(j=1; j <= n; j++)
			{
				for(i=0; i<outlen; i++)
				{
					inputblock[i] = output_block[i] ^ data[i];
				}
				KISA_ARIA_process_block(inputblock,output_block,&ariakey);				
				data		 += ARIA_BLOCK_SIZE;
			}
			break;
      #endif
	}

	//memset(&ariakey,0x00,sizeof(KISA_ARIA_KEY));
	memset(seedkey,0x00,sizeof(int32_t)*32);
	memset(inputblock,0x00,MAX_V_LEN_IN_BYTES);

  #endif
}


int32_t __blockcipher_df(uint32_t* seedkey, int8_t algorithm, uint8_t *input_string, int32_t input_str_len, uint8_t *output, int32_t outlen)
{

  #if 1
  int32_t retcode = 0;
  int32_t i = 0;
  int32_t L = input_str_len;
  int32_t N = outlen;
  uint8_t X [MAX_NUM_OF_BYTES_TO_RETURN];
  uint8_t K [ALGO_ARIA256_KEYLEN_IN_BYTES];	// Maximum length
  int32_t KLen;
  uint8_t IV[BLOCK_SIZE];
  uint8_t block[BLOCK_SIZE];
  int32_t j;
  uint8_t *S = 0;
  int32_t SLen = 0;
  uint8_t *temp = 0;
  uint8_t *_iv_s = 0;
  int32_t _iv_s_len = 0;
  int32_t templen = 0;
  uint8_t *ptr;
  void* hseed = 0;
  //KISA_ARIA_KEY ariakey;

  if(outlen > MAX_NUM_OF_BYTES_TO_RETURN)
  {
    goto FREE_AND_EXIT;
  }

  // form S = L||N||input_string||0x80	
  SLen = 8 + input_str_len + 1;
  if((SLen % SEED_BLOCK_SIZE) != 0)
  SLen += (SEED_BLOCK_SIZE - (SLen % SEED_BLOCK_SIZE));

  S = (uint8_t*)malloc(SLen);
  memset(S,0x00,SLen);
  int_to_octet(S, L);
  int_to_octet(S + SIZE_INT, N);
  memcpy(S + SIZE_INT + SIZE_INT, input_string, input_str_len);
  S[SIZE_INT+SIZE_INT+input_str_len] = 0x80;

  for(j=0; j<ALGO_ARIA256_KEYLEN_IN_BYTES; j++) K[j] = j;

  KLen = (algorithm == ALGO_SEED) ? ALGO_SEED_KEYLEN_IN_BYTES : (algorithm == ALGO_ARIA128) ? ALGO_ARIA128_KEYLEN_IN_BYTES : (algorithm == ALGO_ARIA192) ? ALGO_ARIA192_KEYLEN_IN_BYTES : ALGO_ARIA256_KEYLEN_IN_BYTES;

  templen = (KLen+outlen) + (BLOCK_SIZE - ((KLen+outlen) % BLOCK_SIZE));	
  temp = (uint8_t*)malloc(templen);	
  ptr = temp;
  _iv_s_len = SLen + BLOCK_SIZE;
  _iv_s = (uint8_t*)malloc(_iv_s_len);	
  i = 0;
  templen = 0;

  while(templen < KLen + outlen)
  {		
    int_to_octet(IV,i);
    memset(IV+SIZE_INT,0x00,BLOCK_SIZE-SIZE_INT);
    memcpy(_iv_s,IV,BLOCK_SIZE);
    memcpy(_iv_s + BLOCK_SIZE,S,SLen);

    __bcc(seedkey, algorithm,K,_iv_s,_iv_s_len,block,BLOCK_SIZE);
    memcpy(ptr,block,BLOCK_SIZE);
    ptr += BLOCK_SIZE;
    templen += BLOCK_SIZE;
    i++;
  }

  memcpy(K,temp,KLen);
  memcpy(X,temp+KLen,outlen);

  memset(temp,0x00,templen);
  free(temp);

  temp = (uint8_t*)malloc((outlen) + (BLOCK_SIZE - ((outlen) % BLOCK_SIZE)));
  ptr = temp;
  templen = 0;	

  switch(algorithm)
  {
  case ALGO_SEED:
		__seed_cbc_init(K, seedkey);
    while(templen < outlen)
    {
			__seed_cbc_encrypt((uint32_t*)X,(uint32_t*)X,seedkey);
      memcpy(ptr,X,BLOCK_SIZE);
      ptr += BLOCK_SIZE;
      templen += BLOCK_SIZE;					
    }
    break;
  #if 0
  case ALGO_SEED:
    KISA_SEED_init(K,&seedkey);
    while(templen < outlen)
    {
      KISA_SEED_encrypt_block(X,X,&seedkey);
      memcpy(ptr,X,BLOCK_SIZE);
      ptr += BLOCK_SIZE;
      templen += BLOCK_SIZE;					
    }
    break;
  case ALGO_ARIA128:
    KISA_ARIA_encrypt_init(K,ARIA128,&ariakey);			
    while(templen < outlen){
    KISA_ARIA_process_block(X,X,&ariakey);
    memcpy(ptr,X,BLOCK_SIZE);
    ptr += BLOCK_SIZE;
    templen += BLOCK_SIZE;
    }
    break;	
  case ALGO_ARIA192:
    KISA_ARIA_encrypt_init(K,ARIA192,&ariakey);			
    while(templen < outlen){
    KISA_ARIA_process_block(X,X,&ariakey);
    memcpy(ptr,X,BLOCK_SIZE);
    ptr += BLOCK_SIZE;
    templen += BLOCK_SIZE;
    }
    break;	
  case ALGO_ARIA256:
    KISA_ARIA_encrypt_init(K,ARIA256,&ariakey);			
    while(templen < outlen){
    KISA_ARIA_process_block(X,X,&ariakey);
    memcpy(ptr,X,BLOCK_SIZE);
    ptr += BLOCK_SIZE;
    templen += BLOCK_SIZE;
    }
    break;
  #endif
  }

  memcpy(output,temp,outlen);

  retcode = 1;
FREE_AND_EXIT:
  //memset(&ariakey,0x00,sizeof(ARIA_KEY));
  memset(&seedkey,0x00,sizeof(int32_t)*32);
  if(S != 0){
    memset(S,0x00,SLen);
    free(S);
  }
  if(temp != 0){
    memset(temp,0x00,templen);
    free(temp);
  }
  if(_iv_s != 0){
    memset(_iv_s,0x00,_iv_s_len);
    free(_iv_s);
  }
  memset(X,0x00,MAX_NUM_OF_BYTES_TO_RETURN);
  memset(K,0x00,ALGO_ARIA256_KEYLEN_IN_BYTES);
  memset(IV,0x00,BLOCK_SIZE);
  memset(block,0x00,BLOCK_SIZE);	
  return retcode;
  #endif

  return 0;
}

int32_t __ctrdrbg_update (CTR_DRBG* state, uint8_t* provided_data)
{
  #if 1
  uint8_t temp[MAX_SEEDLEN_IN_BYTES];
  int32_t templen = 0;
  uint8_t* ptr;
  int32_t i;
  int32_t ptrindex = 0;
  //KISA_ARIA_KEY ariakey;

  if( (provided_data==0) || (state->seedlen<=0) ) return 0;

  ptr = temp;

  switch (state->algorithm)
  {
    case ALGO_SEED:
			__seed_cbc_init(state->Key,&state->seedkey);
      while(templen < state->seedlen)
      {
        __ctr_increase(state->V);	
				__seed_cbc_encrypt((uint32_t*)state->V,(uint32_t*)ptr,&state->seedkey);
        ptr += SEED_BLOCK_SIZE;				
        templen += SEED_BLOCK_SIZE;
      }
      memset(&state->seedkey,0x00,sizeof(int32_t)*32);
      break;

    #if 0
    case ALGO_ARIA128:
      KISA_ARIA_encrypt_init(state->Key,ARIA128,&ariakey);
      while(templen < state->seedlen)
      {
      __ctr_increase(state->V);								
      KISA_ARIA_process_block(state->V,ptr,&ariakey);
      ptr += ARIA_BLOCK_SIZE;				
      templen += ARIA_BLOCK_SIZE;
      }
      memset(&ariakey,0x00,sizeof(KISA_ARIA_KEY));
      break;	
    case ALGO_ARIA192:
      KISA_ARIA_encrypt_init(state->Key,ARIA192,&ariakey);
      while(templen < state->seedlen)
      {
      __ctr_increase(state->V);								
      KISA_ARIA_process_block(state->V,ptr,&ariakey);
      ptr += ARIA_BLOCK_SIZE;				
      templen += ARIA_BLOCK_SIZE;
      }
      memset(&ariakey,0x00,sizeof(KISA_ARIA_KEY));
      break;	
    case ALGO_ARIA256:
      KISA_ARIA_encrypt_init(state->Key,ARIA256,&ariakey);
      while(templen < state->seedlen)
      {
      __ctr_increase(state->V);								
      KISA_ARIA_process_block(state->V,ptr,&ariakey);
      ptr += ARIA_BLOCK_SIZE;				
      templen += ARIA_BLOCK_SIZE;
      }
      memset(&ariakey,0x00,sizeof(KISA_ARIA_KEY));
      break;
    #endif
  }

  for(i = 0; i<state->seedlen; i++) temp[i] ^= provided_data[i];

  memcpy(state->Key,temp,state->Keylen);
  ptr = temp;
  memcpy(state->V,ptr + state->seedlen - (state->Vlen), state->Vlen);

  memset(temp,0x00,state->seedlen);

  #endif
  return 1;
}



int32_t ctrdrbg_init(void** hdl, uint8_t algorithm, uint8_t* a, int32_t asz, uint8_t* b, int32_t bsz, uint8_t* c, int32_t csz, uint8_t flg)
{
  uint8_t  seed_material[MAX_SEEDLEN_IN_BYTES];
  uint8_t* seed_material_in = 0;
  uint8_t* ptr = 0;
  int32_t  seed_material_len = 0;
  int32_t  e = 0;
  CTR_DRBG*      p;

  if(a == 0) return e;

  *hdl = (CTR_DRBG*)calloc(1, sizeof(CTR_DRBG));
  p = (CTR_DRBG*)(*hdl);

  if(flg == USE_DERIVATION_FUNCTION) p->der_ivation_function_flag = USE_DERIVATION_FUNCTION;
  else p->der_ivation_function_flag = NON_DERIVATION_FUNCTION;

  switch(algorithm)
  {

  case ALGO_SEED:
    if(flg == USE_DERIVATION_FUNCTION)
    {
      if(asz < ALGO_SEED_SECURITY_STRENGTH_IN_BYTES ) return 0;
    }
    else
    {
      if(asz < ALGO_SEED_SEEDLEN_IN_BYTES ) return 0;
    }

    if( (b!=0) && (bsz < (ALGO_SEED_SECURITY_STRENGTH_IN_BYTES/2)) ) return 0;

    p->seedlen = ALGO_SEED_SEEDLEN_IN_BYTES;
    p->Keylen = ALGO_SEED_KEYLEN_IN_BYTES;
    p->Vlen = ALGO_SEED_OUTLEN_IN_BYTES;			
    break;

  //--------------------------------------------------------------
  case ALGO_ARIA128:
    if(flg == USE_DERIVATION_FUNCTION)
    {
      if(asz < ALGO_ARIA128_SECURITY_STRENGTH_IN_BYTES ) return 0;
    }
    else
    {
      if(asz < ALGO_ARIA128_SEEDLEN_IN_BYTES ) return 0;
    }

    if( (b!=0) && (bsz < (ALGO_ARIA128_SECURITY_STRENGTH_IN_BYTES/2)) ) return 0;

    p->seedlen = ALGO_ARIA128_SEEDLEN_IN_BYTES;
    p->Keylen = ALGO_ARIA128_KEYLEN_IN_BYTES;
    p->Vlen = ALGO_ARIA128_OUTLEN_IN_BYTES;
    break;

  //--------------------------------------------------------------
  case ALGO_ARIA192:	
    if(flg == USE_DERIVATION_FUNCTION)
    {
      if(asz < ALGO_ARIA192_SECURITY_STRENGTH_IN_BYTES ) return 0;
    }
    else
    {
      if(asz < ALGO_ARIA192_SEEDLEN_IN_BYTES ) return 0;
    }

    if( (b!=0) && (bsz < (ALGO_ARIA192_SECURITY_STRENGTH_IN_BYTES/2)) ) return 0;

    p->seedlen = ALGO_ARIA192_SEEDLEN_IN_BYTES;
    p->Keylen = ALGO_ARIA192_KEYLEN_IN_BYTES;
    p->Vlen = ALGO_ARIA192_OUTLEN_IN_BYTES;
    break;

  //--------------------------------------------------------------
  case ALGO_ARIA256:	
    if(flg == USE_DERIVATION_FUNCTION)
    {
      if(asz < ALGO_ARIA256_SECURITY_STRENGTH_IN_BYTES ) return 0;
    }
    else
    {
      if(asz < ALGO_ARIA256_SEEDLEN_IN_BYTES ) return 0;
    }

    if( (b!=0) && (bsz < (ALGO_ARIA256_SECURITY_STRENGTH_IN_BYTES/2)) ) return 0;

    p->seedlen = ALGO_ARIA256_SEEDLEN_IN_BYTES;
    p->Keylen = ALGO_ARIA256_KEYLEN_IN_BYTES;
    p->Vlen = ALGO_ARIA256_OUTLEN_IN_BYTES;
    break;

  default:
    return 0; // No Such Algorithm
  }

	p->algorithm = algorithm;

	if(p->der_ivation_function_flag == USE_DERIVATION_FUNCTION)
	{
		memset(seed_material,0x00,MAX_SEEDLEN_IN_BYTES);
		seed_material_len = asz;
		if( (b!=0) && (bsz>0) ) seed_material_len += (bsz);
		if( (c!=0) && (csz>0) ) seed_material_len += (csz);

		ptr = seed_material_in = (uint8_t*) calloc(1, seed_material_len);
	
		memcpy(ptr, a, asz);
		if( (b!=0) && (bsz>0) )
		{
			ptr += asz;
			memcpy(ptr, b, bsz);			
		}
		
		if( (c!=0) && (csz>0) )
		{
			ptr += bsz;
			memcpy(ptr, c, csz);		
		}

		if(!__blockcipher_df(p->seedkey, algorithm,seed_material_in,seed_material_len,seed_material,p->seedlen))
		{
			goto FREE_AND_EXIT;
		}
	}
	else
	{
		int32_t loop = csz <= asz ? csz : bsz;
		int32_t i;

		if(loop > MAX_SEEDLEN_IN_BYTES) loop = MAX_SEEDLEN_IN_BYTES;
		// seed_material = entropy_input xor personalization_string
		memset(seed_material,0x00,MAX_SEEDLEN_IN_BYTES);
		if( (c==0) || (csz==0) )
			for(i = 0; i < asz; i++)
				seed_material[i] = a[i];
		else
			for(i = 0; i < loop; i++)
				seed_material[i] = a[i] ^ c[i];
	}


	memset(p->Key, 0x00, MAX_Key_LEN_IN_BYTES);
	memset(p->V, 0x00, MAX_V_LEN_IN_BYTES);

	if(!__ctrdrbg_update(p, seed_material))
	{
		goto FREE_AND_EXIT;
	}

	p->reseed_counter = 1;

	e = 1;
	p->initialized_flag = STATE_INITIALIZED_FLAG;

FREE_AND_EXIT:	
	if(seed_material_in){
		memset(seed_material_in,0x00,seed_material_len);
		free(seed_material_in);
	}
	memset(seed_material,0x00,MAX_SEEDLEN_IN_BYTES);
	return e;

}

int32_t ctrdrbg_release(void** hdl)
{
  free(*hdl);
  *hdl = 0;

  return 0;
}


int32_t ctrdrbg_generate(void* hdl, uint8_t* output, int32_t requested_num_of_bits, uint8_t* addtional_input, int32_t addlen)
{
  CTR_DRBG* state = (CTR_DRBG*)hdl;
  #if 1
	uint8_t addtional_input_for_seed[MAX_SEEDLEN_IN_BYTES];
	int32_t request_num_of_bytes;
	
	int32_t retcode = 0;
	uint8_t* temp = NULL;
	uint8_t* ptr = NULL;
	int32_t templen = 0;
	
	if(addlen > state->seedlen)
	{
		addlen = state->seedlen;
	}

	if(requested_num_of_bits <= 0)
	{
		return 0; // No length to generate
	}
	else
	{
		request_num_of_bytes = requested_num_of_bits / 8 + ((requested_num_of_bits % 8) != 0 ? 1 : 0);
	}

	if(state->reseed_counter > NUM_OF_REQUESTS_BETWEEN_RESEEDS)
	{
		return 0; // Reseed Required.
	}
	

	if(addtional_input != NULL && addlen > 0)
	{	
		if(state->der_ivation_function_flag == USE_DERIVATION_FUNCTION)
		{
			if(!__blockcipher_df(state->seedkey, state->algorithm,addtional_input,addlen,addtional_input_for_seed,state->seedlen))
			{
				memset(addtional_input_for_seed,0x00,MAX_SEEDLEN_IN_BYTES);
				return 0;
			}

			if(!__ctrdrbg_update(hdl, addtional_input_for_seed))
			{
				memset(addtional_input_for_seed,0x00,MAX_SEEDLEN_IN_BYTES);
				return 0;
			}
		}
		else
		{
			memset(addtional_input_for_seed,0x00,MAX_SEEDLEN_IN_BYTES);
			memcpy(addtional_input_for_seed, addtional_input, addlen);

			if(!__ctrdrbg_update(hdl, addtional_input_for_seed))
			{
				memset(addtional_input_for_seed,0x00,MAX_SEEDLEN_IN_BYTES);
				return 0;
			}
		}
	}else
	{
		memset(addtional_input_for_seed,0x00,MAX_SEEDLEN_IN_BYTES);
	}

	templen = request_num_of_bytes + (MAX_V_LEN_IN_BYTES - (request_num_of_bytes % MAX_V_LEN_IN_BYTES));
	temp = (uint8_t*)malloc(templen);
	ptr = temp;
	templen = 0;


	switch(state->algorithm)
	{
	case ALGO_SEED:
		__seed_cbc_init(state->Key, state->seedkey);
		while(templen < request_num_of_bytes)
		{
			__ctr_increase(state->V);
			__seed_cbc_encrypt((uint32_t*)state->V,(uint32_t*)ptr, state->seedkey);
			ptr += ALGO_SEED_OUTLEN_IN_BYTES;
			templen += ALGO_SEED_OUTLEN_IN_BYTES;
		}
    memset(&state->seedkey,0x00,sizeof(int32_t)*32);
		break;
  #if 0
	case ALGO_ARIA128:
		KISA_ARIA_encrypt_init(state->Key, 128 ,&aria_key);
		while(templen < request_num_of_bytes)
		{
			__ctr_increase(state->V);
			KISA_ARIA_process_block(state->V,ptr,&aria_key);
			ptr += ALGO_ARIA128_OUTLEN_IN_BYTES;
			templen += ALGO_ARIA128_OUTLEN_IN_BYTES;
		}
		memset(&aria_key,0x00,sizeof(KISA_ARIA_KEY));
		break;
	case ALGO_ARIA192:
		KISA_ARIA_encrypt_init(state->Key, 192 ,&aria_key);
		while(templen < request_num_of_bytes)
		{
			__ctr_increase(state->V);
			KISA_ARIA_process_block(state->V,ptr,&aria_key);
			ptr += ALGO_ARIA192_OUTLEN_IN_BYTES;
			templen += ALGO_ARIA192_OUTLEN_IN_BYTES;
		}
		memset(&aria_key,0x00,sizeof(KISA_ARIA_KEY));
		break;
	case ALGO_ARIA256:
		KISA_ARIA_encrypt_init(state->Key, 256 ,&aria_key);
		while(templen < request_num_of_bytes)
		{
			__ctr_increase(state->V);
			KISA_ARIA_process_block(state->V,ptr,&aria_key);
			ptr += ALGO_ARIA256_OUTLEN_IN_BYTES;
			templen += ALGO_ARIA256_OUTLEN_IN_BYTES;
		}
		memset(&aria_key,0x00,sizeof(KISA_ARIA_KEY));
		break;
  #endif
	}
	
	memcpy(output,temp,request_num_of_bytes);
	if(requested_num_of_bits % 8 != 0)
		output[request_num_of_bytes-1] = temp[request_num_of_bytes-1] & (0x000000FF&(0xFF << (8-(requested_num_of_bits%8))));

	if(!__ctrdrbg_update(state,addtional_input_for_seed))
	{
		goto FREE_AND_EXIT;
	}

	(state->reseed_counter)++;

	retcode = 1;
FREE_AND_EXIT:
	memset(temp,0x00,templen);
	if(temp) free(temp);
	memset(addtional_input_for_seed,0x00,MAX_SEEDLEN_IN_BYTES);	
	return retcode;

  #endif
  return 0;
}



int32_t ctrdrbg_reseed(void* hdl, uint8_t* entropy_input, int32_t entropylen, uint8_t* additional_input, int32_t addlen)
{
  CTR_DRBG* state = (CTR_DRBG*)hdl;

  #if 1
	uint8_t	seed_material[MAX_SEEDLEN_IN_BYTES];
	uint8_t*	seed_material_in = NULL;
	uint8_t*	ptr			 = NULL;
	int32_t				seed_material_len = 0;
	int32_t				retcode = 0;
		
	if(entropy_input == NULL)
	{
		return 0;
	}

	if(addlen > state->seedlen)
	{
		addlen = state->seedlen;
	}

	if(state->initialized_flag != STATE_INITIALIZED_FLAG)
	{
		return 0; // KISA_CTR_DRBG_Instantiate(...) required
	}

	switch(state->algorithm)
	{
		
		//--------------------------------------------------------------
		case ALGO_SEED:
			if(entropylen < ALGO_SEED_SECURITY_STRENGTH_IN_BYTES)
				return 0;			
			break;

		//--------------------------------------------------------------
		case ALGO_ARIA128:
			if(entropylen < ALGO_ARIA128_SECURITY_STRENGTH_IN_BYTES)
				return 0;
			break;
		
		//--------------------------------------------------------------
		case ALGO_ARIA192:	
			if(entropylen < ALGO_ARIA192_SECURITY_STRENGTH_IN_BYTES)
				return 0;
			break;

		//--------------------------------------------------------------
		case ALGO_ARIA256:	
			if(entropylen < ALGO_ARIA256_SECURITY_STRENGTH_IN_BYTES)
				return 0;
			break;

		default:
			return 0; // No Such Algorithm
	}

	if(state->der_ivation_function_flag == USE_DERIVATION_FUNCTION)
	{
		memset(seed_material,0x00,MAX_SEEDLEN_IN_BYTES);
		seed_material_len = entropylen;
		if(addlen > 0)
			seed_material_len += (addlen);
		ptr = seed_material_in = (uint8_t*) malloc(seed_material_len);

		memcpy(ptr, entropy_input, entropylen);
		if(addlen > 0)
		{
			ptr += entropylen;
			memcpy(ptr, additional_input, addlen);		
		}

		if(!__blockcipher_df(state->seedkey, state->algorithm,seed_material_in,seed_material_len,seed_material,state->seedlen))
		{
			goto FREE_AND_EXIT;
		}
	}
	else
	{
		int32_t loop = addlen <= entropylen ? addlen : entropylen;
		int32_t i;

		// seed_material = entropy_input xor additional input
		memset(seed_material, 0x00, MAX_SEEDLEN_IN_BYTES);

		if(additional_input == NULL || addlen == 0) {
			for(i = 0; i < entropylen; i++) {
				seed_material[i] = entropy_input[i];
			}
		}else{
			for(i = 0; i < loop; i++) {
				seed_material[i] = entropy_input[i] ^ additional_input[i];
			}
		}
	}
	
	if(!__ctrdrbg_update(state,seed_material))
	{
		goto FREE_AND_EXIT;
	}

	state->reseed_counter = 1;
	
	retcode = 1;

FREE_AND_EXIT:
	memset(seed_material_in,0x00,seed_material_len);
	if(seed_material_in) free(seed_material_in);
	memset(seed_material,0x00,MAX_SEEDLEN_IN_BYTES);
	return retcode;
  #endif

  return 0;
}


