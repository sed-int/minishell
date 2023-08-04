#include "minishell.h"

/**
 * pwd will absolutely run in child process.
*/
void	ft_pwd(char **simple_cmd, t_list **environ, int fd)
{
	char	*str;

	if (!environ)
		return ;
	if (simple_cmd[1] != NULL && simple_cmd[1][0] == '-')
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(simple_cmd[1], 2);
		ft_putendl_fd(": invalid option ", 2);
		ft_putendl_fd("pwd: no option", 2);
		error_status = 1;
		return ;
	}
	str = NULL;
	str = getcwd(str, 0);
	ft_putendl_fd(str, fd);
	free(str);
}

// int	main(int argc, char **argv)
// {
// 	ft_pwd(argv, 1);
// }
