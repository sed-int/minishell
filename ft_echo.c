#include "minishell.h"

int	check_more_newline(char **simple_cmd)
{
	int	i;

	i = 2;
	while (simple_cmd[i] != NULL)
	{
		if (simple_cmd[i] != NULL && !ft_strcmp("-n", simple_cmd[i]))
			i++;
		else
			break ;
	}
	return (i);

}

void	ft_echo(char **simple_cmd, int fd)
{
	int	i;

	if (simple_cmd[1] != NULL && !ft_strcmp("-n", simple_cmd[1]))
	{
		i = check_more_newline(simple_cmd);
		while (simple_cmd[i] != NULL)
		{
			ft_putstr_fd(simple_cmd[i], fd);
			if (simple_cmd[i + 1] != NULL)
				ft_putstr_fd(" ", fd);
			i++;
		}
		exit(0);
	}
	i = 1;
	while (simple_cmd[i] != NULL)
	{
		ft_putstr_fd(simple_cmd[i], fd);
		if (simple_cmd[i + 1] != NULL)
			ft_putstr_fd(" ", fd);
		i++;
	}
	write(fd, "\n", 1);
}

// int	main(int argc, char **argv)
// {
// 	ft_echo(argv, 1);
// }
