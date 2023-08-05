#include "minishell.h"

void	p_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	if (error_status != 0)
		rl_redisplay();
	error_status = 1;
}