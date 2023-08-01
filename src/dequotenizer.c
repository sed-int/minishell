#include "minishell.h"

char	*modify_word(char *word, char *wd_flag, int wd_len)
{
	char	*res;
	int		i;
	int		j;
	int		res_len;

	i = 0;
	res_len = 0;
	while (i < wd_len)
	{
		if (wd_flag[i] != 1)
			res_len++;
		i++;
	}
	res = (char *)malloc(res_len + 1);
	i = 0;
	j = 0;
	while (i < wd_len && j < res_len)
	{
		if (wd_flag[i] == 0)
			res[j++] = word[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

void	dequotenize(t_token **type_list)
{
	t_token	*iter;
	char	*word;
	size_t	wd_len;
	int		q_flag;
	char	*wd_flag;
	int		i;

	iter = *type_list;
	while (iter)
	{
		word = iter->content;
		wd_len = ft_strlen(word);
		q_flag = 0;
		wd_flag = (char *)ft_calloc(1, wd_len + 1);
		i = 0;
		while (word[i])
		{
			if (word[i] && word[i] == '\"')
			{
				if (q_flag != '\'')
					wd_flag[i] = 1;
				if (q_flag == 0)
					q_flag = '\"';
				else if (q_flag == '\"')
					q_flag = 0;
			}
			else if (word[i] && word[i] == '\'')
			{
				if (q_flag != '\"')
					wd_flag[i] = 1;
				if (q_flag == 0)
					q_flag = '\'';
				else if (q_flag == '\'')
					q_flag = 0;
			}
			i++;
		}
		iter->content = modify_word(word, wd_flag, wd_len);
		free(word);
		free(wd_flag);
		iter = iter->next;
	}
}
