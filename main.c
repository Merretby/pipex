/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:33:32 by moer-ret          #+#    #+#             */
/*   Updated: 2024/04/21 17:15:09 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *av, char **env, t_list *par)
{
	char	*str;
	char	**path;
	int		i;

	i = 0;
	while (env[i])
	{
		str = ft_strchr(env[i++], 'P');
		if (ft_strncmp(str, "PATH=", 5) == 0)
			break ;
	}
	path = ft_split(str + 5, ':');
	par->arg = ft_split(av, ' ');
	i = 0;
	while (path[i] && par->arg)
	{
		if (!ft_strchr(par->arg[0], '/'))
		{
			par->line = ft_strjoin("/", par->arg[0]);
			par->line = ft_strjoin(path[i], par->line);
			if (access(par->line, F_OK) == 0)
				break ;
		}
		i++;
	}
	if (execve(par->line, par->arg, env) == -1)
		exit(1);
}

void	child(char **av, char **env, t_list *par, int *fd)
{
	int	file;

	file = open(av[1], O_RDONLY);
	dup2(fd[1], 1);
	dup2(file, 0);
	execute (av[2], env, par);
}

void	child2(char **av, char **env, t_list *par, int *fd)
{
	int	file;

	file = open(av[4], O_WRONLY | O_CREAT, 0777);
	dup2(fd[0], 0);
	dup2(file, 1);
	execute (av[3], env, par);
}

int	main(int ac, char **av, char **env)
{
	t_list	par;
	int		fd[2];
	int		ip2;
	int		ip;

	if (ac == 5)
	{
		if (pipe(fd) == -1)
			exit (1);
		ip = fork();
		if (ip == 0)
			child(av, env, &par, fd);
		else
		{
			ip2 = fork();
			if (ip2 == 0)
			{
				child2(av, env, &par, fd);
				wait(NULL);
			}
		}
	}
}
