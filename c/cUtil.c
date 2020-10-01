#include "cUtil.h"

const int8_t PROC_INFO[][32] =
{
	"/proc/uptime",
	"/proc/meminfo",
	"/proc/vmstat",
};


int32_t system_noise(int8_t* fname, int32_t idx)
{
	FILE* fp = 0;
	char buf[4096] = {0};
	int32_t i=0;
	int32_t _idx = 0;
	int32_t s = 0;
	int32_t sz = 0;

	fp = fopen(fname, "r");
	if ( fp == 0 ) return -1;

	sz = fread(buf, 1, 4096, fp);
	fclose(fp);

	if ( sz <= 0 ) return -1;


	for ( i=0, s=0 ; i<sz ; i++, _idx++ )
	{
			s = i;
			for ( ; (buf[i]!='\n') ; i++ );
			if ( idx == _idx )
			{
				buf[i] = 0;
				break;
			}
	}

	for ( i=s, _idx=-1; ; i++)
	{
		if ( (_idx==-1) && ( (buf[i]>=0x30) && (buf[i]<=0x39) ) )
		{
			s=i;
			break;
		}
	}

	for ( ; (buf[i]>=0x30) && (buf[i]<=0x39) ; i++ ); //FF
	buf[i] = 0;

	return atoi(&buf[s])&0xFF;
}


int32_t mine_noise()
{
#ifdef __linux__
	int32_t i = 0;
	int32_t m = 0;
	int32_t v = 0;
	struct timeval tv;
	gettimeofday(&tv, 0);

	for ( ; ; )
	{
		if ( (m = system_noise(PROC_INFO[1], (system_noise(PROC_INFO[0], 0)*getpid())&0xF)) > 0 ) break;
	}

	for ( ; ; )
	{
		if ( (m = system_noise(PROC_INFO[2], (system_noise(PROC_INFO[0], 0)*m)&0x1F)) > 0 ) break;
	}


	return ((tv.tv_usec*m)&0xFF);
#else
	return 0;
#endif;
}




int32_t get_noises(uint8_t* out, int32_t sz)
{
	int32_t i=0;

	for ( i=0 ; i<sz; i++ )
	{
		*(out+i) = mine_noise();
	}
	return i;
}
