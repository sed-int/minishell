#include "libft.h"
#include <stdio.h>

void	ft_lstadd_mid(t_list *target_node, t_list **new_lst)
{
	t_list	*tmp;
	t_list	*target_next;
	t_list	*cpy_lst;
	t_list	*last;


	if (!*new_lst)
		return ;
	tmp = *new_lst;
	cpy_lst = NULL;
	while (tmp)
	{
		printf("111111\n");
		ft_lstadd_back(&cpy_lst, ft_lstnew(ft_strdup(tmp->content))); //will modify
		tmp = tmp->next;
	}
		printf("222222\n");
	target_next = target_node->next;
		printf("3\n");
	target_node->next = cpy_lst;
		printf("4\n");
	cpy_lst->prev = target_node;
		printf("5\n");
	last = ft_lstlast(cpy_lst);
		printf("6\n");
	last->next = target_next;
		printf("7\n");
	if (target_next)
		target_next->prev = last;
		printf("8\n");
	// ft_lstclear(new_lst, free);
}
