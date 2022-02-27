/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acmaghou <muteallfocus7@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 17:09:55 by acmaghou          #+#    #+#             */
/*   Updated: 2022/02/26 18:45:02 by acmaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
/*
opens the output file, based on 2 uses (here_doc or multiple pipes)
and makes it the STDOUT , execve executes the cmd if it exists
then exits the line of execution resulting in the end of the program,
if thats not the case then we free the command paths and the 2d array
that contains the commands + their options then and only then it exits
through the put error function.
*/
void	out_process(char *av, char *outfile, char *cmd, char **envp)
{
	int		fd;
	char	*path;
	char	**str;

	str = ft_split(cmd, ' ');
	fd = 0;
	path = find_path(envp, cmd);
	if (!path)
		puterror("Command not found ");
	if (check_here_doc(av))
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	check_fd(fd);
	dup2(fd, STDOUT_FILENO);
	execve(path, ft_split(cmd, ' '), envp);
	free_all(str);
	free(path);
	puterror("Execve Error command failed/not found ");
}
// function responsible of opening the infile and making it work as STDIN
static void	in_process(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
		puterror("Infile Error ");
	dup2(fd, STDIN_FILENO);
}
/* 
Takes given command and inside the child process (result of piping the file descriptors) 
executes it resulting in finishing the child process and beginning of parent process
that closes the writing pipe (since it has already been used)
and duplicates the reading end in order to use it as input for next command.
*/
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
	if (pid == 0) //child process
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		path = find_path(envp, cmd);
		//if we fail to find path for example the "lsd" command
		//will be tested on all paths for example /usr/bin/lsd
		//if not found then it returns NULL.
		//i think we can shorten this code a bit more.
		if (!path || execve(path, ft_split(cmd, ' '), envp) == -1)
			puterror("Execve Error command failed/not found ");
		waitpid(-1, 0, 0);
	}
	else
	{
		close(fds[1]); //close writing end
		dup2(fds[0], STDIN_FILENO); //fds[0] now does same job as STDIN_FILENO
		// basically next command will take the output of this command as input
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
	//in case of multiple pipes index = 2, so we start the do_pipe command from cmd1
	//example : ./pipex infile cmd1 cmd2 ... cmdn outfile
	//in here_doc case we start at index=3 so we skip the limiter and start at cmd1
	//example: ./pipex here_doc limiter cmd1 cmd2 outfile
	while (index < ac - 2)
		do_pipe(av[index++], envp);
	//function responsible of opening and writing to the outfile
	out_process(av[1], av[ac - 1], av[ac - 2], envp);
	return (0);
}
