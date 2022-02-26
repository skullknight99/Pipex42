/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acmaghou <muteallfocus7@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 17:09:55 by acmaghou          #+#    #+#             */
/*   Updated: 2022/02/26 14:33:53 by acmaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	puterror(char *str)
{
	ft_putstr_fd("\033[0;31m", 2);
	perror(str);
	ft_putstr_fd("\033[0m", 2);
	exit(-1);
}

static char	*find_path(char **envp, char *cmd)
{
	char	**paths;
	char	*cmd_path;
	char	*sub;
	char	**str;

	str = ft_split(cmd, ' ');
	cmd = ft_strdup(*str);
	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	sub = ft_substr(*envp, 5, ft_strlen(*envp) - 5);
	paths = ft_split(sub, ':');
	free(sub);
	sub = ft_strjoin("/", cmd);
	cmd_path = check_paths(paths, sub);
	free(cmd);
	free(sub);
	free_all(str);
	free_all(paths);
	return (cmd_path);
}

static void	out_process(int fds[2], char *outfile, char *cmd, char **envp)
{
	int		fd;
	int		pid;
	char	*path;
	char	**str;

	str = ft_split(cmd, ' ');
	pid = fork();
	check_pid(pid);
	if (pid == 0)
	{
		path = find_path(envp, cmd);
		if (!path)
			puterror("Command not found ");
		close(fds[1]);
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		check_fd(fd);
		dup2(fds[0], STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		execute_cmd(path, str, envp);
		free_all(str);
		free(path);
	}
}

static void	in_process(int fds[2], char *infile, char *cmd, char **envp)
{
	int		fd;
	int		pid;
	char	*path;
	char	**str;

	str = ft_split(cmd, ' ');
	pid = fork();
	check_pid(pid);
	if (pid == 0)
	{
		close(fds[0]);
		fd = open(infile, O_RDONLY);
		check_fd(fd);
		dup2(fds[1], STDOUT_FILENO);
		dup2(fd, STDIN_FILENO);
		path = find_path(envp, cmd);
		if (!path)
			puterror("Command not found ");
		execute_cmd(path, str, envp);
		free_all(str);
		free(path);
		exit(1);
	}
}

int	main(int ac, char **av, char **envp)
{
	int	fds[2];

	if (ac != 5)
	{
		ft_putstr_fd("Usage: ./pipex filein cmd1 cmd2 fileout\n", 2);
		return (0);
	}
	if (pipe(fds) == -1)
		puterror("Pipe Error ");
	in_process(fds, av[1], av[2], envp);
	out_process(fds, av[4], av[3], envp);
	close(fds[0]);
	close(fds[1]);
	waitpid(-1, 0, 0);
	return (0);
}
