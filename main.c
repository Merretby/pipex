/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:33:32 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/02 11:55:06 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	case1(t_list *par, char **env, char **path)
{
	if (execve(par->line, par->arg, env) == -1)
		error("command not found", par, path);
}

void	case2(t_list *par, char **env, char **path)
{
	if (access(par->arg[0], F_OK | X_OK) == 0)
		execve(par->arg[0], par->arg, env);
	else
		error("command not found", par, path);
}

char	*path_check(char **env, char *av)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	j = 0;
	while (av[j])
	{
		if (av[j] == '\t')
			av[j] = ' ';
		j++;
	}
	return (env[i]);
}

void	execute(char *av, char **env, t_list *par)
{
	char	*str;
	char	**path;
	int		i;

	i = 0;
	str = path_check(env, av);
	path = ft_split(str + 5, ':');
	par->arg = ft_split(av, ' ');
	while (path[i] && par->arg)
	{
		if (ft_strchr(par->arg[0], '/') == NULL)
		{
			str = ft_strjoin("/", par->arg[0]);
			par->line = ft_strjoin(path[i], str);
			free (str);
			if (access(par->line, F_OK) == 0)
				break ;
			free(par->line);
		}
		else
			case2(par, env, path);
		i++;
	}
	if (ft_strchr(par->arg[0], '/') == NULL)
		case1(par, env, path);
}

int	main(int ac, char **av, char **env)
{
	t_list	par;
	int		fd[2];
	int		ip1;
	int		ip2;

	check(ac, av);
	if (pipe(fd) == -1)
		exit (1);
	ip1 = fork();
	if (ip1 == -1)
		ft_putestr("error in fork ip1");
	if (ip1 == 0)
		child(av, env, &par, fd);
	if (ip1 != 0)
	{
		ip2 = fork();
		if (ip2 == -1)
			ft_putestr("error in fork ip2\n");
		if (ip2 == 0)
			child2(av, env, &par, fd);
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
}
