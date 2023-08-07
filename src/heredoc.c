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
			return ;
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

// void	change_heredoc(t_cmd *cmd)
// {
// 	t_token	*iter;
// 	char	*filename;
// 	int		fd;

// 	iter = cmd->redir_header;
// 	while (iter)
// 	{
// 		if (iter->type == D_LSR)
// 		{
// 			filename = heredoc_file();
// 			fd = open(filename, O_RDWR | O_CREAT, 0644);
// 			if (fd == -1)
// 			{
// 				perror("minishell: ");
// 				exit(1);
// 			}
// 			heredoc_readline(fd, iter->content);
// 			free(iter->content);
// 			iter->content = filename;
// 			close(fd);
// 		}
// 		iter = iter->next;
// 	}
// }

void change_heredoc(t_cmd **pipeline)
{
	t_cmd *iter;
	t_token *red_iter;
	char *file_str;
	int	fd;

	iter = *pipeline;
	while (iter)
	{
		red_iter = iter->redir_header;
		while (red_iter)
		{
			if (red_iter->type == D_LSR)
			{
				file_str = heredoc_file();
				fd = open(file_str, O_CREAT, 0644);
				close(fd);
				red_iter->temp = ft_strdup(red_iter->content);
				free(red_iter->content);
				red_iter->content = file_str;
			}
			red_iter = red_iter->next;
		}
		iter = iter->next;
	}
}

void	read_heredoc(t_cmd **pipeline)
{
	t_cmd *iter;
	t_token *red_iter;
	int fd;
	iter = *pipeline;

	while (iter)
	{
		red_iter = iter->redir_header;
		while (red_iter)
		{
			if (red_iter->type == D_LSR)
			{
				fd = open(red_iter->content, O_RDWR, 0644);
				if (fd == -1)
				{
					perror("minishell: ");
					exit(1);
				}
				heredoc_readline(fd, red_iter->temp);
				close(fd);
			}
			red_iter = red_iter->next;
		}
		iter = iter->next;
	}
	exit(0);
}