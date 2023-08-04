#include "minishell.h"

t_list	*ft_getenvnode(t_list **environ, char *word)
{
	size_t	wd_len;
	t_list	*iter;

	iter = *environ;
	wd_len = ft_strlen(word);
	while (iter)
	{
		if (ft_strnstr(iter->content, word, wd_len))
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


