/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:03:09 by ggiannit          #+#    #+#             */
/*   Updated: 2023/01/03 22:15:46 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

//redirect stdout 0 to fd[1] di pipe

int	main(void)
{
	char *av[] = {"/bin/catt", NULL};
	//char *aw[] = {"/usr/bin/wc", NULL};
	int	fd;
	int pp[2];
	int ppp;
	int err;
	int id;

	fd = open("lol", O_RDONLY);
	pipe(pp);
	id = fork();
	if (!id)
	{
		ppp = dup(1);
		dup2(fd, 0);
		dup2(pp[1], 1);
		err = execve(av[0], av, NULL);
		perror("dale");
		exit(err);
	}
	else
	{
		usleep(100);
		waitpid(id, &err, WNOHANG);
		printf("err is %i\n", err);
		close(pp[1]);
		close(pp[0]);
		close(fd);
	}
}

/*int	main(void)
{
	char *av[] = { "/bin/echo", "ciaoo", NULL};
	char *mall;
	int pp[2];
	int i = 0;
	int	fd;

	mall = (char *) malloc(6 * sizeof(char));
	mall[5] = '\0';
	pipe(pp);
	if (!fork())
	{
		dup2(pp[1], 1);
		execve(av[0], av, NULL);
		close(pp[1]);
		close(pp[0]);
	}
	else
	{
		wait(NULL);
		close(pp[1]);
		read(pp[0], mall, 5);
		close(pp[0]);
		fd = open("lol", O_WRONLY);
		while (mall[i] != '\0')
			write(fd, &mall[i++], 1);
		close(fd);
		free(mall);
	}
}*/

/*int	main(void)
{
	char *av[] = { "/bin/echo", "ciaoo", NULL};
	
	fork 
	execve(av[0], av, NULL);
	printf("e viaa");
}*/
