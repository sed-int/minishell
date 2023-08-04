/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:52:55 by jonhan            #+#    #+#             */
/*   Updated: 2023/07/19 12:05:14 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
	{
		len++;
	}
	return (len);
}

size_t	ft_strlcpy(char	*dst, char *src, size_t dstsize)
{
	size_t	temp;
	size_t	i;

	i = 0;
	temp = ft_strlen(src);
	if (src[0] == '\0')
	{
		dst[0] = '\0';
		return (0);
	}
	if (dstsize == 0)
		return (temp);
	while (i < temp && i + 1 < dstsize)
	{
		if (src[i] == '\0')
			break ;
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (temp);
}

char	*valid(char **path, char *command)
{
	char	*tmp;
	char	*path_cmd;
	int		i;
	int		fd;

	i = 0;
	path_cmd = ft_strjoin("/", command);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], path_cmd);
		fd = access(tmp, F_OK);
		if (fd != -1)
		{
			free(path_cmd);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	free(path_cmd);
	return (NULL);
}

char	*ft_strdup(char *src)
{
	int		index;
	int		j;
	char	*des;

	j = 0;
	index = 0;
	if (!src)
	{
		return (NULL);
	}
	while (src[index] != '\0')
		index++;
	des = (char *)malloc((index + 1) * sizeof(char));
	if (!des)
		return (NULL);
	while (src[j] != '\0')
	{
		des[j] = src[j];
		j++;
	}
	des[j] = '\0';
	return (des);
}

char	*free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}
