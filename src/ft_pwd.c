/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunminjo <hyunminjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:48:40 by hcho2             #+#    #+#             */
/*   Updated: 2023/08/10 12:48:26 by hyunminjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **simple_cmd, t_list **environ, int fd)
{
	char	*str;

	if (!environ)
		return ;
	if (simple_cmd[1] != NULL && simple_cmd[1][0] == '-')
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(simple_cmd[1], STDERR_FILENO);
		ft_putendl_fd(": invalid option ", STDERR_FILENO);
		ft_putendl_fd("pwd: no option", STDERR_FILENO);
		g_exit_code = 1;
		return ;
	}
	str = NULL;
	str = getcwd(str, 0);
	if (str == NULL)
		str = ft_strdup(".");
	ft_putendl_fd(str, fd);
	free(str);
}
