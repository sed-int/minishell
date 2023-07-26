#include "libft.h"

void	ft_lstdel_mid(t_list *iter)
{
	t_list	*prev;
	t_list	*next;

	prev = NULL;
	next = NULL;
	if (iter->prev)
	{
		prev = iter->prev; 
		prev->next = next;
	}
	if (iter->next)
	{
		next = iter->next;
		next->prev = prev;
	}
	ft_lstdelone(iter, free);
}
