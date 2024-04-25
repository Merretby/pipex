/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:33:32 by moer-ret          #+#    #+#             */
/*   Updated: 2024/04/25 14:48:12 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *av, char **env, t_list *par)
{
	char *str;
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
		if (ft_strchr(par->arg[0], '/') == NULL)
		{
			dprintf(2,"mafiya slash \n");
			str = ft_strjoin("/", par->arg[0]);
			par->line = ft_strjoin(path[i], str);
			free (str);
			if (access(par->line, F_OK) == 0)
			{
				printf("found it now breaking \n");
				break ;
			}
			free(par->line);
		}
		else
		{
			dprintf(2,"fiya slash \n");
			if (access(par->arg[0], F_OK | X_OK) == 0)
			{
				if (execve(par->arg[0], par->arg, env) == -1)
				{
					// free(par->line);
					ft_free(path);
					ft_free(par->arg);
					ft_error("invalid path");
					// exit(0);
			
				}
			}
		}
		i++;
		printf("1->%p\n", par->line);
	}
	dprintf(2,"akhir haja => %s \n",par->line);
	if (execve(par->line, par->arg, env) == -1)
	{
		// free (par->line);
		ft_free(path);
		ft_free(par->arg);
		dprintf(2,"ana f execve \n");
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
