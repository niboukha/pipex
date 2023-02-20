/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 20:16:12 by niboukha          #+#    #+#             */
/*   Updated: 2023/02/12 18:31:53 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*m;
	unsigned char	*m1;
	size_t			i;

	m = (unsigned char *)s1;
	m1 = (unsigned char *)s2;
	i = 0;
	while (i < n && (m[i] || m1[i]) && (m[i] == m1[i]))
		i++;
	if (i < n)
		return (m[i] - m1[i]);
	else
		return (0);
}
