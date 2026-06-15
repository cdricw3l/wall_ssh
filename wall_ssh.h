/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_ssh.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 19:23:01 by cebouhad          #+#    #+#             */
/*   Updated: 2026/06/15 19:26:25 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALL_SSH_H
# define WALL_SSH_H

# include <sys/types.h>
# include <dirent.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <assert.h>
# include <ctype.h>
# include <sys/wait.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# define PATH "/dev/pts/"
//#define SCRIPT_PATH "/root/./monitoring.sh"
# define SCRIPT_PATH "./monitoring.sh"
# define OK 0
# define ERR 1
# define PTS_SIZE 512

void	*ft_split_clean(char ***split);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *restrict dst,
			const char *restrict src, size_t dstsize);

#endif