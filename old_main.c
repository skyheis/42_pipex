/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:57:39 by ggiannit          #+#    #+#             */
/*   Updated: 2022/12/28 16:28:53 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*char ***ft_convert_cmd(int ac, char **av)
{
	char ***allcmd;
	int	k;

	k = 0;
	allcmd = (char ***) ft_calloc((ac - 2), sizeof(char *));
	ac -= 3;
	while (k < ac)
	{
		allcmd[k] = ft_split(av[k + 2] , ' ');
		k++;
	}
	allcmd[k] = NULL;
	return (allcmd);
}*/

void ft_execve(char *cmd_str)
{
	char **cmd_mat;

	cmd_mat = ft_split(cmd_str, ' ');
	execve(cmd_mat[0], cmd_mat, NULL);
}

int	**ft_pipe_mat(int ac)
{
	int	**pp;
	int	i;

	i = 0;
	ac -= 4;
	pp = (int **) ft_calloc(ac + 1, sizeof(int *));
	pp[ac] = NULL;
	while (ac--)
		pp[i++] = (int *) ft_calloc(2, sizeof(int));
	return (pp);
}

void	ft_is_child(int ac, char **av, int **pp)
{
	int fd_in;

	dup2(*pp[1], 1);
	if (ac == 5)
	{
		fd_in = open(av[1], O_RDONLY);
		dup2(fd_in, 0);
		ft_execve(av[ac - 3]);
	}
	else
	{
		pp++;
		pipe(*pp);
		if(!fork())
			ft_is_child(ac--, av, pp);
		else
		{
			wait(NULL);
			dup2(*pp[0], 0);
			ft_execve(av[ac - 2]);
		}
	}
}

int	main(int ac, char **av)
{
	int	**pp;

	if (ac < 4)
		return (1);
	pp = ft_pipe_mat(ac);
	pipe(*pp);
	if(!fork())
		ft_is_child(ac, av, pp);
}
//	fd_in = open(av[1], O_RDONLY);
