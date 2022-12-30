/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:57:39 by ggiannit          #+#    #+#             */
/*   Updated: 2022/12/30 17:21:00 by ggiannit         ###   ########.fr       */
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



/*void ft_execvp(char *cmd_str, char **envp)
{
	char **cmd_mat;
	char *full_path;

	cmd_mat = ft_split(cmd_str, ' ');
	full_path = ft_getenv("PATH", envp);
	full_path = ft_getpath(full_path, cmd_mat[0]);
	if (!full_path)
		return ;
	if (!fork())
		execve(full_path, cmd_mat, NULL);
	wait(NULL);
	ft_free_null(&full_path);
	ft_free_matrix(cmd_mat);
}*/

void	ft_do_exec(char **cmd, char *file, int *pp, int is_main)
{
	int	fd_file;

	if (!fork())
	{
		if (is_main)
		{
			fd_file = open(file, O_WRONLY| O_TRUNC);
			ft_redirect(pp[0], fd_file, pp[1]);
		}
		else
		{
			fd_file = open(file, O_RDONLY);
			ft_redirect(fd_file, pp[1], pp[0]);
		}
		execve(cmd[0], cmd, NULL);
		ft_close_4(pp[0], pp[1], fd_file, -1);
	}
	ft_close_4(pp[0], pp[1], -1, -1);
	wait(NULL);
	ft_free_matrix(cmd);
}

int	main(int ac, char **av, char **envp)
{
	int	pp[2];
	char **cmd;

	if (ac < 4)
		return (1);
	pipe(pp);
	if(!fork())
	{
		cmd = ft_getcmd(av[2], envp);
		ft_do_exec(cmd, av[1], pp, 0);
		/*if (!fork())
		{
			fd_in = open(av[1], O_RDONLY);
			ft_redirect(fd_in, pp[1], pp[0]);
			execve(cmd[0], cmd, NULL);
			ft_close_4(pp[1], fd_in, -1, -1);
		}
		ft_close_4(pp[0], pp[1], -1, -1);
		wait(NULL);
		ft_free_matrix(cmd);*/
	}
	else
	{
		wait(NULL);
		cmd = ft_getcmd(av[3], envp);
		ft_do_exec(cmd, av[4], pp, 1);
		/*if (!fork())
		{
			fd_out = open(av[4], O_WRONLY| O_TRUNC);
			ft_redirect(pp[0], fd_out, pp[1]);
			execve(cmd[0], cmd, NULL);
			ft_close_4(pp[0], fd_out, -1, -1);
		}
		ft_close_4(pp[0], pp[1], -1, -1);
		wait(NULL);
		ft_free_matrix(cmd);*/
	}
}

/*int main(int argc, char **argv, char **envp)
{
	if (argc < 2)
		return (1);
	//Print the command-line arguments
	//printf("argc: %d\n", argc);
	//for (int i = 0; i < argc; i++)
	//	ft_printf("argv[%d]: %s\n", i, argv[i]);
	// Print the environment variables
	//for (int i = 0; envp[i]; i++)
	//		printf("%s\n", envp[i]);
	//ft_printf("\n");
	//lol = ft_getenv(argv[1], envp);
	//ft_printf("%s\n", lol);
	//ft_printf("\n");
	ft_execvp(argv[1], envp);
    return 0;
}*/
