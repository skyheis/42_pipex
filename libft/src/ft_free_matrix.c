/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:19:48 by ggiannit          #+#    #+#             */
/*   Updated: 2022/12/30 12:20:09 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_free_matrix(char **matrix)
{
	int i;

	i = 0;
	while (matrix[i])
		ft_free_null(&matrix[i++]);
	free(matrix);
	return (NULL);
}
