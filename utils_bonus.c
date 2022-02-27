/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acmaghou <muteallfocus7@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:10:24 by acmaghou          #+#    #+#             */
/*   Updated: 2022/02/26 18:38:14 by acmaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	puterror(char *str)
{
	ft_putstr_fd("\033[0;31m", 2);
	perror(str);
	ft_putstr_fd("\033[0m", 2);
	exit(-1);
}

char	*find_path(char **envp, char *cmd)
{
	char	**paths;
	char	*cmd_path;
	char	*sub;
	char	**str;

	str = ft_split(cmd, ' ');
	cmd = ft_strdup(*str);
	while (*envp && ft_memcmp(*envp, "PATH=", 5) != 0)
		envp++;
	if (!*envp)
		return (NULL);
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

void	write_line(int *fds, char *line, char *limiter, int len)
{
	while (1)
	{
		line = get_next_line(0);
		if (!ft_strncmp(limiter, line, len) && (line[len] == '\n'))
			exit(-1);
		write(fds[1], line, ft_strlen(line));
	}
}

int	check_here_doc(char *av)
{
	if (!ft_strncmp(av, "here_doc", 8))
		return (1);
	return (0);
}
