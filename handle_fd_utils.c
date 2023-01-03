/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:39:48 by ggiannit          #+#    #+#             */
/*   Updated: 2023/01/03 21:52:31 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_close_n_ret(int fd1, int fd2, int fd3, int ret_num)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	if (fd3 != -1)
		close(fd3);
	if (ret_num != -2)
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
