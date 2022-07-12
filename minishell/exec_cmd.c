/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/07/11 17:51:43 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// getenv output cannot be free (not malloc)
// return NULL if path doesn't exist
char	*get_path(char *cmd)
{
	char	*str;
	char	**env_tab;
	int		i;
	int		cmd_len;
	int		file_fd;

	if ((file_fd = open(cmd, O_RDONLY)) != -1)
	{
		close(file_fd);
		return (ft_strdup(cmd));
	}
	str = getenv("PATH");
	env_tab = ft_split(str, ':');
	i = 0;
	cmd = ft_strjoin("/", cmd);
	cmd_len = ft_strlen(cmd);
	while (env_tab[i])
	{
		str = ft_strjoin(env_tab[i], cmd);
		file_fd = open(str, O_RDONLY);
		//fprintf(stderr, "[output]: %d\n", file_fd);
		if (file_fd != -1)
			break ;
		close(file_fd);
		//free(env_tab[i]);
		i++;
		free(str);
		str = NULL;
	}
	close(file_fd);
	ft_free_split(env_tab);
	free(cmd);
	return (str);
}

int	quote_empty(char *first_quote)
{
	if (first_quote)
	{
		if (first_quote[0] == first_quote[1])
			return (1);
		else if (first_quote[0] && first_quote[1])
			return (0);
	}
	return (-1);
}

/* spaces num if not quoted */
int	line_presplit(char *cmd)
{
	int	quote;
	int	i;
	int	tab_len;
	int	last_quote;

	ft_is_quoted(NULL, 0);
	last_quote = 0;
	quote = 0;
	i = 0;
	tab_len = 1;
	while (cmd[i])
	{
		if ((quote = ft_is_quoted(cmd, i)) != last_quote)
		{
			cmd[i] = '\0';
			tab_len++;
			last_quote = quote;
		}
		if (cmd[i] == ' ' && !quote && tab_len++)
			cmd[i] = '\0';
		i++;
	}
	return (tab_len);
}

char	**split_formated(t_cmd_tree *node)
{
	int 	i;
	int 	new_i;
	char	*cmd_path;
	char	**cmd_split;

	cmd_split = quotes_spaces_split(node->data);
	if (!cmd_split)
		return (NULL);
	new_i = 0;
	i = 0;
	while (cmd_split[i])
	{
		if (*cmd_split[i] != '\0')
		{
			if (i != new_i)
				cmd_split[new_i] = cmd_split[i];
			new_i++;
		}
		else
			free(cmd_split[i]);
		i++;
	}
	cmd_split[new_i] = NULL;
	cmd_path = get_path(cmd_split[0]);
	free(cmd_split[0]);
	cmd_split[0] = cmd_path;
	return (cmd_split);
}

char	**quotes_spaces_split(char *line)
{
	int		i;
	int		nb_split;
	int		next;
	char	**tab;

	nb_split = line_presplit(line);
	tab = malloc(sizeof(char *) * (nb_split + 1));
	i = 0;
	next = 0;
	while (i < nb_split)
	{
		tab[i] = ft_strdup(&line[next]);
		next += ft_strlen(&line[next]) + 1;
		//tmp = fprintf(stderr, "%s\n", &line[next]);
		i++;
	}
	tab[i] = NULL;
	free(line);
	return (tab);
}

void	node_cmd(t_cmd_tree *node)
{
	char	**cmd_split;

	if (node && node->data && !ft_is_operand(node->data))
	{
		cmd_split = split_formated(node);
		if (!cmd_split)
			cmd_split = ft_split ("/usr/bin/cat,command not found\n", ',');
		if (execve(cmd_split[0], cmd_split, *node->envp) == -1)
		{
			perror(NULL);
		}
		ft_free_split(cmd_split);
		
	}
}