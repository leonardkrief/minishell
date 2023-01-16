/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 05:02:23 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/16 07:10:07 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// comme on peut export des nouvelles variables, la taille de ev
// ets susceptible de changer au cours de minishell donc on devra
// potentiellement realloc/free.
// Pour pas se prendre la tete, des qu'on lance minishell, on copie
// ev dans une variable a nous quon modifiera ensuite comme on  veut
// Pour plus de simplicité, on aurait pu utiliser une liste chainee
// mais jai vu que tu fais deja a appelle a ev pas mal donc je vais 
// rester sur un tableau

#include "minishell.h"

char	**ft_copy_tab(char **tab)
{
	char	**new_tab;
	int		i;

	if (!tab)
		return (NULL);
	new_tab = malloc(sizeof(*new_tab) * (ft_strlen(tab) + 1));
	if (!new_tab)
		return (ft_puterror(FAILED_MALLOC));
	i = -1;
	while (tab[++i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (new_tab[i] == NULL)
		{
			ft_puterror(FAILED_MALLOC);
			return (ft_free_tab(new_tab, i));
		}
	}
	new_tab[i] = NULL;
	return (new_tab);
}

// sets a new ev tab by copying the first len elems while non-NULL
// and not copy the elem nb index
// if there are null elems found before len elem, then we will still 
// have allocated more mem, in case we need to add to ev
// it wont copy the elem nb index of ev, in case we need to
// delete from ev
// this function can take care of both export and unset

char	**regenerate_ev(int len, int index, char **ev)
{
	char	**my_ev;
	int		i;

	if (!ev)
		return (NULL);
	my_ev = malloc(sizeof(*my_ev) * (len + 1));
	if (!my_ev)
		return (ft_puterror(FAILED_MALLOC));
	i = -1;
	while (ev[++i] && i < len)
	{
		if (i != index)
		{
			my_ev[i] = ft_strdup(ev[i]);
			if (my_ev[i] == NULL)
			{
				ft_puterror(FAILED_MALLOC);
				return (ft_free_tab(my_ev, i));
			}
		}
	}
	my_ev[len] = NULL;
	ft_free_tab(ev, -1);
	return (my_ev);
}

int	ft_ev_getvar(char *var, char **ev)
{
	int	i;
	int	len;

	if (ev == NULL || var == NULL)
		return (-1);
	len = ft_strlen(var);
	i = 0;
	while (ev[i])
	{
		if (!ft_strncmp(var, ev[i], len) && !ft_strncmp("=", ev[i][len], 1))
			break;
		i++;
	}
	if (ev[i])
		return (i);
	else
		return (-1);
}

char	*ft_ev_setvar(char *var, char *str, char ***addr_ev)
{
	int		n;
	char	*tmp;
	char	**ev;

	ev = *addr_ev;
	n = ft_evexists(var, ev);
	if (n < 0)
	{
		n = ft_strlen(ev) + 1;
		*addr_ev = regenerate_ev(n + 1, -1, ev);
		if (!ev)
			return (NULL);
	}
	free(ev[n]);
	tmp = ft_strjoin_lkrief(var, "=");
	ev[n] = ft_strjoin_lkrief(tmp, str);
	if (!tmp || !ev[n])
		return (ft_puterror(FAILED_MALLOC));
	free(tmp);
	return (ev[n]);
}