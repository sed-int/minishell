#include "minishell.h"

int	is_delim_in_dquote(char c)
{
	return (c == '<' || c == '>' || c == '\'' || c == '|' || c == '$' || c == ' ');
}

int	ft_strcmp(char *s1, char *s2)
{
	int				i;
	unsigned char	*us1;
	unsigned char	*us2;

	i = 0;
	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	while (us1[i] != '\0' && us2[i] != '\0')
	{
		if (us1[i] == us2[i])
		{
			i++;
		}
		else
			return (us1[i] - us2[i]);
	}
	return (us1[i] - us2[i]);
}

t_token	*ft_token_new(void *content)
{
	t_token	*tmp;

	tmp = (t_token *)malloc(sizeof(t_token));
	if (!tmp)
		return (0);
	tmp->type = -1;
	tmp->content = content;
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}

void	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		new->prev = NULL;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	ft_tokenclear(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = *lst;
		del((*lst)->content);
		*lst = tmp->next;
		free(tmp);
	}
	lst = NULL;
}

void	ft_tokeniter(t_token *lst, void (*f)(t_token *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst);
		lst = lst->next;
	}
}

int		check_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr("0123456789", str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atouc(char *str, unsigned char *num)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (check_num(str) == 0)
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*(str++) - '0');
		if (check_over_max(sign, result, str))
			return (0);
		if (check_under_min(sign, result, str))
			return (0);
	}
	*num = (unsigned char)(result * sign);
	return (1);
}
