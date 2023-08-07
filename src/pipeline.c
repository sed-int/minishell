#include "minishell.h"
#include <errno.h>

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
	// change_heredoc(cmd);
	// change_heredoc(pipeline);
	if (init_redir(cmd) == 1) // open error
	{
		unlink_temp_files(cmd);
		exit(1);
	}
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
		run_cmd(cmd, env, is_built_in(cmd->simple_cmd), 0);
		exit(error_status);
	}
	/**
	 * path 먼저 검사, '/' 하나라도 있을시 path 검사 안함
	 * heredoc .tmp파일 안 없어지는 경우들
	 * syscall fail시 예외 처리 -> fork, pipe 등
	*/
	if (cmd->simple_cmd[0] == NULL)
		exit(error_status);

	valid_cmd = valid(arg.path, cmd->simple_cmd[0]);
	if (!valid_cmd && !access(cmd->simple_cmd[0], F_OK))
		valid_cmd = cmd->simple_cmd[0];
	if (execve(valid_cmd, cmd->simple_cmd, envp) < 0)
	{
		if (valid_cmd)
		{
			if (access(valid_cmd, X_OK) < 0)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(valid_cmd);
				exit(126);
			}
			else
				exit(0);
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->simple_cmd[0], 2);
			ft_putendl_fd(": command not found", 2);
			exit(127);
		}
	}
}

void middle_child(t_exec arg, t_cmd *cmd, t_list **env)
{
	char *valid_cmd;
	char **envp;

	envp = make_envp(env);
	close(arg.fds_next[0]);
	close(arg.fds_prev[1]);
	// change_heredoc(cmd);
	if (init_redir(cmd) == 1) // open error
	{
		unlink_temp_files(cmd);
		exit(1);
	}
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
		run_cmd(cmd, env, is_built_in(cmd->simple_cmd), 0);
		exit(error_status);
	}
	if (cmd->simple_cmd[0] == NULL)
		exit(error_status);
	valid_cmd = valid(arg.path, cmd->simple_cmd[0]);
	if (!valid_cmd && !access(cmd->simple_cmd[0], F_OK))
		valid_cmd = cmd->simple_cmd[0];
	if (execve(valid_cmd, cmd->simple_cmd, envp) < 0)
	{
		if (valid_cmd)
		{
			if (access(valid_cmd, X_OK) < 0)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(valid_cmd);
				exit(126);
			}
			else
				exit(0);
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->simple_cmd[0], 2);
			ft_putendl_fd(": command not found", 2);
			exit(127);
		}
	}
}

void last_child(t_exec arg, t_cmd *cmd, t_list **env)
{
	char *valid_cmd;
	char **envp;

	envp = make_envp(env);
	close(arg.fds_prev[1]);
	// change_heredoc(cmd);
	if (init_redir(cmd) == 1) // open error
	{
		unlink_temp_files(cmd);
		exit(1);
	}
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
		run_cmd(cmd, env, is_built_in(cmd->simple_cmd), 0);
		exit(error_status);
	}
	close(arg.fds_next[0]);
	close(arg.fds_next[1]);
	if (cmd->simple_cmd[0] == NULL)
		exit(error_status);
	valid_cmd = valid(arg.path, cmd->simple_cmd[0]);
	if (!valid_cmd && !access(cmd->simple_cmd[0], F_OK))
		valid_cmd = cmd->simple_cmd[0];
	if (execve(valid_cmd, cmd->simple_cmd, envp) < 0)
	{
		if (valid_cmd)
		{
			if (access(valid_cmd, X_OK) < 0)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(valid_cmd);
				exit(126);
			}
			else
				exit(0);
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->simple_cmd[0], 2);
			ft_putendl_fd(": command not found", 2);
			exit(127);
		}
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

void fork_heredoc(t_cmd **pipeline)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		signal(SIGINT, c_handler);
		signal(SIGTERM, c_handler);
		signal(SIGQUIT, SIG_IGN);
		read_heredoc(pipeline);
	}
	if (waitpid(-1, &status, 0) > 0)
	{
		error_status = WEXITSTATUS(status);
	}
}

void pipexline(t_cmd **pipeline, t_list **env)
{
	pid_t	pid;
	t_exec	exec;
	t_cmd	*iter;

	error_status = 0;
	iter = *pipeline;
	init_exec(&exec, pipeline, env);
	fork_heredoc(pipeline);
	if (pipe(exec.fds_prev) < 0)
		exit(1);
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
		{
			if (pipe(exec.fds_next) < 0)
				exit(1);
		}
		// error_status = 0;
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
		}
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

/**
 * syscall 실패 시 예외처리
*/