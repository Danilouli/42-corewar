#include "libft.h"

t_list	*ft_lstfilter(t_list *list, void *ref, int (*f)(t_list *elem, void *ref),
		void (*del)(void *, size_t))
{
	t_list	*result;
	t_list	*next;

	result = NULL;
	while (list)
	{
		next = list->next;
		if (f(list, ref))
		{
			list->next = NULL;
			ft_lstappend(&result, list);
		}
		else
		{
			del(list->content, list->content_size);
			free(list);
		}
		list = next;
	}
	return (result);
}
