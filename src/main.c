#include "minishell.h"

void make_token(char *input, t_list **token_list, int token_size)
{
	char *token;
	t_list *new_token;

	token = ft_substr(input, 0, token_size);
	new_token = ft_lstnew(token);
	if (new_token == NULL)
		exit(1);
	ft_lstadd_back(token_list, new_token);
}

char	*substitute_env(int before_len, char *after, char *content)
{
	char	*env_subs;
	int		i;
	int		j;

	env_subs = (char *)malloc(sizeof(char) * \
		(ft_strlen(content) + ft_strlen(after) - before_len));
	if (!env_subs)
		exit(1);
	i = 0;
	while (content[i] && !ft_strchr(" |<>\'$", content[i]))
	{
		env_subs[i] = content[i];
		i++;
	}
	j = 0;
	while (after[j])
	{
		env_subs[i + j] = after[j];
		j++;
	}
	while (content[i + before_len + 1])
	{
		env_subs[i + j] = content[i + before_len + 1];
		i++;
	}
	env_subs[i + j] = '\0';
	free(content);
	return (env_subs);
}

void	expand_env(t_list **token_list, t_list **environ)
{
	t_list	*iter;
	t_list	*iter_next;
	t_list	*tmp_list;
	char	*tmp;
	int		flag;
	int		i;
	int		exp_flag;

	exp_flag = 0;
	tmp_list = NULL;
	iter = *token_list;
	while (iter)
	{
		tmp = (char *)iter->content;
		iter_next = iter->next;
		i = 0;
		if (ft_strchr(tmp, '$'))
		{
			while (tmp[i])
			{
				flag = 0;
				if (tmp[i] == '\'' || tmp[i] == '\"')
				{
					flag = tmp[i];
					while (flag == '\'' && tmp[i])
					{
						i++;
						if (tmp[i] == flag)
						{
							flag = 0;
							i++;
						}
					}
					while (tmp[i] && flag == '\"')
					{
						if (tmp[i] != '$')
							i++;
						if (tmp[i] == '$')
						{
							exp_flag = 1;
							expansion(iter, iter->content, &i, environ);
							tokenizer(iter->content, &tmp_list);
							ft_lstadd_mid(iter, &tmp_list);
							ft_lstclear(&tmp_list, free);
							flag = 0;
							break;
						}
					}
					if (exp_flag)
						break ;
				}
				else
				{
					if (tmp[i] == '$')
					{
						exp_flag = 1;
						expansion(iter, iter->content, &i, environ);
						tokenizer(iter->content, &tmp_list);
						ft_lstadd_mid(iter, &tmp_list);
						ft_lstclear(&tmp_list, free);
						break ;
					}
					i++;
				}
			}
		}
		iter = iter->next;
		if (exp_flag && iter != NULL)
		{
			ft_lstdel_mid(token_list, iter->prev);
			iter = iter_next;
			exp_flag = 0;
		}
	}
}


void	list_print(void *content)
{
	printf("token: [%s]\n", (char *)content);
}

void	token_print(t_token *node)
{
	printf("token: [%s], type: %d len: %zu\n", node->content, node->type, ft_strlen(node->content));
}

t_list *dup_envp(char **envp)
{
	t_list	*environ;
	int	i;

	i = -1;
	while (envp[++i])
		ft_lstadd_back(&environ, ft_lstnew(ft_strdup(envp[i])));
	return (environ);
}

void	print_env(char **environ)
{
	int i = -1;
	while (environ[++i])
		printf("environ : %s\n", environ[i]);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_list	*environ;
	t_list	*token_list;
	t_token	*type_list;
	t_cmd	*pipeline;

	token_list = NULL;
	type_list = NULL;
	environ = dup_envp(envp);
	(void)ac;
	(void)av;
	while (1)
	{
		input = readline("🐮🦪> ");
		add_history(input);
		tokenizer(input, &token_list);
		// ft_lstiter(token_list, list_print);
		expand_env(&token_list, &environ);
		identify_token_type(&token_list, &type_list);
		free(input);
		if (syntax_error(&type_list) == SYNTAX_ERROR)
			continue ;
		dequotenize(&type_list);
		pipeline = struct_cmd(&type_list);
		ft_exec(&pipeline, &environ);
		ft_cmdclear(&pipeline, free);
		ft_tokenclear(&type_list, free);
	}
}
