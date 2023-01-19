/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_basics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 03:53:52 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/19 16:40:31 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *s1, int n)
{
	char	*cp;
	int		len;

	len = 0;
	while (s1[len] && (len < n || n < 0))
		len++;
	cp = malloc(sizeof(*cp) * (len + 1));
	if (!cp)
		return (ft_puterror(FAILED_MALLOC, (char *)"ft_strndup"));
	len = 0;
	while (s1[len] && (len < n || n < 0))
	{
		cp[len] = s1[len];
		len++;
	}
	cp[len] = '\0';
	return (cp);
}

void	*init_rpn_aux(t_rpn *rpn, char *to_parse)
{
	if (!ft_lstappendcopy(&rpn->specials, rpn->operators))
		return (ft_puterror(FAILED_MALLOC, (char *)"init_rpn append ops"));
	if (!ft_lstappendcopy(&rpn->specials, rpn->parenthesis))
		return (ft_puterror(FAILED_MALLOC, (char *)"init_rpn append prths"));
	rpn->blanks = ft_strndup(" \t\v", 3);
	if (!rpn->blanks)
		return (ft_puterror(FAILED_MALLOC, (char *)"init_rpn blanks"));
	rpn->s = to_parse;
	return (rpn->blanks);
}

void	*init_rpn(t_rpn *rpn, char *to_parse)
{
	t_list	*tmp;

	ft_memset(rpn, 0, sizeof(*rpn));
	tmp = ft_lstnew_rpn(ft_strndup(")", -1), 0);
	if (!tmp)
		return (ft_puterror(FAILED_MALLOC, (char *)"init_rpn ')'"));
	ft_lstadd_front(&rpn->parenthesis, tmp);
	tmp = ft_lstnew_rpn(ft_strndup("(", -1), 0);
	if (!tmp)
		return (ft_puterror(FAILED_MALLOC, (char *)"init_rpn '('"));
	ft_lstadd_front(&rpn->parenthesis, tmp);
	tmp = ft_lstnew_rpn(ft_strndup("&&", -1), 1);
	if (!tmp)
		return (ft_puterror(FAILED_MALLOC, (char *)"init_rpn '&&'"));
	ft_lstadd_front(&rpn->operators, tmp);
	tmp = ft_lstnew_rpn(ft_strndup("||", -1), 1);
	if (!tmp)
		return (ft_puterror(FAILED_MALLOC, (char *)"init_rpn '||'"));
	ft_lstadd_front(&rpn->operators, tmp);
	return (init_rpn_aux(rpn, to_parse));
}


void	free_rpn(t_rpn *rpn)
{
	// out, ops, parenthesis, operators, specials OK
	// quid de check et current ?
	ft_lstclear(&rpn->out, &free);
	ft_lstclear(&rpn->ops, &free);
	ft_lstclear(&rpn->parenthesis, &free);
	ft_lstclear(&rpn->operators, &free);
	ft_lstclear(&rpn->specials, &free);
}

char	*invert_quotes(char *s)
{
	int		i;
	char	c;

	i = 0;
	while (s[i])
	{
		c = s[i];
		if (c == '\"' || c == '\'')
		{
			i++;
			while (s[i] && s[i] != c)
				s[i++] *= -1;
		}
		else
			i++;
	}
	return (s);
	// a voir pour inverser seulement les espaces + \t + \v
	// faudra le faire a part car mon parsing peut se prendre les
	// pieds dans le tapis sinon
}

t_rpn	*rpn(t_rpn *rpn, char *str)
{
	if (str == NULL)
		return (NULL);
	else
	{
		invert_quotes(str);
		generate_rpn(rpn, str);
		return (rpn);
	}
}

int	main(int ac, char **av)
{
	t_rpn	*rpn_var;

	rpn_var = malloc(sizeof(*rpn_var));
	if (ac >= 2)
		rpn(rpn_var, av[1]);
	free(rpn_var);
}
