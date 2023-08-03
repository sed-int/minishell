#include "minishell.h"

int init_redir(t_cmd *cmd)
{
	t_token	*redir_iter;
	int		type;

	// cmd->io_fd[0] = 0;
	// cmd->io_fd[1] = 1;
	// dup2(cmd->io_fd[0], STDIN_FILENO);
	// dup2(cmd->io_fd[1], STDOUT_FILENO);
	redir_iter = cmd->redir_header;
	while (redir_iter)
	{
		type = redir_iter->type;
		if (type == LSR || type == D_LSR) //access
		{
			if (cmd->io_fd[0] != 0)
				close(cmd->io_fd[0]);
			cmd->io_fd[0] = open(redir_iter->content, O_RDONLY);
			if (cmd->io_fd[0] < 0)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(redir_iter->content);
				return (1);
			}
		}
		else if (type == GRT) //create file
		{
			if (cmd->io_fd[1] != 1)
				close(cmd->io_fd[1]);
			cmd->io_fd[1] = open(redir_iter->content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (cmd->io_fd[1] < 0)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(redir_iter->content);
				return (1);
			}
		}
		else if (type == D_GRT) //access chmod == 000
		{
			if (cmd->io_fd[1] != 1)
				close(cmd->io_fd[1]);
			cmd->io_fd[1] = open(redir_iter->content, O_APPEND | O_WRONLY | O_CREAT, 0644);
			if (cmd->io_fd[1] < 0)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(redir_iter->content);
				return (1);
			}
		}
		redir_iter = redir_iter->next;
	}
	return (0);
}

void while_pipe(t_cmd **pipeline)
{
	t_cmd *iter;

	iter = *pipeline;
	while (iter)
	{
		printf("<pipe 1>\n");
		init_redir(iter);
		iter = iter->next;
	}
}