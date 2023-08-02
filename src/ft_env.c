#include "minishell.h"

void	ft_env(char **simple_cmd, t_list **environ, int fd)
{
	t_list	*iter;

	if (!simple_cmd)
		return ;
	iter = *environ;
	while (iter)
	{
		ft_putendl_fd(iter->content, fd);
		iter = iter->next;
	}
}
