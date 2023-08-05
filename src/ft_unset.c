#include "minishell.h"

t_list	*ft_getenvnode(t_list **environ, char *word)
{
	t_list	*iter;

	iter = *environ;
	while (iter)
	{
		if (!ft_strncmp(iter->content, word, ft_strlen(word)))
			break ;
		iter = iter->next;
	}
	return (iter);
}

void	ft_unset(char **simple_cmd, t_list **environ, int fd)
{
	t_list	*tmp;
	int		i;

	(void)fd;
	tmp = NULL;
	i = 0;
	error_status = 0;
	while (simple_cmd[++i])
	{
		tmp = ft_getenvnode(environ, simple_cmd[i]);
		if (tmp)
			ft_lstdel_mid(environ, tmp);
	}
}


