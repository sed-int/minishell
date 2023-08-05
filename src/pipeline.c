#include "minishell.h"

char **make_envp(t_list **env)
{
	t_list *iter;
	char **ret;
	int size;

	iter = *env;
	size = 0;
	while (iter)
	{
		size++;
		iter = iter->next;
	}
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ret)
		exit(1);
	iter = *env;
	size = 0;
	while (iter)
	{
		ret[size++] = ft_strdup(iter->content);
		iter = iter->next;
	}
	ret[size] = NULL;
	return (ret);
}

void init_exec(t_exec *exec, t_cmd **pipeline, t_list **env)
{
	exec->count = count_pipe(pipeline);
	exec->repeat_fork = 0;
	exec->path = detec_path(env);
}

void first_child(t_exec arg, t_cmd *cmd, t_list **env)
{
	char *valid_cmd;
	char **envp;

	envp = make_envp(env);
	change_heredoc(cmd);
	if (init_redir(cmd) == 1) //open error
		exit(1);
	dup2(cmd->io_fd[0], STDIN_FILENO);
	if (cmd->io_fd[1] != 1)
		dup2(cmd->io_fd[1], STDOUT_FILENO);
	else if (arg.count > 1)
		dup2(arg.fds_next[1], STDOUT_FILENO);
	if (cmd->io_fd[1] != 1)
		close(cmd->io_fd[1]);
	if (cmd->io_fd[0] != 0)
		close(cmd->io_fd[0]);
	close(arg.fds_next[0]);
	close(arg.fds_next[1]);
	unlink_temp_files(cmd);
	if (is_built_in(cmd->simple_cmd) > -1)
	{
		run_cmd(cmd, env, is_built_in(cmd->simple_cmd));
		exit(error_status);
	}
	if (cmd->simple_cmd[0] == NULL)
		exit(1);
	if (!access(cmd->simple_cmd[0], F_OK))
		valid_cmd = cmd->simple_cmd[0];
	else
		valid_cmd = valid(arg.path, cmd->simple_cmd[0]);
	if (execve(valid_cmd, cmd->simple_cmd, envp) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->simple_cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
}

void middle_child(t_exec arg, t_cmd *cmd, t_list **env)
{
	char *valid_cmd;
	char **envp;

	envp = make_envp(env);
	close(arg.fds_next[0]);
	close(arg.fds_prev[1]);
	change_heredoc(cmd);
	if (init_redir(cmd) == 1) // open error
		exit(1);
	if (cmd->io_fd[1] != 1)
		dup2(cmd->io_fd[1], STDOUT_FILENO);
	else
		dup2(arg.fds_next[1], STDOUT_FILENO);
	if (cmd->io_fd[0] != 0)
		dup2(cmd->io_fd[0], STDIN_FILENO);
	else
		dup2(arg.fds_prev[0], STDIN_FILENO);
	// close(arg.fds_prev[0]);
	if (cmd->io_fd[0] != 0)
		close(cmd->io_fd[0]);
	else
		close(arg.fds_prev[0]);
	if (cmd->io_fd[1] != 1)
		close(cmd->io_fd[1]);
	else
		close(arg.fds_next[1]);
	unlink_temp_files(cmd);
	if (is_built_in(cmd->simple_cmd) > -1)
	{
		run_cmd(cmd, env, is_built_in(cmd->simple_cmd));
		exit(error_status);
	}
	if (cmd->simple_cmd[0] == NULL)
		exit(1);
	if (!access(cmd->simple_cmd[0], F_OK))
		valid_cmd = cmd->simple_cmd[0];
	else
		valid_cmd = valid(arg.path, cmd->simple_cmd[0]);
	if (execve(valid_cmd, cmd->simple_cmd, envp) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->simple_cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
}

void last_child(t_exec arg, t_cmd *cmd, t_list **env)
{
	char *valid_cmd;
	char **envp;

	envp = make_envp(env);
	close(arg.fds_prev[1]);
	change_heredoc(cmd);
	if (init_redir(cmd) == 1) // open error
		exit(1);
	if (cmd->io_fd[1] != 1)
		dup2(cmd->io_fd[1], STDOUT_FILENO);
	if (cmd->io_fd[0] != 0)
		dup2(cmd->io_fd[0], STDIN_FILENO);
	else
		dup2(arg.fds_prev[0], STDIN_FILENO);
	close(arg.fds_prev[0]);
	if (cmd->io_fd[0] != 0)
		close(cmd->io_fd[0]);
	else
		close(arg.fds_prev[0]);
	if (cmd->io_fd[1] != 1)
		close(cmd->io_fd[1]);
	unlink_temp_files(cmd);
	if (is_built_in(cmd->simple_cmd) > -1)
	{
		run_cmd(cmd, env, is_built_in(cmd->simple_cmd));
		exit(error_status);
	}
	close(arg.fds_next[0]);
	close(arg.fds_next[1]);
	if (cmd->simple_cmd[0] == NULL)
		exit(1);
	if (!access(cmd->simple_cmd[0], F_OK))
		valid_cmd = cmd->simple_cmd[0];
	else
		valid_cmd = valid(arg.path, cmd->simple_cmd[0]);
	if (execve(valid_cmd, cmd->simple_cmd, envp) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->simple_cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
}

void wait_child(pid_t pid, int count)
{
	int fork_count;
	int	status;

	fork_count = 0;
	while (pid != 0 && fork_count < count)
	{
		if (waitpid(-1, &status, 0) > 0)
		{
			if (WIFEXITED(status))
				error_status = WEXITSTATUS(status);
			else if (WTERMSIG(status) == 2)
				error_status = 130;
			else if (WTERMSIG(status) == 3)
			{
				error_status = 131;
				printf("QUIT: 3\n");
			}
		}
		else
			return ;
		fork_count++;
	}
	return;
}

void	close_fd(t_exec *arg)
{
	close(arg->fds_prev[0]);
	close(arg->fds_prev[1]);
	if (arg->count > 0)
	{
		close(arg->fds_next[1]);
		close(arg->fds_next[0]);
	}
}

void pipexline(t_cmd **pipeline, t_list **env)
{
	pid_t	pid;
	t_exec	exec;
	t_cmd	*iter;

	iter = *pipeline;
	init_exec(&exec, pipeline, env);
	pipe(exec.fds_prev);
	while (exec.repeat_fork < exec.count)
	{
		if (exec.repeat_fork > 1)
		{
			close(exec.fds_prev[0]);
			close(exec.fds_prev[1]);
		}
		if (exec.repeat_fork != 0)
		{
			exec.fds_prev[0] = exec.fds_next[0];
			exec.fds_prev[1] = exec.fds_next[1];
		}
		if (exec.repeat_fork < exec.count)
			pipe(exec.fds_next);
		error_status = 0;
		pid = fork();
		if (pid == 0 && exec.repeat_fork == 0)
			first_child(exec, iter, env);
		else if (pid == 0 && exec.repeat_fork == exec.count - 1)
			last_child(exec, iter, env);
		else if (pid == 0)
			middle_child(exec, iter, env);
		else
		{
			exec.repeat_fork++;
			iter = iter->next;
		}
	}
	close_fd(&exec);
	wait_child(pid, exec.count);
	// unlink_temp_files(pipeline);
}