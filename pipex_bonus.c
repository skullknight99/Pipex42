/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acmaghou <muteallfocus7@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 17:09:55 by acmaghou          #+#    #+#             */
/*   Updated: 2022/02/25 18:17:52 by acmaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	out_process(char *av, char *outfile, char *cmd, char **envp)
{
	int		fd;
	int		execstat;
	char	*path;

	fd = 0;
	if (check_here_doc(av))
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		puterror("Infile Error ");
	dup2(fd, STDOUT_FILENO);
	path = find_path(envp, cmd);
	if (!path)
		puterror("Command not found ");
	execstat = execve(path, ft_split(cmd, ' '), envp);
	if (execstat == -1)
		puterror("Execve Error command failed/not found ");
}

static void	in_process(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
		puterror("Infile Error ");
	dup2(fd, STDIN_FILENO);
}

static void	do_pipe(char *cmd, char **envp)
{
	int		fds[2];
	int		pid;
	char	*path;

	if (pipe(fds) == -1)
		puterror("Pipe Error ");
	pid = fork();
	if (pid == -1)
		puterror("Fork Error ");
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		path = find_path(envp, cmd);
		if (!path || execve(path, ft_split(cmd, ' '), envp) == -1)
			puterror("Execve Error command failed/not found ");
		waitpid(-1, 0, 0);
	}
	else
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
	}
}

void	listen(char *limiter)
{
	char	*line;
	int		fds[2];
	int		pid;
	int		len;

	if (pipe(fds) == -1)
		puterror("Pipe Error ");
	pid = fork();
	line = NULL;
	if (pid == 0)
	{
		len = ft_strlen(limiter);
		write_line(fds, line, limiter, len);
	}
	else
	{
		dup2(fds[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
	close(fds[0]);
	close(fds[1]);
}

int	main(int ac, char **av, char **envp)
{
	int		index;
	int		check_doc;

	if (ac < 5)
	{
		ft_putstr_fd("Usage: ./pipex filein cmd1 cmd2 cmdN ... fileout\n", 2);
		ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmdN ... fileout\n", 2);
		return (0);
	}
	index = 2;
	check_doc = check_here_doc(av[1]);
	if (check_doc)
	{
		listen(av[2]);
		index = 3;
	}
	else
		in_process(av[1]);
	while (index < ac - 2)
		do_pipe(av[index++], envp);
	out_process(av[1], av[ac - 1], av[ac - 2], envp);
	return (0);
}
