/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:42:17 by moer-ret          #+#    #+#             */
/*   Updated: 2024/04/26 20:14:39 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check(int ac, char **av)
{
	if (ac != 5)
		ft_putestr("U NEED 5 ARGUMENT");
	if (av[2][0] == '\0' || av[3][0] == '\0')
		ft_putestr("ERROR");
}

void	ft_free(char **fr)
{
	size_t	i;

	i = 0;
	while (fr[i])
	{
		free(fr[i]);
		i++;
	}
	free (fr);
}

void	error(char *str, t_list *par, char **path)
{
	ft_free(path);
	ft_free(par->arg);
	ft_putestr(str);
	exit(1);
}

void	ft_error(char *str, int *fd)
{
	close(fd[0]);
	close(fd[1]);
	ft_putestr(str);
	exit(1);
}

void	ft_putestr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	write (2, "\n", 1);
}
