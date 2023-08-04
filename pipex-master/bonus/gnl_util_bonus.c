/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_util_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:24:25 by jonhan            #+#    #+#             */
/*   Updated: 2023/07/17 15:57:28 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// size_t	ft_strlen(char *str)
// {
// 	size_t	len;

// 	len = 0;
// 	while (str[len])
// 	{
// 		len++;
// 	}
// 	return (len);
// }

int	ft_strchr_index(char *str, int c)
{
	int	i;

	i = 0;
	while ((str[i] != c) && (str[i] != '\0'))
		i++;
	if (str[i] != c)
		return (-1);
	return (i);
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

// char	*ft_strdup(char *src)
// {
// 	int		index;
// 	int		j;
// 	char	*des;

// 	j = 0;
// 	index = 0;
// 	if (!src)
// 	{
// 		return (NULL);
// 	}
// 	while (src[index] != '\0')
// 		index++;
// 	des = (char *)malloc((index + 1) * sizeof(char));
// 	if (!des)
// 		return (NULL);
// 	while (src[j] != '\0')
// 	{
// 		des[j] = src[j];
// 		j++;
// 	}
// 	des[j] = '\0';
// 	return (des);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*str;
// 	size_t	s1_len;
// 	size_t	s2_len;

// 	s1_len = ft_strlen(s1);
// 	s2_len = ft_strlen(s2);
// 	if (!s1 || !s2)
// 		return (NULL);
// 	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
// 	if (!str)
// 	{
// 		return (NULL);
// 	}
// 	ft_strlcpy(str, s1, s1_len + 1);
// 	ft_strlcpy(str + s1_len, s2, s2_len + 1);
// 	return (str);
// }

// size_t	ft_strlcpy(char	*dst, char *src, size_t dstsize)
// {
// 	size_t	temp;
// 	size_t	i;

// 	i = 0;
// 	temp = ft_strlen(src);
// 	if (src[0] == '\0')
// 	{
// 		dst[0] = '\0';
// 		return (0);
// 	}
// 	if (dstsize == 0)
// 		return (temp);
// 	while (i < temp && i + 1 < dstsize)
// 	{
// 		if (src[i] == '\0')
// 			break ;
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	dst[i] = '\0';
// 	return (temp);
// }
