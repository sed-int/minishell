#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

# define SYNTAX_SUCCESS	0
# define SYNTAX_ERROR	258
# define SYNTAX_ERROR_MSG "minishell: syntax error near unexpected token: "

enum	e_type
{
	GRT,
	D_GRT,
	LSR,
	D_LSR,
	PIPE,
	WORD
};

typedef struct s_exp_vars
{
	char	*exp;
	char	*new;
	char	*parsed_env;
	int		env_size;
}	t_exp_vars;

typedef struct s_token
{
	enum e_type		type;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd
{
	char			**simple_cmd;
	t_token			*redir_header;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

int		is_delim_in_dquote(char c);
void	tokenizer(char *input, t_list **token_list);
void	list_print(void *content);
void	make_token(char *input, t_list **token_list, int token_size);
void	expansion(t_list *node, char *content, int *idx, char **environ);
void	identify_token_type(t_list **lst, t_token **token_lst);
int		syntax_error(t_token **type_list);

//util
char	*ft_lst_strjoin(t_list **lst);
int		ft_strcmp(char *s1, char *s2);
t_token	*ft_token_new(int type, void *content);
void	ft_tokenadd_back(t_token **lst, t_token *new);
void	ft_tokenclear(t_token **lst, void (*del)(void *));
void	ft_tokeniter(t_token *lst, void (*f)(t_token *));
void	ft_tokendel_mid(t_token **lst, t_token *node);
int		ft_error(t_token **type_list, char *content);
int		ft_is_blank(int c);
char	*ft_getenv(char **environ, char *word);

t_cmd	*ft_cmd_new(void);
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new);
void	ft_cmdclear(t_cmd **lst, void (*del)(void *));
void dequotenize(t_token **type_list);

t_cmd	*struct_cmd(t_token **type_list);

void token_print(t_token *node); // to delete

#endif


