#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <_xcrypt.h>
#include <pbkdf.h>

#include <cUtil.h>
#include <cSeed.h>
#include <cHight.h>
#include <util.h>

int8_t key[512] = {0, };
int32_t key_sz;
int8_t rkey[512] = {0, };
int32_t rkey_sz;
int8_t  plain_text[8192]= {0, };
int32_t plain_text_sz;
int8_t  cipher_text[8192]= {0, };
int32_t cipher_text_sz;
int8_t  replain_text[8192]= {0, };
int32_t replain_text_sz;

#define PADDING_SIZE(a,b)   ((a%b)==0?a:a+(b-(a%b)))



int32_t sfk_base64_encode(int8_t* text, int32_t sz, int8_t* out)
{
  return 0;
}

int32_t sfk_base64_decode(int8_t* text, int32_t sz, int8_t* out)
{
  return 0;
}

void key_gen()
{
	uint8_t temp[1024] = { 0, };
	int32_t sz;
	int32_t i = 0;
	for ( i=0 ; i<10 ; i++ )
	{
		key[i] = 0x30 + i;
	}
	for ( ; i<16 ; i++ )
	{
		key[i] = 0x41 - 10 + i;
	}
	//key_sz = sfk_base64_decode(SEED_ECB_KEY, strlen(SEED_ECB_KEY), key);

	
}

int32_t init_plain_text()
{
	uint8_t temp[1024] = { 0, };
	int32_t sz = 0;

	int32_t i = 0;
	int32_t j = 0;

	for ( j=0 ; j<3; j++ )
	{
		for ( i=0 ; i<36 ; i++ )
		{
			if ( i<10 ) plain_text[i+j*36] = 0x30+i;
			else plain_text[i+j*36] = 0x41-10+i;
		}
		sz = i+j*36;
	}
	sz = PADDING_SIZE(72, 8);
	return sz;
}

int32_t* seed_ecb_cipher(int8_t* b, int32_t sz, int32_t code, void* o)
{
	printf(" code ---> %d, sz : %d \r\n", code, sz);
	//display((int8_t*)o, b, sz);
	return 0;
}


void seed_ecb_check()
{
	uint8_t temp[1024] = { 0, };
	int32_t sz;
	int32_t ecode = 0;

	plain_text_sz = 16;

	#if 0
	display("SEED KEY", key, 16);
	display("SEED ECB PLAIN TEXT", plain_text, plain_text_sz);
	plain_text[plain_text_sz] = 0;

	ecode = sfk_seed_ecb_encode(0, plain_text, plain_text_sz, cipher_text, 1024);
	sfk_print_status(ecode);



	cipher_text_sz = sfk_seed_ecb_encode(key, plain_text, plain_text_sz, cipher_text, 1024);
	display("SEED ECB CIPHER TEXT", cipher_text, cipher_text_sz);
//	sz = sfk_base64_encode(cipher_text, cipher_text_sz, temp);
//	display("CIPHER 64", temp, sz);


//	cipher_text_sz = sfk_seed_ecb_encrypt(key, plain_text, plain_text_sz, seed_ecb_cipher, "cipher text");

	//display("TEST_CIPHER_64", TEST_CIPHER_64, strlen(TEST_CIPHER_64));
	replain_text_sz = sfk_seed_ecb_decode(key, cipher_text, cipher_text_sz, replain_text, 1024);
	display("SEED ECB PLAIN TEXT", replain_text, replain_text_sz);
	//sz = sfk_base64_encode(replain_text, replain_text_sz, temp);
	//display("PLAIN 64", temp, sz);

	//replain_text_sz = sfk_seed_ecb_decrypt(key, cipher_text, cipher_text_sz, seed_ecb_cipher, "plain text");
	//display("TEST_PLAIN_64", TEST_PLAIN_64, strlen(TEST_PLAIN_64));
	#endif
}

size_t cp(size_t s, size_t p) {
	if (s % p != 0)
		return s + (p - (s % p));
	else {
		return s + p;
	}
}



void seed_cbc_check()
{
	uint8_t ivc[16];
	int32_t r;
	int i = 0;
	int e = 0;
	char* eb;
	char* db;
	for ( i=0 ; i<16 ; i++ )
	{
		ivc[i] = 'A';
	}

	printf("plain_text_sz ---> %d \r\n", plain_text_sz);

	eb = (char*)calloc(1, sizeof(char)*plain_text_sz);

	display("seed_cbc_encode ivc", ivc, 16);
	display("seed_cbc_encode plain_text", plain_text, plain_text_sz);

	e = seed_cbc_encode(key, (uint32_t *)ivc, plain_text, plain_text_sz, eb);

	display("seed_cbc_encode", eb, e);



	for ( i=0 ; i<16 ; i++ )
	{
		ivc[i] = 'A';
	}

	printf(" e :%d, plain_text_sz :%d \r\n", e, plain_text_sz);

	// Decrypt
	db = (char*)calloc(1, sizeof(char)*e);

	printf("-----\r\n");
	seed_cbc_decode(key, (uint32_t *)ivc, eb, e, db);

	display("seed_cbc_decode", db, plain_text_sz);



	printf("-----------------\r\n");
	free(db);
	printf("free(db) \r\n");
	db = 0;
	free(eb);
	printf("free(eb) \r\n");
	eb = 0;


}


