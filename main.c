/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:57:39 by ggiannit          #+#    #+#             */
/*   Updated: 2023/01/04 14:31:07 by ggiannit         ###   ########.fr       */
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
		perror("I guess it doesn't exist.. am I right? command not found");
		ft_close_n_ret(fd_in, fd_out, -1, -2);
		exit(127);
	}
	ft_close_n_ret(fd_in, fd_out, -1, -2);
	if (ft_strncmp("cat", &(cmd[0][ft_strlen(cmd[0]) - 3]), 4))
		wait(&stat);
	else
		waitpid(pid, &stat, WNOHANG);
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
	int	is_here;

	if (ac < 5)
		return (1);
	is_here = ft_strncmp("here_doc", av[1], 9);
	if (!is_here && ac < 6)
		return (1);
	if (!is_here)
		fd_out = open(av[--ac], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open(av[--ac], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_out == -1)
		return (2);
	error = ft_pipez((ac - 1), av, envp, fd_out);
	close(fd_out);
	if (!is_here)
		unlink("/tmp/ggiannit_ugly_pipex");
	return (error);
}
