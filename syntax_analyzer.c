#include "minishell.h"

void	identify_token_type(t_list **token_list, t_token **type_list)
{
	char	*word;
	t_list	*iter;
	t_token	*token;

	iter = *token_list;
	while (iter)
	{
		word = ft_strdup(iter->content);
		token = ft_token_new(word);
		if (!ft_strcmp("<", word))
			token->type = LSR;
		else if (!ft_strcmp(">", word))
			token->type = GRT;
		else if (!ft_strcmp("<<", word))
			token->type = D_LSR;
		else if (!ft_strcmp(">>", word))
			token->type = D_GRT;
		else if (!ft_strcmp("|", word))
			token->type = PIPE;
		else
			token->type = WORD;
		ft_tokenadd_back(type_list, token);
		iter = iter->next;
	}
	ft_lstclear(token_list, free);
}

int	syntax_error(t_token **type_list)
{
	t_token	*iter;

	if (!*type_list)
		return (SYNTAX_SUCCESS);
	iter = *type_list;
	while (iter->next)
	{
		if (iter->type != WORD && iter->next->type != WORD)
			return (ft_error(iter->next->content));
		iter = iter->next;
	}
	if (iter->type != WORD)
		return (ft_error("newline"));
	return (SYNTAX_SUCCESS);
}

int	ft_error(char *content)
{
	ft_putstr_fd(SYNTAX_ERROR_MSG, 2);
	ft_putendl_fd(content, STDERR_FILENO);
	return (SYNTAX_ERROR);
}
