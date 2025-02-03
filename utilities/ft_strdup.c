/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoayedde <yoayedde@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-23 00:59:34 by yoayedde          #+#    #+#             */
/*   Updated: 2025-01-23 00:59:34 by yoayedde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_utils.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dup;

	len = (ft_strlen(s1) + 1);
	dup = (char *)malloc(len * sizeof(char));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s1, len);
	return (dup);
}
