/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:57:39 by ggiannit          #+#    #+#             */
/*   Updated: 2023/01/03 18:12:33 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_get_heredoc(char *delimiter)
{
	char	*nline;
	size_t	delimiter_size;
	int		fd_gg;

	unlink("/tmp/ggiannit_ugly_pipex");
	fd_gg = open("/tmp/ggiannit_ugly_pipex",
			O_WRONLY | O_CREAT , 0644);
	delimiter_size = ft_strlen(delimiter) + 1;
	ft_putstr_fd("pipe heredoc> ", 1);
	delimiter = ft_strjoin(delimiter, "\n");
	nline = get_next_line(0);
	while (ft_strncmp(delimiter, nline, delimiter_size))
	{
		ft_putstr_fd(nline, fd_gg);
		ft_free_null(&nline);
		ft_putstr_fd("pipe heredoc> ", 1);
		while (!nline)
			nline = get_next_line(0);
	}
	close(fd_gg);
	ft_free_null(&nline);
	ft_free_null(&delimiter);
	return (open("/tmp/ggiannit_ugly_pipex", O_RDONLY));
}

int	ft_do_exec(char **cmd, int fd_in, int fd_out)
{
	if (!fork())
	{
		ft_redirect(fd_in, fd_out, -1);
		execve(cmd[0], cmd, NULL);
		perror("I guess it doesn't exist.. am I right? command non found");
		close(fd_in);
		close(fd_out);
		exit(2);
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
	else if (ac == 3 && !ft_strncmp("here_doc", av[1], 9))
	{
		pp[1] = -1;
		pp[0] = ft_get_heredoc(av[2]);
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
	if (!error)
		return (3);
	return (0);
}
