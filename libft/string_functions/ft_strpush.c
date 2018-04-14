#include "libft.h"

void ft_strpush(char *str, char c)
{
	if (!str)
		return ;
	while (*str)
		str++;
	*str++ = c;
	*str = '\0';
}
