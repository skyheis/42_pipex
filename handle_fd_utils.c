/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:39:48 by ggiannit          #+#    #+#             */
/*   Updated: 2023/01/04 21:38:03 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_fd_in_check(int fd_in, char *file)
{
	if (fd_in == -1)
		printf("ggianit: no such file or directory: %s\n", file);
	else
	{
		close(fd_in);
		fd_in = 0;
	}
	return (fd_in);
}

int	ft_pipez_check_acav(int ac, char **av)
{
	int	is_here;
	int	fd_out;
	int	in_status;

	if (ac < 5)
		return (-1);
	is_here = ft_strncmp("here_doc", av[1], 9);
	if (!is_here && ac < 6)
		return (-1);
	if (!is_here)
	{
		in_status = ft_fd_in_check(open(av[2], O_RDONLY), av[2]);
		fd_out = open(av[--ac], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		in_status = ft_fd_in_check(open(av[1], O_RDONLY), av[1]);
		fd_out = open(av[--ac], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	if (in_status == -1)
		return (-1);
	return (fd_out);
}

int	ft_close_n_ret(int fd1, int fd2, int fd3, int ret_num)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	if (fd3 != -1)
		close(fd3);
	if (ret_num == -2)
		return (0);
	return (ret_num);
}

void	ft_redirect(int fd_in, int fd_out, int pp_close)
{
	if (fd_in != -1)
		dup2(fd_in, 0);
	if (fd_out != -1)
		dup2(fd_out, 1);
	if (pp_close != -1)
		close(pp_close);
}
