/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:33:32 by moer-ret          #+#    #+#             */
/*   Updated: 2024/04/25 13:26:43 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *av, char **env, t_list *par)
{
	char	**path;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	path = ft_split(env[i] + 5, ':');
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
		else
		{
			if (access(par->arg[0], F_OK | X_OK) == 0)
			{
				if (execve(par->arg[0], par->arg, env) == -1)
				{
					int j = 0;
					free(par->line);
					printf("1->%p\n", par->line);
					ft_free(path);
					while (path[j])
					{
						printf("2->%p\n", path[j]);
						printf("\n");
						j++;
					}
					j = 0;
					ft_free(par->arg);
					while (par->arg[j])
					{
						printf("3->%p\n", par->arg[j]);
						printf("\n");
						j++;
					}
					ft_error("invalid path");
				}
			}
		}
		i++;
		free (par->line);
		printf("1->%p\n", par->line);
	}
	if (execve(par->line, par->arg, env) == -1)
	{
		int j = 0;
		ft_free(path);
		while (path[j])
		{
			printf("2---->%p", path[j]);
			printf("\n");
			j++;
		}
		j = 0;
		ft_free(par->arg);
		while (par->arg[j])
		{
			printf("3---->%p\n", par->arg[j]);
			printf("\n");
			j++;
		}
		ft_error("invalid path");
	}
}

void	child(char **av, char **env, t_list *par, int *fd)
{
	int	file;

	if (access(av[1], R_OK) == -1)
		ft_error("permission denied");
	file = open(av[1], O_RDONLY, 0777);
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	dup2(file, 0);
	close(file);
	execute (av[2], env, par);
}

void	child2(char **av, char **env, t_list *par, int *fd)
{
	int	file;

	file = 0;
	if (access(av[4], F_OK) == -1)
		file = open(av[4], O_WRONLY | O_CREAT, 0777);
	else if (access(av[4], W_OK) == -1)
		ft_error("permission denied");
	else
		file = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	dup2(file, 1);
	close(file);
	execute (av[3], env, par);
}

int	main(int ac, char **av, char **env)
{
	t_list	par;
	int		fd[2];

	if (ac != 5)
		ft_error("U NEED 5 ARGUMENT");
	if (av[2][0] == '\0' || av[2][0] == '\\' || av[2][0] == '\t'\
		|| av[2][0] == ' ' || av[2][0] == '.' || av[3][0] == '\0'\
		|| av[3][0] == '\\' || av[3][0] == '\t'|| av[3][0] == ' '\
		|| av[3][0] == '.')
		ft_error("ERROR");
	if (pipe(fd) == -1)
		exit (1);
	if (fork() == 0)
		child(av, env, &par, fd);
	else
	{
		if (fork() == 0)
		{
			child2(av, env, &par, fd);
			wait(NULL);
		}
	}
}
