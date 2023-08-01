#include "minishell.h"

int	is_invalid_key(int c)
{
	return (c == '!' || c == ' ' || c == '\\'
		|| c == '?' || c == '\'' || c == '\"');
}

int	print_export_err(char *str)
{
	ft_putstr_fd("minishell: export: \'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	return (0);
}

int	is_valid_export_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isdigit(str[0]))
			return (print_export_err(str));
		if (is_invalid_key(str[i]))
			return (print_export_err(str));
		++i;
	}
	if (i == 1)
		return (print_export_err(str));
	return (1);
}

void	ft_export(char **simple_cmd, t_list **environ, int *status)
{
	char	**tmp;
	int		i;

	i = 0;
	while (simple_cmd[++i])
	{
		if (is_valid_export_arg(simple_cmd[i]))
		{
			ft_lstadd_back(environ, ft_lstnew(ft_strdup(simple_cmd[1])));
			*status = 0;
		}
		else
			*status = 1;
	}
}

/**
 * 1. no '=' in simple_cmd[1]
 * 2. starts with number -> "bash: export: `1=value': not a valid identifier"
 * 3. contains " \?!$" in key -> "bash: export: `key!=value': not a valid identifier"
 * 4. no key -> "bash: export: `=value': not a valid identifier"
 * export can take multiple arguments
*/
