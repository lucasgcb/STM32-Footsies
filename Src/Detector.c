#include "Detector.h"
uint8_t nivelDeColisao = 0;
void detectarColisao(void)
{
		#ifdef DEBUG_COL
		if (nivelDeColisao==0)
			print_seguro(0,0,"NOCOL");
		else
			if (nivelDeColisao==1)
				print_seguro(0,0,"ATKCOL");
			else
				if (nivelDeColisao==2)
					print_seguro(0,0,"BIGCOL");
		#endif
		int8_t	val = (posP2.x1) - (posP1.x1+32);
		if ( val >= 0 )
		{
			nivelDeColisao = 0;
		}
		else
		{
			if ( val < 0 && val > -6 )
			{
					nivelDeColisao = 1;
			}
				else
				{
					nivelDeColisao = 2;
				}
		}
}
