#include "minishell.h"

char	*heredoc_file()
{
	int		heredoc_idx;
	char	*tmp;
	char	*itoa;

	heredoc_idx = 0;
	itoa = ft_itoa(heredoc_idx);
	tmp = ft_strjoin(".tmp_", itoa);
	while (access(tmp, F_OK) >= 0)
	{
		heredoc_idx++;
		free(tmp);
		free(itoa);
		itoa = ft_itoa(heredoc_idx);
		tmp = ft_strjoin(".tmp_", itoa);
	}
	free(itoa);
	return (tmp);
}

void	heredoc_readline(int fd, char *lim)
{
	char	*input;

	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
		{
			return ;
		}
		if (!ft_strcmp(input, lim))
		{
			free(input);
			return ;
		}
		else
			ft_putendl_fd(input, fd);
		free(input);
	}
}

// void	unlink_temp_files(t_cmd **pipeline)
// {
// 	t_cmd	*cmd;
// 	t_token	*iter;

// 	cmd = *pipeline;
// 	while (cmd)
// 	{
// 		iter = cmd->redir_header;
// 		while (iter)
// 		{
// 			if (iter->type == D_LSR)
// 			{
// 				printf("%s\n", iter->content);
// 				unlink(iter->content);
// 			}
// 			iter = iter->next;
// 		}
// 		cmd = cmd->next;
// 	}
// }

void	unlink_temp_files(t_cmd *cmd)
{
	t_token	*iter;

	iter = cmd->redir_header;
	while (iter)
	{
		if (iter->type == D_LSR)
			unlink(iter->content);
		iter = iter->next;
	}
}

void	change_heredoc(t_cmd *cmd)
{
	t_token	*iter;
	char	*filename;
	int		fd;

	iter = cmd->redir_header;
	while (iter)
	{
		if (iter->type == D_LSR)
		{
			filename = heredoc_file();
			fd = open(filename, O_RDWR | O_CREAT, 0644);
			if (fd == -1)
			{
				perror("minishell: ");
				exit(1);
			}
			heredoc_readline(fd, iter->content);
			free(iter->content);
			iter->content = filename;
			close(fd);
		}
		iter = iter->next;
	}
}