/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spacestr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:54:00 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/18 02:17:24 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_iswhitespace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	str_isredirection(char *str)
{
	if (*str == '>' && *(str + 1) == '>')
		return (2);
	else if (*str == '<' && *(str + 1) == '<')
		return (2);
	else if (*str == '>')
		return (1);
	else if (*str == '<')
		return (1);
	else if (*str)
		return (-1);
	else
		return (0);
}

int	ft_spacestrlen(char *str)
{
	int	len;
	int	forward;

	len = 0;
	while (*str)
	{
		forward = str_isredirection(str);
		if (forward > 0)
		{
			len += forward;
			str += forward;
			if (*str && !ft_iswhitespace(*str))
				len++;
		}
		else if (forward < 0)
		{
			if (!ft_iswhitespace(*str)
				&& (*(str + 1) == '>' || *(str + 1) == '<'))
				len++;
			len++;
			str++;
		}
	}
	return (len);
}

void	ft_spacestr_treatment(char **addr_str, char *newstr, int *addr_i)
{
	int	i;
	int	forward;
	char	*str;

	i = *addr_i;
	str = *addr_str;
	forward = str_isredirection(str);
	if (forward > 0)
	{
		while (forward--)
			newstr[i++] = *(str++);
		if (*str && !ft_iswhitespace(*str))
			newstr[i++] = ' ';
	}
	else if (forward < 0)
	{
		newstr[i++] = *str;
		if (!ft_iswhitespace(*str)
			&& (*(str + 1) == '>' || *(str + 1) == '<'))
			newstr[i++] = ' ';
		str++;
	}
	*addr_i = i;
	*addr_str = str;
}

char	*ft_spacestr(char *str)
{
	int		i;
	int		forward;
	char	*newstr;

	if (!str)
		return (NULL);
	newstr = malloc(sizeof (*newstr) * (ft_spacestrlen(str) + 1));
	if (newstr == NULL) 
		return (ft_puterror(FAILED_MALLOC), NULL);
	i = 0;
	while (*str)
		ft_spacestr_treatment(&str, newstr, &i);
	return (newstr);
}
