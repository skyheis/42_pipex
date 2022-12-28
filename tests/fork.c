/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:03:09 by ggiannit          #+#    #+#             */
/*   Updated: 2022/12/21 18:50:35 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

// fork: fork the executrion line
//	bork a new child process, so the code will work 
//	id is 0 for the child
//	id is n for the parent
//
// wait: wait when at least one child be over
//		it return -1 if there is nothing to wait for
//		if (wait(NULL) != -1 || errno != ECHILD)
//
// getpid
// getppid -> if the parent is over, the parent will be asigned to a new process

int	main(void)
{
	int id;
	int pp;

	id = fork();
	pp = wait(NULL);
	if (id)
		printf("im in and pp is %i and id is %i also my p is %i\n", pp, getpid(), getppid());
	else
		printf("im out and pp is %i and id is %i also my p is %i\n", pp, getpid(), getppid());
}

/*int	main(void)
{
	int id;

	id = fork();
	if (id)
	{
		id = fork();
		if (!id)
			printf("fdf %d\n", id);
		else
			printf("lol %d\n", id);
	}
	else
		printf("pdp %d\n", id);
}*/
