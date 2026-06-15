/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 19:24:17 by cebouhad          #+#    #+#             */
/*   Updated: 2026/06/15 19:24:19 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall_ssh.h"

void	*ft_split_clean(char ***split)
{
	char	**ptr;

	if (!(*split))
		return (NULL);
	ptr = *split;
	while (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
		ptr++;
	}
	free(*split);
	return (NULL);
}
