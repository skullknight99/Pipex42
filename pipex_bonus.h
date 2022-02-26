/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acmaghou <muteallfocus7@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:23:40 by acmaghou          #+#    #+#             */
/*   Updated: 2022/02/25 18:18:01 by acmaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"
# include "get_next_line.h"

void	puterror(char *str);
char	*find_path(char **envp, char *cmd);
int		check_here_doc(char *av);
void	write_line(int *fds, char *line, char *limiter, int len);

#endif
