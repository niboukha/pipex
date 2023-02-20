/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:46:40 by niboukha          #+#    #+#             */
/*   Updated: 2023/02/20 12:03:48 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **_env)
{
	t_pipex	_pipex;

	if (ac != 5)
	{
		write(2, "Error: incorrect number of arguments \n", 39);
		exit(1);
	}
	if (pipe(_pipex._pipe) == -1)
	{
		perror("error");
		exit (1);
	}
	_pipex.path = check_path(_env);
	if (!fork())
		first_child(&_pipex, av, _env);
	if (!fork())
		second_child(&_pipex, av, _env);
	close(_pipex._pipe[0]);
	close(_pipex._pipe[1]);
	while (wait(NULL) != -1)
		;
	return (0);
}
