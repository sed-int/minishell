/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunminjo <hyunminjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:48:30 by hcho2             #+#    #+#             */
/*   Updated: 2023/08/12 19:50:28 by hyunminjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	is_n_option(char **simple_cmd)
{
	int	i;
	int	j;

	j = 0;
	while (simple_cmd[++j])
	{
		i = 1;
		if (simple_cmd[j][0] != '-')
			return (0);
		while (simple_cmd[j][i] && simple_cmd[j][i] == 'n')
		{
			i++;
		}
		if (simple_cmd[j][i] && simple_cmd[j][i] != 'n')
			return (0);
	}
	return (1);
}

void	ft_echo(char **simple_cmd, t_list **environ, int fd)
{
	int	i;

	g_exit_code = 0;
	if (is_n_option(simple_cmd))
	{
		i = check_more_newline(simple_cmd);
		while (simple_cmd[i] != NULL)
		{
			ft_putstr_fd(simple_cmd[i], fd);
			if (simple_cmd[i + 1] != NULL)
				ft_putstr_fd(" ", fd);
			i++;
		}
		return ;
	}
	i = 1;
	while (environ && simple_cmd[i] != NULL)
	{
		ft_putstr_fd(simple_cmd[i], fd);
		if (simple_cmd[i + 1] != NULL)
			ft_putstr_fd(" ", fd);
		i++;
	}
	write(fd, "\n", STDOUT_FILENO);
}
