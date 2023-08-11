/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcho2 <hcho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:49:13 by hcho2             #+#    #+#             */
/*   Updated: 2023/08/11 13:12:43 by hcho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_execve_error(t_cmd *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->simple_cmd[0], STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	exit(127);
}

void	ft_execve(t_exec arg, t_cmd *cmd, char **envp)
{
	char	*valid_cmd;

	valid_cmd = valid(arg.path, cmd->simple_cmd[0]);
	if (!valid_cmd && !access(cmd->simple_cmd[0], F_OK))
		valid_cmd = cmd->simple_cmd[0];
	if (execve(valid_cmd, cmd->simple_cmd, envp) < 0)
	{
		if (valid_cmd)
		{
			if (access(valid_cmd, X_OK) < 0)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				perror(valid_cmd);
				exit(126);
			}
			else
				exit(0);
		}
		else
			ft_execve_error(cmd);
	}
}
