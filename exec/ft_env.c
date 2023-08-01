#include "minishell.h"

void	ft_env(t_list **environ, int fd)
{
	t_list	*iter;

	iter = *environ;
	while (iter)
	{
		ft_putstr_fd(iter->content, fd);
		iter = iter->next;
	}
}
