/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 05:51:56 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/16 05:55:05 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_puterror(int flag)
{
	if (flag & FAILED_MALLOC)
		ft_putstr_fd("Malloc failed\n", STDERR_FILENO);
	return (NULL);
}