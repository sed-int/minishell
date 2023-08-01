#include "minishell.h"

void	ft_exit(char **simple_cmd)
{
	unsigned char	exit_status;

	if (ft_atouc(simple_cmd[1], &exit_status) == 0)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(simple_cmd[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(255);
	}
	if (simple_cmd[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(simple_cmd[1], 2);
		ft_putendl_fd(": too many arguments", 2);
		exit(255);
	}
	ft_putendl_fd("exit", 2);
	exit(exit_status);
}
