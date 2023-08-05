#include "minishell.h"

void	ft_exec(t_cmd **pipeline, t_list **environ)
{
	t_cmd	*iter;

	if (!pipeline || !*pipeline)
		return ;
	iter = *pipeline;
	while (iter)
	{
		run_cmd(iter, environ, 0);
		iter = iter->next;
	}
}


