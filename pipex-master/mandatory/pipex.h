/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:15:23 by jonhan            #+#    #+#             */
/*   Updated: 2023/07/19 15:35:18 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_arg{
	int		infile;
	int		outfile;
	char	**path;
	char	**parse_arg;
	char	**command;
	char	*valid_cmd;
	int		repeat_fork;
	int		i;
}	t_arg;

//main
void	pipex(int argc, t_arg arg, char *argv[], char *envp[]);
char	*valid(char **path, char *command);

//util
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strcat(char *dest, char *src);
char	**detec_path(char *envp[]);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*free_arr(char **arr);
size_t	ft_strlen(char *str);
size_t	ft_strlcpy(char	*dst, char *src, size_t dstsize);
//split
char	**ft_split(char const *str, char c);

#endif
