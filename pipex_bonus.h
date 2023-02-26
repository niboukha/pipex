/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:30:07 by niboukha          #+#    #+#             */
/*   Updated: 2023/02/22 10:16:19 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	int		fd[2];
	int		pid1;
	int		pid2;
	int		i;
	int		outfile;
	int		infile;
	char	**cmd_arg;
	char	**path;
	char	*cmd;
}			t_pipex;

char	**check_path(char **_env);
void	exec_function(t_pipex *_pipex, char **av, char **_env);
void	open_files(int ac, t_pipex *_pipex, char **av);
void	close_pipe(t_pipex *_pipex);
void	handling_pipes(t_pipex *_pipex, int ac, char **av, char **_env);
char	*check_cmd(t_pipex *_pipex, char *cmd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);

#endif