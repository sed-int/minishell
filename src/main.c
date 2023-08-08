#include "minishell.h"

t_list	*dup_envp(char **envp)
{
	t_list	*environ;
	int		i;

	environ = NULL;
	i = -1;
	while (envp[++i])
		ft_lstadd_back(&environ, ft_lstnew(ft_strdup(envp[i])));
	return (environ);
}

char	*get_pwd(void)
{
	char	**spl;
	char	*tmp;
	int		size;

	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
		return (". % ");
	spl = ft_split(tmp, '/');
	free(tmp);
	size = 0;
	while (spl[size])
		size++;
	return (ft_strjoin(spl[size - 1], " % "));
}

void	hello_minishell(void)
{
	printf("              _         _         __          __    __ \n");
	printf("   ____ ___  (_) ____  (_) _____ / /_   ___  / /   / /\n");
	printf("  / __ `__ \\/ / / __ \\/ / / ___// __ \\ / _ \\/ /   / /\n");
	printf(" / / / / / / / / / / / / (__  )/ / / /( ___/ /___/ /___\n");
	printf("/_/ /_/ /_/_/ /_/ /_/_/ /____//_/ /_/ \\___/_____/_____/\n");
	printf("                    ver.1  @phan @jonhan @hcho2 @junssong\n");
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_list	*environ;
	t_list	*token_list;
	t_token	*type_list;
	t_cmd	*pipeline;

	token_list = NULL;
	type_list = NULL;
	environ = dup_envp(envp);
	(void)ac;
	(void)av;
	hello_minishell();
	while (1)
	{
		signal(SIGINT, p_handler);
		signal(SIGQUIT, SIG_IGN);
		input = readline(get_pwd());
		if (!input)
		{
			ft_putendl_fd("\nexit", 1);
			exit(0);
		}
		if (*input)
			add_history(input);
		tokenizer(input, &token_list);
		expand_env(&token_list, &environ);
		identify_token_type(&token_list, &type_list);
		free(input);
		if (syntax_error(&type_list) == SYNTAX_ERROR)
			continue ;
		dequotenize(&type_list);
		pipeline = struct_cmd(&type_list);
		change_heredoc(&pipeline);
		if (count_pipe(&pipeline) == 1 && \
			is_built_in(pipeline->simple_cmd) > -1)
		{
			if (init_redir(pipeline) == 1)
			{
				unlink_temp_files(pipeline);
				exit(1);
			}
			run_cmd(pipeline, &environ, is_built_in(pipeline->simple_cmd), 1);
		}
		else
			pipexline(&pipeline, &environ);
		ft_cmdclear(&pipeline, free);
		ft_tokenclear(&type_list, free);
	}
}
