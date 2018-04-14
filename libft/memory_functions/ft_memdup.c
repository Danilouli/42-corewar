#include "libft.h"

void	*ft_memdup(void *src, size_t len)
{
	unsigned char	*res;

	if (!(res = (unsigned char*)malloc(sizeof(unsigned char) * len)))
		return (NULL);
	ft_memcpy(res, src, len);
	return (res);
}
