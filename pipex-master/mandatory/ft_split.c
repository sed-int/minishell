/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:43:32 by jonhan            #+#    #+#             */
/*   Updated: 2023/07/13 15:36:05 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static unsigned int	word_count(char const *str, char c)
{
	unsigned int	i;
	unsigned int	count;

	count = 0;
	i = 0;
	while (str[i])
	{	
		while (str[i] && (str[i] == c))
			i++;
		if (str[i])
			count++;
		while (str[i] && !(str[i] == c))
			i++;
	}
	return (count);
}

static char	**freeall(char **array, unsigned int j)
{
	unsigned int	i;

	i = 0;
	while (i < j)
		free(array[i++]);
	free(array);
	return ((char **)0);
}

static unsigned int	s_len(char const *str, char c)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			i++;
		else
			break ;
	}
	return (i);
}

static char	*word_cut(char const *str, char c)
{
	char			*word;
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = s_len(str, c);
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (0);
	while (j < i)
	{
		word[j] = str[j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

char	**ft_split(char const *str, char c)
{
	char			**array;
	unsigned int	j;
	unsigned int	i;
	unsigned int	word_num;

	i = 0;
	j = 0;
	word_num = word_count(str, c);
	array = (char **)malloc(sizeof(char *) * (word_num + 1));
	if (!array)
		return (0);
	while (j < word_num)
	{
		while (str[i] && (str[i] == c))
			i++;
		if (str[i])
			array[j++] = word_cut(&str[i], c);
		if (!array[j - 1])
			return (freeall(array, j));
		while (str[i] && !(str[i] == c))
			i++;
	}
	array[j] = 0;
	return (array);
}
