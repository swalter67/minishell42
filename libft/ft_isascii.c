/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:48:16 by supersko          #+#    #+#             */
/*   Updated: 2022/08/16 12:48:19 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
/*
//
#include "error_msg.h"
#include <ctype.h>
#include <stdio.h>
// MAIN
int	main(int argc, char *argv[])
{
	int	ii;

	ii = -1;
	while (ii < 257)
	{
		if (isascii(ii) != ft_isascii(ii))
		{
			f//printf(stderr, "isascii(%c) = %d\n", (char)ii, isascii(ii));
			f//printf(stderr, "ft_isascii(%c) = %d\n", (char)ii, ft_isascii(ii));
			return (error_msg(ii, "isascii"));
		}
		ii++;
	}
	(void)argc;
	f//printf(stderr, "%s have same output from same input\n", argv[0]);
	return (0);
}
*/
