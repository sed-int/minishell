/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:21:10 by jonhan            #+#    #+#             */
/*   Updated: 2023/08/03 16:36:44 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*valid(char **path, char *command)
{
	char	*tmp;
	char	*path_cmd;
	int		i;
	int		fd;

	i = 0;
	path_cmd = ft_strjoin("/", command);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], path_cmd);
		fd = access(tmp, F_OK);
		if (fd != -1)
		{
			free(path_cmd);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	free(path_cmd);
	return (NULL);
}

void	create_file(t_arg arg, char *argv[])
{
	char	*tmp;
	char	*eof;

	arg.new_file = open(TMP_FILE, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (arg.new_file == -1)
		exit(1);
	eof = ft_strjoin(argv[2], "\n");
	tmp = ft_strdup("");
	while (ft_strcmp(tmp, eof))
	{
		free(tmp);
		tmp = get_next_line(1);
		if (ft_strcmp(tmp, eof))
			ft_putstr_fd(tmp, arg.new_file);
	}
	free(tmp);
	free(eof);
	close(arg.new_file);
}

void	if_heredoc(t_arg arg, char *argv[], int argc, char *envp[])
{
	create_file(arg, argv);
	arg.path = detec_path(envp);
	pipex_heredoc(argc, arg, argv, envp);
	free_arr(arg.path);
}

void	ft_error(void)
{
	ft_putstr_fd("error\n", 2);
	exit(1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_arg	arg;
	char	*f_name;

	if (argc > 5 && !ft_strcmp("here_doc", argv[1]))
	{
		arg.index = 3;
		if_heredoc(arg, argv, argc, envp);
	}
	else if (argc > 4)
	{
		f_name = ft_strjoin("bash: ", argv[1]);
		arg.index = 2;
		// arg.infile = open(argv[1], O_RDONLY);
		// if (arg.infile == -1)
		// 	perror(f_name);
		free(f_name);
		close(arg.infile);
		arg.path = detec_path(envp);
		pipex(argc, arg, argv, envp);
		free_arr(arg.path);
	}
	else
		ft_error();
	return (0);
}
