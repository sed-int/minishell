#include "minishell.h"

char **free_all(char **w_list)
{
	int i;

	i = -1;
	while (w_list[++i])
		free(w_list[i]);
	free(w_list);
	w_list = NULL;
	return (0);
}

t_cmd *ft_cmd_new(void)
{
	t_cmd *tmp;

	tmp = (t_cmd *)malloc(sizeof(t_cmd));
	if (!tmp)
		return (0);
	tmp->simple_cmd = NULL;
	tmp->redir_header = NULL;
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}

void ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd *tmp;

	if (!new)
		return;
	if (!*lst)
	{
		*lst = new;
		new->prev = NULL;
		return;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void ft_cmdclear(t_cmd **lst, void (*del)(void *))
{
	t_cmd *tmp;

	if (!lst || !del)
		return;
	while (*lst)
	{
		tmp = *lst;
		ft_tokenclear(&((*lst)->redir_header), del);
		free_all((*lst)->simple_cmd);
		*lst = tmp->next;
		free(tmp);
	}
	lst = NULL;
}