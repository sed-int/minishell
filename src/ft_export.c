/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunminjo <hyunminjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:47:59 by hcho2             #+#    #+#             */
/*   Updated: 2023/08/10 18:00:18 by hyunminjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_export_err(char *str)
{
	ft_putstr_fd("minishell: export: \'", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\': not a valid identifier\n", STDERR_FILENO);
	return (0);
}

char	*make_word(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	ret = ft_substr(str, 0, i);
	return (ret);
}

int	is_valid_export_arg(char *str)
{
	int	i;

	i = 0;
	if (str[0] && ft_isdigit(str[0]))
		return (print_export_err(str));
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (print_export_err(str));
		++i;
	}
	if (i == 0)
		return (print_export_err(str));
	return (1);
}

void	print_export(t_list **environ, int fd)
{
	t_list	*iter;

	iter = *environ;
	while (iter)
	{
		ft_putendl_fd(iter->content, fd);
		iter = iter->next;
	}
	g_exit_code = 0;
}

void	ft_export(char **simple_cmd, t_list **environ, int fd)
{
	int		i;
	char	*word;
	t_list	*tmp;

	(void)fd;
	if (!simple_cmd[1])
		print_export(environ, fd);
	i = 0;
	while (simple_cmd[++i])
	{
		word = make_word(simple_cmd[i]);
		if (!word)
			continue ;
		if (is_valid_export_arg(word))
		{
			tmp = ft_getenvnode(environ, word);
			if (tmp)
				ft_lstdel_mid(environ, tmp);
			ft_lstadd_back(environ, ft_lstnew(ft_strdup(simple_cmd[i])));
			g_exit_code = 0;
		}
		else
			g_exit_code = 1;
		free(word);
	}
}
