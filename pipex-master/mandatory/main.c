/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:15:08 by jonhan            #+#    #+#             */
/*   Updated: 2023/07/20 13:51:47 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_arg arg, int *fds, char *argv[], char *envp[])
{
	arg.infile = open(argv[1], O_RDONLY);
	if (arg.infile == -1)
		exit(1);
	dup2(arg.infile, STDIN_FILENO);
	close(fds[0]);
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	close(arg.infile);
	arg.command = ft_split(argv[arg.i], ' ');
	arg.valid_cmd = valid(arg.path, arg.command[0]);
	if (execve(arg.valid_cmd, arg.command, envp) < 0)
	{
		ft_putstr_fd("bash: command not found\n", 2);
		exit(127);
	}
}

void	last_child(t_arg arg, int *fds, char *argv[], char *envp[])
{
	close(fds[1]);
	arg.outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (arg.outfile == -1)
		exit(1);
	dup2(fds[0], STDIN_FILENO);
	dup2(arg.outfile, STDOUT_FILENO);
	close(fds[0]);
	close(arg.outfile);
	arg.command = ft_split(argv[arg.i], ' ');
	arg.valid_cmd = valid(arg.path, arg.command[0]);
	if (execve(arg.valid_cmd, arg.command, envp) < 0)
	{
		ft_putstr_fd("bash: command not found\n", 2);
		exit(127);
	}
}

void	wait_child(pid_t pid, int argc)
{
	int	count;

	count = 0;
	while (pid != 0 && count < argc - 3)
	{
		if (waitpid(-1, 0, 0) < 0)
			return ;
		count++;
	}
	return ;
}

void	pipex(int argc, t_arg arg, char *argv[], char *envp[])
{
	int		fds[2];
	pid_t	pid;

	arg.repeat_fork = 0;
	pipe(fds);
	while (arg.repeat_fork < argc - 3)
	{
		pid = fork();
		if (pid == 0)
		{
			if (pid == 0 && arg.repeat_fork == 0)
				first_child(arg, fds, argv, envp);
			else if (pid == 0 && arg.repeat_fork == 1)
				last_child(arg, fds, argv, envp);
		}
		else
		{
			arg.repeat_fork++;
			arg.i++;
		}
	}
	close(fds[0]);
	close(fds[1]);
	wait_child(pid, argc);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_arg	file;
	t_arg	arg;
	char	*f_name;

	if (argc == 5)
	{
		f_name = ft_strjoin("bash: ", argv[1]);
		file.infile = open(argv[1], O_RDONLY);
		if (file.infile == -1)
			perror(f_name);
		free(f_name);
		close(file.infile);
		arg.path = detec_path(envp);
		arg.i = 2;
		pipex(argc, arg, argv, envp);
		free_arr(arg.path);
	}
	else
	{
		perror("error\n");
		exit(1);
	}
}
