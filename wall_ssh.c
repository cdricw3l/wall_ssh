/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_ssh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 18:43:43 by cebouhad          #+#    #+#             */
/*   Updated: 2026/06/15 19:39:51 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall_ssh.h"

int	get_fd(char *pts)
{
	int	fd;

	fd = open(pts, O_RDWR);
	if (fd < 1)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}

int	check_pts_name(char *pts)
{
	while (*pts)
	{
		if (!isdigit(*pts))
			return (ERR);
		pts++;
	}
	return (OK);
}

int	exec_prog(int fd)
{
	pid_t	f;
	int		status;
	char	*arg[2];

	f = fork();
	if (f < 0)
	{
		perror("fork");
		return (ERR);
	}
	if (f == 0)
	{
		dup2(fd, STDOUT_FILENO);
		write (fd, "\n", 1);
		arg[0] = "monitoring";
		arg[1] = NULL;
		if (execve(SCRIPT_PATH, arg, NULL) < 0)
		{
			perror("Excve");
			exit(errno);
		}
	}
	waitpid(f, &status, 0);
	return (OK);
}

char	**get_pts(void)
{
	char			**arr;
	DIR				*dir;
	struct dirent	*d;
	int				i;

	dir = opendir(PATH);
	if (!dir)
	{
		perror("open_dir");
		return (NULL);
	}
	i = 0;
	arr = malloc(sizeof(char *) * (PTS_SIZE + 1));
	if (!arr)
		return (NULL);
	while ((d = readdir(dir)) != NULL)
	{
		if (check_pts_name(d->d_name) == OK)
			arr[i++] = ft_strjoin(PATH, d->d_name);
	}
	arr[i] = NULL;
	closedir(dir);
	return (arr);
}

int	main(void)
{
	char			**pts;
	int				fd;
	int				i;

	i = 0;
	
	pts = get_pts();
	while (pts[i])
	{
		fd = get_fd(pts[i]);
		if (fd < 0)
		{
			printf("ERROR\n");
			ft_split_clean(&pts);
			return (ERR); 
		}
		exec_prog(fd);
		write(fd, "\n", 1);
		close(fd);
		free(pts[i]);
		i++;
	}
	free(pts);
	return (0);
}
