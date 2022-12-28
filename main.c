/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:57:39 by ggiannit          #+#    #+#             */
/*   Updated: 2022/12/28 20:55:32 by ggiannit         ###   ########.fr       */
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

char *ft_getenv(char *to_get, char **envp)
{
	int	i;
	int len;

	i = 0;
	while (envp[i])
	{
		len = ft_strlen(to_get);
		if (!ft_strncmp(to_get, envp[i], len) && envp[i][len] == '=')
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	return(&envp[i][len + 1]);
}

char *ft_free_matrix(char **matrix)
{
	int i;

	i = 0;
	while (matrix[i])
		ft_free_null(&matrix[i++]);
	free(matrix);
	return (NULL);
}

char *ft_getpath(char *full_path, char *cmd)
{
	int		i;
	char	**path_mat;
	char	*exec_path;

	i = 0;
	path_mat = ft_split(full_path, ':');
	while (path_mat[i])
	{
		full_path = ft_strjoin("/", cmd);
		exec_path = ft_strjoin(path_mat[i], full_path);
		ft_free_null(&full_path);
		if (!access(exec_path, X_OK))
			break ;
		ft_free_null(&exec_path);
		i++;
	}
	if (!path_mat[i])
		return (ft_free_null(&exec_path));
	ft_free_matrix(path_mat);
	return (exec_path);
}

char **ft_getcmd(char *cmd_str, char **envp)
{
	char **cmd_mat;
	char *full_path;

	cmd_mat = ft_split(cmd_str, ' ');
	full_path = ft_getenv("PATH", envp);
	full_path = ft_getpath(full_path, cmd_mat[0]);
	if (!full_path)
		return ((char **) ft_free_matrix(cmd_mat));
	ft_free_null(&cmd_mat[0]);
	cmd_mat[0] = full_path;
	return (cmd_mat);
}

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

void ft_redirect(int fd_in, int fd_out, int pp_close)
{
	if (fd_in != -1)
		dup2(fd_in, 0);
	if (fd_out != -1)
		dup2(fd_out, 1);
	if (pp_close != -1)
		close(pp_close);
}

int	main(int ac, char **av, char **envp)
{
	int	pp[2];
	int	fd_in;
	int	fd_out;
	char **cmd;

	if (ac < 4)
		return (1);
	pipe(pp);
	if(!fork())
	{
		cmd = ft_getcmd(av[2], envp);
		if (!fork())
		{
			//ft_redirect(fd_in, pp[1], pp[0]);
			fd_in = open(av[1], O_RDONLY);
			dup2(fd_in, 0);
			dup2(pp[1], 1);
			close(pp[0]);
			execve(cmd[0], cmd, NULL);
			close(pp[1]);
			close(fd_in);
		}
		wait(NULL);
		ft_free_matrix(cmd);
	}
	else
	{
		wait(NULL);
		cmd = ft_getcmd(av[3], envp);
		if (!fork())
		{
			//ft_redirect(pp[0], fd_out, pp[1]);
			fd_out = open(av[4], O_WRONLY);
			dup2(pp[0], 0);
			dup2(fd_out, 1);
			close(pp[1]);
			execve(cmd[0], cmd, NULL);
			close(pp[0]);
			close(fd_out);
		}
		close(pp[0]);
		close(pp[1]);
		wait(NULL);
		ft_free_matrix(cmd);
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
