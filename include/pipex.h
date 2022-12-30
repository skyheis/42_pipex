/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:55:24 by ggiannit          #+#    #+#             */
/*   Updated: 2022/12/30 12:41:43 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

/* pipex_utils */
char	**ft_getcmd(char *cmd_str, char **envp);

/* handle_fd_utils */
int		ft_close_4(int fd1, int fd2, int fd3, int fd4);
void	ft_redirect(int fd_in, int fd_out, int pp_close);

#endif
