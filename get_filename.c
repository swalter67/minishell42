/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_filename.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/16 13:04:29 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **pop_names_from_sep(t_data *param, int i, char **sep)
{
    char    *cmd_cpy;
    char    **fname_matrix;
    char    **cmd_split;
    int     j;

    cmd_cpy = param->cmds[i];
    //f//printf(stderr, "[pop_name_from_sep] cmd_split, i = %d\n", i);
    cmd_split = ft_split_multistrsep(cmd_cpy, sep, 1);
    print_tab(cmd_split);
    j = 1;
    fname_matrix = NULL;
    if (cmd_split && cmd_split[j])
    {
	//f//printf(stderr, "cmd_split, i = %d\n", i);
	//print_tab(cmd_split);
        while (cmd_split[j])
        {
            fname_matrix = ft_append_tab(fname_matrix, pop_first_wd(&cmd_split[j++]));
        }
        if (param->input_cleaned)
            free(param->input_cleaned);
        param->input_cleaned = matrix_to_str(cmd_split);
	    //printf(stderr, "[input_cleaned in pop_manes_from_sep] %s\n", param->input_cleaned);
        ft_free_split(cmd_split);
    }
    else
    {
        if (param->input_cleaned)
        {
            free(param->input_cleaned);
            param->input_cleaned = NULL;
        }
        param->input_cleaned = matrix_to_str(cmd_split);
	    //printf(stderr, "[input_cleaned in pop_manes_from_sep] %s\n", param->input_cleaned);
        ft_free_split(cmd_split);

    }
    return (fname_matrix);
}
