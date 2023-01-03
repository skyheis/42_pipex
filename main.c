/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:57:39 by ggiannit          #+#    #+#             */
/*   Updated: 2023/01/03 14:00:31 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_do_exec(char **cmd, int fd_in, int fd_out)
{
	if (!fork())
	{
		ft_redirect(fd_in, fd_out, -1);
		execve(cmd[0], cmd, NULL);
		perror("I guess it doesn't exist.. am I right? error");
		close(fd_in);
		close(fd_out);
		exit(1);
	}
	close(fd_in);
	close(fd_out);
	wait(NULL);
	ft_free_matrix(cmd);
	return (1);
}

int	ft_pipez(int ac, char **av, char **envp, int fd_write)
{
	int		error;
	int		pp[2];
	char	**cmd;

	if (ac == 2)
	{
		pp[1] = -1;
		pp[0] = open(av[1], O_RDONLY);
	}
	else
	{
		pipe(pp);
		error = ft_pipez((ac - 1), av, envp, pp[1]);
		if (!error)
			return (ft_close_4(pp[1], pp[0], fd_write, -1));
	}
	if (pp[1] != -1)
		close(pp[1]);
	cmd = ft_getcmd(av[ac], envp);
	return (ft_do_exec(cmd, pp[0], fd_write));
}

int	main(int ac, char **av, char **envp)
{
	int	fd_out;
	int	error;

	if (ac < 5)
		return (1);
	fd_out = open(av[--ac], O_WRONLY| O_TRUNC | O_CREAT, 0644);
	if (fd_out == -1)
		return (1);
	error = ft_pipez((ac - 1), av, envp, fd_out);
	close(fd_out);
	if (!error)
		return (1);
	return (0);
}




/*int	main(int ac, char **av, char **envp)
{
	int	pp[2];
	char **cmd;
	//ac vale 5, meglio tenersi il valore okay
	//ne copio uno e e lo abbasso di 2, primo spot utile sara il 3 (ultimo cmd)
	//.  fai il pipe su cui il parent scrive
	//.  finche (copia > 1)	sforketta /parent/ abbasa di uno , legge dal pipe del children
	//.  e 
	
// porcamadonna devo fare un disegno mi sta fottendo la testa
	
	if (ac < 4)
		return (1);
	pipe(pp);
	if(!fork())
	{
		cmd = ft_getcmd(av[2], envp);
		ft_do_exec(cmd, av[1], pp, 0);
		//if (!fork())
		//{
		//	fd_in = open(av[1], O_RDONLY);
	//	//	ft_redirect(fd_in, pp[1], pp[0]);
	//		execve(cmd[0], cmd, NULL);
	//		ft_close_4(pp[1], fd_in, -1, -1);
	//	}
	//	ft_close_4(pp[0], pp[1], -1, -1);
	//	wait(NULL);
	//	ft_free_matrix(cmd);
	}
	else
	{
		wait(NULL);
		cmd = ft_getcmd(av[3], envp);
		ft_do_exec(cmd, av[4], pp, 1);
	//	if (!fork())
	//	{
	//		fd_out = open(av[4], O_WRONLY| O_TRUNC);
	//		ft_redirect(pp[0], fd_out, pp[1]);
	//		execve(cmd[0], cmd, NULL);
	//		ft_close_4(pp[0], fd_out, -1, -1);
	//	}
	//	ft_close_4(pp[0], pp[1], -1, -1);
	//	wait(NULL);
	//	ft_free_matrix(cmd);
	}
}*/





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
