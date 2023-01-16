/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:47:54 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/16 07:24:25 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// on doit gerer cd - et retourner au previous directory, comment faire ?
// cd --- donne en message d'erreur: "bash: cd: --: invalid option"
// il faut que j'expand les $ de str ou non ?

// $> unset HOME
// $> cd $HOME
// doit renvoyer
// bash: cd: HOME not set
// $>

char	*ft_getpath(char **av, char **ev)
{
	char	*new_pwd;

	if (av == NULL || av[0] == NULL)
		new_pwd = ft_expand(ft_strdup(getenv("HOME")), ev);
	else if (av && av[0] && av[1])
	{
		new_pwd = NULL;
		ft_putstr_fd("bash: cd: too many arguments\n", STDERR_FILENO);
	}
	else if (!ft_strcmp(av[0], "-"))
		new_pwd = ft_expand(ft_strdup(getenv("OLDPWD")), ev);
	else if (!ft_strcmp(av[0], "--"))
		new_pwd = ft_expand(ft_strdup(getenv("HOME")), ev);
	else if (!ft_strncmp(av[0], "~", 1))
		new_pwd = ft_expand(ft_strjoin(getenv("HOME"), av[0] + 1), ev);
	else if (!ft_strncmp(av[0], "--", 2))
	{
		new_pwd = NULL;
		ft_putstr_fd("bash: cd: --: invalid option\n", STDERR_FILENO);
	}
	else
		new_pwd = ft_expand(ft_strjoin("./", av[0]), ev);
	return (new_pwd);
}

int	change_directory(char *new_pwd, char **ev)
{
	char	*pwd;

	pwd = getcwd(0, NULL);
	if (chdir(new_pwd))
	{
		if (pwd)
		{
			ft_ev_setvar("OLDPWD", pwd, ev);
			free(pwd);
		}
		pwd = getcwd(0, NULL);
		if (pwd)
		{
			ft_ev_setvar("PWD", pwd, ev);
			free(pwd);
		}
		return (0);
	}
	else
		return (-1);
}

int	ft_cd(char **av, char **ev)
{
	char	*new_pwd;

	new_pwd = ft_getpath(av, ev);
	// if (new_pwd)
	// 	printf("new_pwd = %s\n", new_pwd);
	// else
	// 	printf("new_pwd = NULL");
	errno = 0;
	if (change_directory(new_pwd, ev) || errno)
	{
		ft_putstr_fd("bash: cd: ", STDERR_FILENO);
		ft_putstr_fd(av[0], STDERR_FILENO);
		if (errno == EACCES || errno == ENOENT)
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		else if (errno == ENOTDIR)
			ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
		else
			ft_putstr_fd(": Error changing directory\n", STDERR_FILENO);
		if (new_pwd)
			free(new_pwd);
		return (1);
	}
	if (new_pwd)
		free(new_pwd);
	return (0);
}

int	main(int ac, char **av, char **ev)
{
	ft_cd(av + 1, ev);
}