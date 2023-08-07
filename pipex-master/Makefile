# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/29 15:39:58 by jonhan            #+#    #+#              #
#    Updated: 2023/08/06 12:14:19 by phan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = pipex
BNAME = pipex
RM = rm -rf
AR = ar
ARFLAGS = crs
SRCS = mandatory/main.c mandatory/pipex_util.c \
	mandatory/ft_split.c mandatory/pipex_util_2.c
SRCS_BONUS = bonus/ft_split.c bonus/gnl_bonus.c bonus/gnl_util_bonus.c \
		bonus/main_bonus.c bonus/pipe_bonus.c bonus/pipe_heredoc_bonus.c \
		bonus/pipex_util_2_bonus.c bonus/pipex_util_bonus.c
OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_BONUS:.c=.o)

all : .MAKE_ALL

bonus : .MAKE_BONUS

.MAKE_ALL : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		$(RM) .MAKE_BONUS
		touch $@

.MAKE_BONUS : $(OBJS_B)
		$(CC) $(CFLAGS) $(OBJS_B) -o $(BNAME)
		$(RM) .MAKE_ALL
		touch $@

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

clean : 
	$(RM) $(RMFLAG) $(OBJS) $(OBJS_B) 
	$(RM) .MAKE_BONUS
	$(RM) .MAKE_ALL

fclean : clean
	$(RM) $(NAME)
	$(RM) $(BNAME)

re : 
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all clean fclean re bonus