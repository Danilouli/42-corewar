#include "libft.h"

void ft_endian_swap(unsigned int *ptr)
{
    unsigned int        tmp;
    tmp = *ptr;
    *ptr = ((tmp>>24) & 0xff) | ((tmp<<8) & 0xff0000) | ((tmp>>8) & 0xff00)
    | ((tmp<<24) & 0xff000000);
}
