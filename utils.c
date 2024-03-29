/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/16 10:30:22 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_is_quoted(char *c, int i)
{
	static int	squote;
	static int	dquote;

	if (!c)
	{
		squote = 0;
		dquote = 0;
	}
	else
	{
		if (c[i] == '\'' && !dquote) // not_escaped(c, i) && 
			squote = !squote;
		else if (c[i] == '\"' && !squote) // not_escaped(c, i) && 
			dquote = !dquote;
		if (dquote)
			return (2);
		if (squote)
			return (1);
	}
	return (0);
}
