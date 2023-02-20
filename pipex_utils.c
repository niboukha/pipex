/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 09:43:33 by niboukha          #+#    #+#             */
/*   Updated: 2023/02/20 10:32:24 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		if (access(cmd_tmp, X_OK) == 0)
			return (cmd_tmp);
		free(cmd_tmp);
		i++;
	}
	if (check_slash(cmd) != 0)
		return (NULL);
	return (cmd);
}

void	first_child(t_pipex *_pipex, char *av[], char *_env[])
{
	_pipex->infile = open(av[1], O_RDONLY);
	if (_pipex->infile < 0)
	{
		perror("error");
		exit(1);
	}
	_pipex->cmd_arg = ft_split(av[2], ' ');
	_pipex->cmd = check_cmd(_pipex, _pipex->cmd_arg[0]);
	if (!_pipex->cmd)
	{
		write(2, "no such file or directory \n", 28);
		exit(1);
	}
	dup2(_pipex->_pipe[1], 1);
	dup2(_pipex->infile, 0);
	close(_pipex->_pipe[0]);
	close(_pipex->_pipe[1]);
	close(_pipex->infile);
	if (execve(_pipex->cmd, _pipex->cmd_arg, _env) == -1)
	{
		write(2, "command not found \n", 20);
		exit(1);
	}
}

void	second_child(t_pipex *_pipex, char *av[], char *_env[])
{
	_pipex->outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (_pipex->outfile < 0)
	{
		perror("error");
		exit(1);
	}
	_pipex->cmd_arg = ft_split(av[3], ' ');
	_pipex->cmd = check_cmd(_pipex, _pipex->cmd_arg[0]);
	if (!_pipex->cmd)
	{
		write(2, "no such file or directory \n", 28);
		exit(1);
	}
	dup2(_pipex->_pipe[0], 0);
	dup2(_pipex->outfile, 1);
	close(_pipex->_pipe[1]);
	close(_pipex->_pipe[0]);
	close(_pipex->outfile);
	if (execve(_pipex->cmd, _pipex->cmd_arg, _env) == -1)
	{
		write(2, "command not found \n", 20);
		exit(1);
	}
}

char	**check_path(char **_env)
{
	int		i;

	i = 0;
	while (_env[i])
	{
		if (ft_strncmp("PATH=", _env[i], 5) == 0)
			return (ft_split(_env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}
