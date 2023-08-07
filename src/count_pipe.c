#include "minishell.h"

int	count_pipe(t_cmd **pipeline)
{
	t_cmd	*iter;
	int		cnt;

	cnt = 0;
	iter = *pipeline;
	while (iter)
	{
		cnt++;
		iter = iter->next;
	}
	return (cnt);
}
