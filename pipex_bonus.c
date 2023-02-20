/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:29:52 by niboukha          #+#    #+#             */
/*   Updated: 2023/02/20 20:48:53 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**check_path(char **_env)
{
	int	i;

	i = 0;
	while (_env[i])
	{
		if (ft_strncmp("PATH=", _env[i], 5) == 0)
			return (ft_split(_env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

void	open_files(int ac, t_pipex *_pipex, char **av)
{
	_pipex->infile = open(av[1], O_RDONLY);
	if (_pipex->infile < 0)
	{
		perror("error");
		_pipex->i++;
	}
	_pipex->outfile = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (_pipex->outfile < 0)
		perror("error");
}

int	main(int ac, char **av, char **_env)
{
	t_pipex	_pipex;

	_pipex.i = 2;
	if (ac < 5)
	{
		write(2, "Error: incorrect number of arguments \n", 39);
		exit(1);
	}
	_pipex.path = check_path(_env);
	open_files(ac, &_pipex, av);
	handling_pipes(&_pipex, ac, av, _env);
	while (wait(NULL) != -1)
		;
	return (0);
}
