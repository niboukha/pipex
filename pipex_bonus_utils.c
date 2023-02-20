/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 09:49:17 by niboukha          #+#    #+#             */
/*   Updated: 2023/02/20 21:06:24 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_slash(char *path)
{
	int	i;

	i = -1;
	while (path[++i])
	{
		if (path[i] == '/')
			return (1);
	}
	return (0);
}

char	*check_cmd(t_pipex *_pipex, char *cmd)
{
	char	*cmd_tmp;
	int		i;

	i = 0;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (_pipex->path[i])
	{
		cmd_tmp = ft_strjoin(_pipex->path[i], cmd);
		if (access(cmd_tmp, F_OK) == 0)
			return (cmd_tmp);
		free(cmd_tmp);
		i++;
	}
	if (check_slash(cmd) != 0)
		return (NULL);
	return (cmd);
}

void	exec_function(t_pipex *_pipex, char **av, char **_env)
{
	_pipex->cmd_arg = ft_split(av[_pipex->i], ' ');
	_pipex->cmd = check_cmd(_pipex, _pipex->cmd_arg[0]);
	if (!_pipex->cmd)
	{
		write(2, "no such file or directory1 \n", 29);
		exit(1);
	}
	if (execve(_pipex->cmd, _pipex->cmd_arg, _env) == -1)
	{
		write(2, "command not found \n", 20);
		exit(1);
	}
}

void	close_pipe(t_pipex *_pipex)
{
	close(_pipex->fd[0]);
	close(_pipex->fd[1]);
}

void	handling_pipes(t_pipex *_pipex, int ac, char **av, char **_env)
{
	dup2(_pipex->infile, 0);
	close(_pipex->infile);
	dup2(_pipex->outfile, 1);
	close(_pipex->outfile);
	while (_pipex->i < ac - 1)
	{
		if (pipe(_pipex->fd) == -1)
		{
			perror("error");
			exit (1);
		}
		if (!fork())
		{
			if (_pipex->i < ac - 2)
				dup2(_pipex->fd[1], 1);
			close_pipe(_pipex);
			exec_function(_pipex, av, _env);
		}
		dup2(_pipex->fd[0], 0);
		close_pipe(_pipex);
		_pipex->i++;
	}
}
