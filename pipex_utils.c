/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acmaghou <muteallfocus7@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:21:17 by acmaghou          #+#    #+#             */
/*   Updated: 2022/02/26 18:33:02 by acmaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*check_paths(char **paths, char *sub)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], sub);
		if (!cmd_path)
			return (NULL);
		if (!access(cmd_path, F_OK))
			break ;
		free(cmd_path);
		i++;
	}
	if (!paths[i])
		return (NULL);
	return (cmd_path);
}

void	check_fd(int fd)
{
	if (fd == -1)
		ft_putstr_fd("Pipe Error ", 2);
}

void	check_pid(int pid)
{
	if (pid == -1)
		ft_putstr_fd("Fork Error ", 2);
}
