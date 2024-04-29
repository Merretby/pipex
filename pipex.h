/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:24:22 by moer-ret          #+#    #+#             */
/*   Updated: 2024/04/26 12:28:21 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_list
{
	char	**arg;
	char	*line;
}	t_list;

void	check(int ac, char **av);
char	*ft_strchr(const char *str, int c);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);
void	ft_error(char *str, int *fd);
void	error(char *str, t_list *par, char **path);
void	ft_putestr(char *str);
void	ft_free(char **fr);
void	execute(char *av, char **env, t_list *par);
void	child(char **av, char **env, t_list *par, int *fd);
void	child2(char **av, char **env, t_list *par, int *fd);

#endif