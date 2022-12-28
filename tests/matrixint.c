/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:09:08 by ggiannit          #+#    #+#             */
/*   Updated: 2022/12/28 15:58:48 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int		main(void)
{
	int *fd[2];

	fd = (int *) malloc(4 * sizeof(int *));
}


/*int main()
{
	int fd[2];
	int x = 10;
	int c;

	pipe(fd);
	write(fd[1], &x, sizeof(int));
	read(fd[0], &c, sizeof(int));
	close(fd[0]);
	close(fd[1]);
	printf("%d", c);
}*/
