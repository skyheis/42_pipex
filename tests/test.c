/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:09:08 by ggiannit          #+#    #+#             */
/*   Updated: 2022/12/21 19:45:46 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int		main(void)
{
	int arr[12] = { 10, 2, 4 , 2, 1 , 11, 12, 22, 0, 1, 2, 1};
	int fd[2];
	int cfd[2];
	int id;
	int sum;
	int sum_child;
	int	start;
	int	end;

	sum = 0;
	sum_child = 0;
	pipe(fd);
	pipe(cfd);
	id = fork();
	if (!id)
	{
		id = fork();
		wait(NULL);
		if (id)
		{
			start = sizeof(arr) / sizeof(int) / 3;
			end = start << 1;
			printf("im semi-cap my id is %i\n", id);
		}
		else
		{
			start = sizeof(arr) / sizeof(int) / 3 * 2;
			end = sizeof(arr) / sizeof(int);
			printf("im no-one my id is %i\n", id);
		}
	}
	else
	{
		start = 0;
		end = sizeof(arr) / sizeof(int) / 3;
		printf("im cap my id is %i\n", id);
	}

	while (start < end)
		sum += arr[start++];
	printf("for me sum is %i\n", sum);
	
	if (end == sizeof(arr) / sizeof(int))
	{
		close(fd[1]);
		close(fd[0]);
		close(cfd[0]);
		write(cfd[1], &sum, sizeof(sum));
		close(cfd[1]);
	}
	else if (wait(NULL) == -1)
	{
		close(cfd[1]);
		close(cfd[0]);
		close(fd[0]);
		write(fd[1], &sum, sizeof(sum));
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		close(cfd[1]);
		read(fd[0], &sum_child, sizeof(sum));
		close(fd[0]);
		sum += sum_child;
		read(cfd[0], &sum_child, sizeof(sum));
		close(cfd[0]);
		sum += sum_child;
		printf("final result is %i\n", sum);
	}
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
