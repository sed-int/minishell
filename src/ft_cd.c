/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcho2 <hcho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:47:55 by hcho2             #+#    #+#             */
/*   Updated: 2023/08/11 16:00:27 by hcho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cd_err(char *path, char *str)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	g_exit_code = 1;
}

char	*check_path(char *word, t_list **environ)
{
	char	*pathname;

	if (word)
		pathname = ft_strdup(word);
	else
	{
		pathname = ft_getenv(environ, "HOME");
		if (!pathname)
		{
			print_cd_err("HOME", "not set");
			return (NULL);
		}
	}
	return (pathname);
}

char	*check_cwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", STDOUT_FILENO);
		perror("getcwd: cannot access parent ");
		return (NULL);
	}
	return (cwd);
}

int	renew_pwd(t_list **environ)
{
	char	*cwd;
	t_list	*tmp;

	cwd = check_cwd();
	if (!cwd)
		return (1);
	tmp = ft_getenvnode(environ, "PWD");
	if (tmp == NULL)
		return (1);
	free(tmp->content);
	tmp->content = ft_strjoin("PWD=", cwd);
	free(cwd);
	return (0);
}

void	ft_cd(char **simple_cmd, t_list **environ, int fd)
{
	char	*pathname;
	int		ch;

	(void)fd;
	g_exit_code = 0;
	pathname = check_path(simple_cmd[1], environ);
	if (!pathname)
		return ;
	ch = chdir(pathname);
	if (ch < 0)
		print_cd_err(pathname, "No such file or directory");
	else
		renew_pwd(environ);
	free(pathname);
}
