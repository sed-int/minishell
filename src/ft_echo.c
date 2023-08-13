/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcho2 <hcho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:48:30 by hcho2             #+#    #+#             */
/*   Updated: 2023/08/13 14:25:29 by hcho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n_option(char *simple_cmd)
{
	int	i;

	i = 0;
	if (simple_cmd[i] && simple_cmd[i] == '-')
		i++;
	else
		return (0);
	if (!simple_cmd[i])
		return (0);
	while (simple_cmd[i] && simple_cmd[i] == 'n')
		i++;
	if (simple_cmd[i] && simple_cmd[i] != 'n')
		return (0);
	return (1);
}

int	check_printable_cmd(char **simple_cmd)
{
	int	i;

	i = 1;
	while (simple_cmd[i])
	{
		if (is_n_option(simple_cmd[i]))
			i++;
		else
			return (i);
	}
	return (i);
}

void	ft_echo(char **simple_cmd, t_list **environ, int fd)
{
	int	newline_flag;
	int	i;

	g_exit_code = 0;
	newline_flag = 1;
	if (!environ)
		return ;
	i = check_printable_cmd(simple_cmd);
	if (i > 1)
		newline_flag = 0;
	while (simple_cmd[i] != NULL)
	{
		ft_putstr_fd(simple_cmd[i], fd);
		if (simple_cmd[i + 1] != NULL)
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (newline_flag)
		write(fd, "\n", 1);
}
