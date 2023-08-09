#include "minishell.h"

int	is_redir(t_list *node)
{
	return ((node->prev && \
		(!ft_strcmp(node->prev->content, "<") || \
		!ft_strcmp(node->prev->content, ">") || \
		!ft_strcmp(node->prev->content, ">>"))));
}

void	to_expand(t_list *node, t_list *environ, int *i)
{
	t_list	*temp_list;

	temp_list = NULL;
	expansion(node, node->content, i, &environ);
	if (!is_redir(node))
		tokenizer(node->content, &temp_list);
	ft_lstadd_mid(node, &temp_list);
	ft_lstclear(&temp_list, free);
}

int	search_quoted(t_list *node, t_list *environ, int *q_flag, int *i)
{
	char	*word;

	word = node->content;
	*q_flag = word[*i];
	while (*q_flag == '\'' && word[*i])
	{
		*i += 1;
		if (word[*i] == *q_flag)
		{
			*q_flag = 0;
			*i += 1;
		}
	}
	while (word[*i] && *q_flag == '\"')
	{
		if (word[*i] != '$')
			*i += 1;
		if (word[*i] == '$')
		{
			to_expand(node, environ, i);
			*q_flag = 0;
			return (1);
		}
	}
	return (0);
}

void	search_exp(t_list *node, t_list *environ, int *exp_flag, int i)
{
	char	*word;
	int		q_flag;

	word = node->content;
	while (word[i])
	{
		q_flag = 0;
		if (word[i] == '\'' || word[i] == '\"')
		{
			*exp_flag = search_quoted(node, environ, &q_flag, &i);
			if (*exp_flag)
				break ;
		}
		else
		{
			if (word[i] == '$')
			{
				*exp_flag = search_quoted(node, environ, &q_flag, &i);
				break ;
			}
			i++;
		}
	}
}

void	delete_double(t_list **token_list, \
	t_list **node, t_list **next, int *exp_flag)
{
	ft_lstdel_mid(token_list, (*node)->prev);
	*node = *next;
	*exp_flag = 0;
}
