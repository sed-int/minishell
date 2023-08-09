/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunminjo <hyunminjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:49:21 by hcho2             #+#    #+#             */
/*   Updated: 2023/08/10 01:31:26 by hyunminjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_minishell(void)
{
	printf("              _         _         __          __    __ \n");
	printf("   ____ ___  (_) ____  (_) _____ / /_   ___  / /   / /\n");
	printf("  / __ `__ \\/ / / __ \\/ / / ___// __ \\ / _ \\/ /   / /\n");
	printf(" / / / / / / / / / / / / (__  )/ / / /( ___/ /___/ /___\n");
	printf("/_/ /_/ /_/_/ /_/ /_/_/ /____//_/ /_/ \\___/_____/_____/\n");
	printf("                                  ver.1 @hcho2 @junssong\n");
}

t_list	*dup_envp(char **envp)
{
	t_list	*environ;
	int		i;

	environ = NULL;
	i = -1;
	while (envp[++i])
		ft_lstadd_back(&environ, ft_lstnew(ft_strdup(envp[i])));
	return (environ);
}

void	init_main(t_list **environ, t_list **token_list, \
	t_token **type_list, char **envp)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	*token_list = NULL;
	*type_list = NULL;
	*environ = dup_envp(envp);
	print_minishell();
}
