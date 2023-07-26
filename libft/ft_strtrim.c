/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:49:54 by phan              #+#    #+#             */
/*   Updated: 2023/04/01 18:50:51 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_instr(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	rlen;
	int		idx;

	while (*s1 && is_instr(*s1, set))
		s1++;
	rlen = ft_strlen(s1);
	idx = rlen - 1;
	while (idx >= 0 && is_instr(s1[idx], set))
		idx--;
	rlen = idx + 1;
	result = (char *)malloc(sizeof(char) * (rlen + 1));
	if (!result)
		return (0);
	ft_memmove(result, s1, rlen);
	result[rlen] = '\0';
	return (result);
}
