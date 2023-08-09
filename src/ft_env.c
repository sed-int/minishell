/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunminjo <hyunminjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:48:33 by hcho2             #+#    #+#             */
/*   Updated: 2023/08/10 01:26:36 by hyunminjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **simple_cmd, t_list **environ, int fd)
{
	t_list	*iter;

	g_exit_code = 0;
	if (!simple_cmd)
		return ;
	iter = *environ;
	while (iter)
	{
		if (ft_strchr(iter->content, '='))
			ft_putendl_fd(iter->content, fd);
		iter = iter->next;
	}
}
