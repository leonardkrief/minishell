/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:47:54 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/16 07:24:02 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_swap(char **tab, int i, int j)
{
	char	*tmp;

	tmp = tab[i];
	tab[i] = tab[j];
	tab[j] = tmp;
}

char	**ft_sorted_ev(char **ev)
{
	int	i;
	int	j;
	int	len;

	len = 0;
	while (ev && ev[len])
		len++;
	i = 1;
	while (i < len - 1)
	{
		j = 1;
		while (j < len - i)
		{
			if (ft_strcmp(ev[j], ev[j + 1]) > 0)
				ft_swap(ev, j, j + 1);
			j++;
		}
		i++;
	}
	return (ev);
}

int	ft_display_ordered_ev(char **ev)
{
	int		i;
	char	**ev;

	ev = ft_sorted_ev(ev);
	i = -1;
	while (ev && ev[i])
		printf("%s\n", ev[i]);
	return (1);
}

int	ft_export(char **av, char ***addr_ev)
{
	int	i;
	char *str;

	if (*addr_ev)
		return (-1);
	if (av && av[0] == NULL)
		return (ft_display_ordered_ev(*addr_ev));
	else
	{
		i = -1;
		while (av[++i])
		{
			str = ft_strchr(av[i], '=');
			if (str)
				*str = '\0';
			if (!ft_ev_setvar(av[i], str + 1, addr_ev))
				return (-1);
		}
	}
	return (0);
}