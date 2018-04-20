#include "libft.h"

unsigned			ft_endian_swap(unsigned int *ptr)
{
	unsigned int        tmp;
	tmp = *ptr;
	*ptr = ((tmp>>24) & 0xff) | ((tmp<<8) & 0xff0000) | ((tmp>>8) & 0xff00)
	| ((tmp<<24) & 0xff000000);
	return (*ptr);
}

unsigned short		ft_short_endian_swap(unsigned short *ptr)
{
	unsigned short      tmp;
	tmp = *ptr;
	*ptr = (tmp>>8) | (tmp<<8);
	return (*ptr);
}
