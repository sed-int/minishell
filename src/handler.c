/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunminjo <hyunminjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:48:48 by hcho2             #+#    #+#             */
/*   Updated: 2023/08/10 01:26:36 by hyunminjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	p_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_code = 1;
}

void	c_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		exit(1);
	}
	else if (sig == SIGTERM)
		exit(0);
}
