#include "minishell.h"

char *ft_token_strjoin(t_token **lst)
{
	t_token	*iter;
	char	*res;
	char	*tmp;

	res = ft_strdup((char *)(*lst)->content);
	iter = (*lst)->next;
	tmp = 0;
	while (iter)
	{
		tmp = res;
		res = ft_strjoin(res, iter->content);
		free(tmp);
		iter = iter->next;
	}
	return (res);
}

void	redir_type(t_token **type_list, t_token *node)
{
	char	*tmp;

	tmp = node->content;
	node->content = ft_strdup(node->next->content);
	free(tmp);
	ft_tokendel_mid(type_list, node->next);
}

void	print_cmd(t_cmd *pipeline)
{
	t_cmd	*iter;
	char	**tmp;

	iter = pipeline;
	while (iter)
	{
		tmp = iter->simple_cmd;
		while (*tmp)
		{
			printf("token : %s ", *tmp);
			tmp++;
		}
		printf("\n");
		if (iter->redir_header)
			ft_tokeniter(iter->redir_header, token_print);
		iter = iter->next;
	}
	printf("\n");
}

char	**make_simple_cmd(t_token *word_list)
{
	t_token	*iter;
	char	**ret;
	int		size;

	iter = word_list;
	size = 0;
	while (iter)
	{
		size++;
		iter = iter->next;
	}
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	iter = word_list;
	size = 0;
	while (iter)
	{
		ret[size++] = ft_strdup(iter->content);
		iter = iter->next;
	}
	ret[size] = NULL;
	return (ret);
}

t_cmd	*struct_cmd(t_token **type_list)
{
	t_cmd	*pipeline;
	t_cmd	*cmd;
	t_token	*iter;
	t_token	*word_list;
	t_token *new;

	iter = *type_list;
	pipeline = NULL;
	word_list = NULL;
	cmd = ft_cmd_new();
	while (iter)
	{
		if (iter->type == WORD)
		{
			ft_tokenadd_back(&word_list, ft_token_new(WORD, ft_strdup(iter->content)));
		}
		else if (iter->type == PIPE)
		{
			cmd->simple_cmd = make_simple_cmd(word_list);
			ft_tokenclear(&word_list, free);
			ft_cmdadd_back(&pipeline, cmd);
			cmd = ft_cmd_new();
		}
		else
		{
			redir_type(type_list, iter);
			new = ft_token_new(iter->type, ft_strdup(iter->content));
			ft_tokenadd_back(&(cmd->redir_header), new);
		}
		iter = iter->next;
	}
	cmd->simple_cmd = make_simple_cmd(word_list);
	ft_tokenclear(&word_list, free);
	ft_cmdadd_back(&pipeline, cmd);
	print_cmd(pipeline);
	return (pipeline);
}
