#include "minishell.h"

int	ft_is_blank(int c)
{
	return (c == ' ' || c == '\t');
}

void	make_token(char *input, t_list **token_list, int token_size)
{
	char	*token;
	t_list	*new_token;

	token = ft_substr(input, 0, token_size);
	new_token = ft_lstnew(token);
	if (new_token == NULL)
		exit(1);
	ft_lstadd_back(token_list, new_token);
}

void	tokenizer(char *input, t_list **token_list)
{
	int		token_size;
	int		flag;

	while (*input)
	{
		token_size = 0;
		flag = 0;
		while (ft_is_blank(*input))
			input++;
		while (*input && !ft_is_blank(*input))
		{
			if (*input == '|')
			{
				if (token_size)
				{
					make_token(input - token_size, token_list, token_size);
					token_size = 0;
				}
				make_token(input++, token_list, 1);
			}
			else if (*input == '<' || *input == '>')
			{
				if (token_size)
				{
					make_token(input - token_size, token_list, token_size);
					token_size = 0;
				}
				if (*(input + 1) == *input)
				{
					make_token(input, token_list, 2);
					input += 2;
				}
				else
					make_token(input++, token_list, 1);
			}
			else if (*input == '\"' || *input == '\'')
			{
				flag = *input;
				while (flag && *input)
				{
					token_size++;
					input++;
					if (*input == flag)
					{
						token_size++;
						input++;
						flag = 0;
					}
				}
				if (flag)
					return ;
			}
			else
			{
				token_size++;
				input++;
			}
		}
		if (token_size)
			make_token(input - token_size, token_list, token_size);
	}
}
