#include "minishell.h"

int	is_delim(char c)
{
	return (c == '$' || c == '\'' || c == '\"');
}

char	*ft_lst_strjoin(t_list **lst)
{
	t_list	*iter;
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



void	expansion(t_list *node, char *content, int *idx, t_list **environ)
{
	t_vars	vars;
	t_list	*lst;

	init_vars(&vars);
	lst = NULL;
	while (content[vars.i])
	{
		vars.size = 0;
		if (content[vars.i + vars.size] == '$' && vars.q_flag != '\'')
			expand_key(content, &vars, environ);
		else if (content[vars.i + vars.size] == '\''
			|| content[vars.i + vars.size] == '\"')
			check_quote(&vars, content[vars.i + vars.size]);
		else
			sub_key(content, &vars, environ);
		ft_lstadd_back(&lst, ft_lstnew(vars.str));
	}
	*idx = vars.i;
	free(node->content);
	node->content = ft_lst_strjoin(&lst);
	ft_lstclear(&lst, free);
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
		if (iter->prev && !ft_strcmp("<<", iter->prev->content))
		{
			iter = iter->next;
			if (!iter)
				break ;
		}
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
							if (!(iter->prev && (!ft_strcmp(iter->prev->content, "<") || \
								!ft_strcmp(iter->prev->content, ">") || !ft_strcmp(iter->prev->content, ">>"))))
								tokenizer(iter->content, &tmp_list);
							ft_lstadd_mid(iter, &tmp_list);
							ft_lstclear(&tmp_list, free);
							flag = 0;
							break ;
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
						if (!(iter->prev && (!ft_strcmp(iter->prev->content, "<") || \
							!ft_strcmp(iter->prev->content, ">") || !ft_strcmp(iter->prev->content, ">>"))))
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
