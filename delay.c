#include "delay.h"

void Delay10us(unsigned char x)		//@33.1776MHz
{
	while(x)
	{
		unsigned char i;

		i = 80;
		while (--i);
	}
}
