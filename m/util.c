#include <util.h>

void display(int8_t* title, int8_t* b, int32_t sz)
{
  int32_t i = 0;

  CRLF;
  PREFIX;
  printf("**************************************************");
  CRLF;
  PREFIX;
  printf("* %-46s *", title);
  CRLF;
  PREFIX;
  printf("**************************************************");
  CRLF;
  PREFIX;
  for ( i=0 ; i<sz ; i++ )
  {
    if ( i &&  (i%8)==0 ) printf("  ");
    if ( i &&  (i%16)==0 )
    {
      CRLF;
      PREFIX;
    }
    printf(" %02X", (uint8_t)*(b+i));
  }
  CRLF;
  PREFIX;
  printf("--------------------------------------------------");
  CRLF;
  CRLF;
}
