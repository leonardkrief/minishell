/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 02:09:47 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/19 11:01:31 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblkriefft.h"

// char	*ft_strndup(const char *s1, int n)
// {
// 	char	*cp;
// 	int		len;

// 	len = 0;
// 	while (s1[len] && (len < n || n < 0))
// 		len++;
// 	cp = malloc(sizeof(*cp) * (len + 1));
// 	if (!cp)
// 		return (NULL);
// 	len = 0;
// 	while (s1[len] && (len < n || n < 0))
// 	{
// 		cp[len] = s1[len];
// 		len++;
// 	}
// 	cp[len] = '\0';
// 	return (cp);
// }
