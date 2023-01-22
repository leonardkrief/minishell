/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 05:02:23 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/22 06:23:53 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// comme on peut export des nouvelles variables, la taille de ev
// ets susceptible de changer au cours de minishell donc on devra
// potentiellement realloc/free.
// Pour pas se prendre la tete, des qu'on lance minishell, on copie
// ev dans une variable a nous quon modifiera ensuite comme on  veut
// Pour plus de simplicité, on aurait pu utiliser une liste chainee
// mais jai vu que tu fais deja appelle a ev pas mal donc je vais 
// rester sur un tableau

#include "minishell.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_swap_ev(char **tab, int i, int j)
{
	char	*tmp;

	tmp = tab[i];
	tab[i] = tab[j];
	tab[j] = tmp;
}
