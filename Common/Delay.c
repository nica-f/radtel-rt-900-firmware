#include "includes.h"

void DelayUs(U16 n)// 1US
{
    U16 t = n * 10;
    while(t--){
	
    }
}
void DelayMs(U16 n)
{
   U16 i=0;
   for (i=0;i<n;i++)
	{
		DelayUs( 1000 );
	}
}