void hight_ecb_check()
{
	uint8_t ivc[16];
	int32_t r;
	int i = 0;
	int e = 0;
	char* eb;
	char* db;

	printf("plain_text_sz ---> %d \r\n", plain_text_sz);

	eb = (char*)calloc(1, sizeof(char)*plain_text_sz);

	display("hight_ecb_encode ivc", ivc, 16);
	display("hight_ecb_encode plain_text", plain_text, plain_text_sz);

	e = hight_ecb_encode(key, plain_text, plain_text_sz, eb);

	display("hight_ecb_encode", eb, e);


	printf(" e :%d, plain_text_sz :%d \r\n", e, plain_text_sz);

	// Decrypt
	db = (char*)calloc(1, sizeof(char)*e);

	printf("-----\r\n");
	hight_ecb_decode(key, eb, e, db);

	display("hight_ecb_decode", db, plain_text_sz);



	printf("-----------------\r\n");
	free(db);
	printf("free(db) \r\n");
	db = 0;
	free(eb);
	printf("free(eb) \r\n");
	eb = 0;


}

void hight_cbc_check()
{
	uint8_t ivc[16];
	int32_t r;
	int i = 0;
	int e = 0;
	char* eb;
	char* db;
	for ( i=0 ; i<16 ; i++ )
	{
		ivc[i] = 'A';
	}

	printf("plain_text_sz ---> %d \r\n", plain_text_sz);

	eb = (char*)calloc(1, sizeof(char)*plain_text_sz);

	display("hight_cbc_encode ivc", ivc, 16);
	display("hight_cbc_encode plain_text", plain_text, plain_text_sz);

	e = hight_cbc_encode(key, (uint32_t *)ivc, plain_text, plain_text_sz, eb);

	display("hight_cbc_encode", eb, e);



	for ( i=0 ; i<16 ; i++ )
	{
		ivc[i] = 'A';
	}

	printf(" e :%d, plain_text_sz :%d \r\n", e, plain_text_sz);

	// Decrypt
	db = (char*)calloc(1, sizeof(char)*(e));

	printf("-----\r\n");
	hight_cbc_decode(key, (uint32_t *)ivc, eb, e, db);

	display("hight_cbc_decode", db, plain_text_sz);



	printf("-----------------\r\n");
	free(db);
	printf("free(db) \r\n");
	db = 0;
	free(eb);
	printf("free(eb) \r\n");
	eb = 0;


}




void sha256_hash_check()
{
	int i = 0;
	char key[32];
	char md5[32];

	for ( i=0; i<32; i++ )
	{
		key[i] = i%0x10;
	}

	display("key", key, 32);
	//sfk_sha256_hash(key, 32, md5, 32);
	display("md5", md5, 32);
}


void check()
{
	FILE* fp;
	char buf[4096] = {0};
	int32_t i=0;
	int32_t s = 0;
	int32_t sz = 0;

	fp = fopen("/proc/meminfo", "r");
	sz = fread(buf, 1, 4096, fp);
	fclose(fp);


	fprintf(stderr, "%s\r\n", buf);


	fprintf(stderr, "%d\r\n", sz);


	for ( i=0 ; i<sz ; i++ )
	{
		if ( strncmp("PageTables:", &buf[i], strlen("PageTables:")) == 0 )
		{
			s = i;
			for ( ; buf[i]!='\n' ; i++ );
			buf[i] = 0;
			break;
		}
	}

	fprintf(stderr, "[%s]\r\n", &buf[s]);

}




void main()
{
	int i = 0;
	char rN[1024] = {0, };
	char* sample = "Hello World Hello World";
	int sz = 48;
	char result[1024] = {0, };
	int e = 0;



	get_noises(rN, 1024);


	display("rN", rN, 1024);

	return 0;


	key_gen();
	plain_text_sz = init_plain_text();


	//hight_ecb_check();
	hight_cbc_check();

	//seed_cbc_check();
	//seed_ecb_check();



	return 0;

	printf(	"________________________________________"
					"________________________________________\r\n");

	display("Random Number 65", rN, 65);



	HMAC_SHA256(rN, 65, sample, sz, result);
	display("HMAC_SHA256", result, strlen(result));

	printf(	"________________________________________"
					"________________________________________\r\n");



	display("result", result, 32);

	return 0;




	//self_check();

}
