/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:57:39 by ggiannit          #+#    #+#             */
/*   Updated: 2023/01/04 21:38:41 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_do_exec(char **cmd, int fd_in, int fd_out, char **envp)
{
	int	stat;
	int	pid;
	int	pexit;

	pid = fork();
	if (!pid)
	{
		ft_redirect(fd_in, fd_out, -1);
		execve(cmd[0], cmd, envp);
		perror("ggiannit: command not found");
		ft_free_matrix(cmd);
		ft_close_n_ret(fd_in, fd_out, -1, -2);
		exit(127);
	}
	ft_close_n_ret(fd_in, fd_out, -1, -2);
	if (!ft_strncmp("cat", &(cmd[0][ft_strlen(cmd[0]) - 3]), 4))
		waitpid(pid, &stat, WNOHANG);
	else
		wait(&stat);
	pexit = WEXITSTATUS(stat);
	ft_free_matrix(cmd);
	return (pexit);
}

int	ft_pipez(int ac, char **av, char **envp, int fd_write)
{
	int		pp[2];
	char	**cmd;

	if (ac == 2)
	{
		pp[1] = -1;
		pp[0] = open(av[1], O_RDONLY);
	}
	else if (ac == 3 && !ft_strncmp("here_doc", av[1], 9))
	{
		pp[1] = -1;
		pp[0] = ft_get_heredoc(av[2]);
	}
	else
	{
		pipe(pp);
		ft_pipez((ac - 1), av, envp, pp[1]);
	}
	if (pp[1] != -1)
		close(pp[1]);
	cmd = ft_getcmd(av[ac], envp);
	return (ft_do_exec(cmd, pp[0], fd_write, envp));
}

int	main(int ac, char **av, char **envp)
{
	int	fd_out;
	int	error;

	fd_out = ft_pipez_check_acav(ac, av);
	if (fd_out == -1)
		return (1);
	error = ft_pipez((ac - 1), av, envp, fd_out);
	close(fd_out);
	if (!ft_strncmp("here_doc", av[1], 9))
		unlink("/tmp/ggiannit_ugly_pipex");
	return (error);
}
