/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:53:25 by jonhan            #+#    #+#             */
/*   Updated: 2023/08/04 14:37:28 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define TMP_FILE "7884779F-D071-44C5-B19D-AD84880036CD"

typedef struct s_arg{
	int		infile;
	int		outfile;
	char	**path;
	// char	**parse_arg;
	char	**command;
	char	*valid_cmd;
	int		repeat_fork;
	int		fds_next[2];
	int		fds_prev[2];
	int		index;
	int		new_file;
}	t_arg;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strcat(char *dest, char *src);
void	ft_putstr_fd(char *s, int fd);
char	**detec_path(char *envp[]);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *str);
size_t	ft_strlcpy(char	*dst, char *src, size_t dstsize);
char	*ft_strdup(char *src);
int		ft_strcmp(char *s1, char *s2);
char	*free_arr(char **arr);

char	**ft_split(char const *str, char c);

void	pipex(int argc, t_arg arg, char *argv[], char *envp[]);
void	pipex_heredoc(int argc, t_arg arg, char *argv[], char *envp[]);
char	*valid(char **path, char *command);
void	close_fd(t_arg *arg);

int		ft_strchr_index(char *str, int c);
char	*get_next_line(int fd);
#endif