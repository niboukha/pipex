/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 09:01:51 by niboukha          #+#    #+#             */
/*   Updated: 2023/02/20 10:32:24 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

typedef struct t_pipex
{
	int		_pipe[2];
	int		pid1;
	int		pid2;
	int		infile;
	int		outfile;
	char	**path;
	char	*cmd;
	char	**cmd_arg;
}		t_pipex;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	**check_path(char **_env);
char	*check_cmd(t_pipex *_pipex, char *cmd);
int		check_slash(char *path);
void	first_child(t_pipex *_pipex, char *av[], char *_env[]);
void	second_child(t_pipex *_pipex, char *av[], char *_env[]);

#endif