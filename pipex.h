/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acmaghou <muteallfocus7@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:23:10 by acmaghou          #+#    #+#             */
/*   Updated: 2022/02/26 13:18:44 by acmaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"

void	free_all(char **str);
void	puterror(char *str);
char	*check_paths(char **paths, char *sub);
void	check_fd(int fd);
void	check_pid(int pid);
void	execute_cmd(char *path, char **str, char **envp);

#endif
