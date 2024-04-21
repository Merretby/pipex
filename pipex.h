/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:24:22 by moer-ret          #+#    #+#             */
/*   Updated: 2024/04/21 14:14:52 by moer-ret         ###   ########.fr       */
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

char	*ft_strchr(const char *str, int c);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);

#endif