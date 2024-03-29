#include "minishell.h"

static void	set_pipe_args(t_data *param, int i)
{
	char	**aux;
	int		j;
	int		k;

	j = 0;
	while (param->argv[i + j] && ft_memcmp(param->argv[i + j], "|", 2))
		j++;
	aux = (char **)ft_calloc(sizeof(char *), j + 1);
	k = -1;
	while (++k < j)
		aux[k] = ft_strdup(param->argv[i + k]);
	param->argv = aux;
	param->argc = j;
}

static void	pipe_son(int *flag, int *fds, t_data *param, int pos)
{
	int		i;
	int		argc;
	char	**argv;

	//signal(SIGINT, child_sig_handler);
	if (!fork())
	{
		if (!flag[0])
			dup2(fds[0], 0);
		if (!flag[1])
			dup2(fds[3], 1);
		i = 0;
		while (i < 4)
			close(fds[i++]);
		argc = param->argc;
		argv = param->argv;
		set_pipe_args(param, pos);
		//check_command(param->str, param);
		free_matrix(param->argv);
		param->argc = argc;
		param->argv = argv;
		exit(param->retour);
	}
}

static void	switch_pipes(int *fds)
{
	close(fds[0]);
	close(fds[1]);
	fds[0] = fds[2];
	fds[1] = fds[3];
	pipe(fds + 2);
}

static int	check_pipe(int *fds, t_data *param)
{
	int		sons;
	int		*flag;
	int		i;
	int		j;

	sons = 0;
	flag = (int *)malloc(sizeof(int) * 2);
	flag[0] = 1;
	flag[1] = 0;
	j = 0;
	while (param->argv[j])
	{
		i = 0;
		while (param->argv[j + i] &&
			   ft_memcmp(param->argv[j + i], "|", 2))
			i++;
		flag[1] = (!param->argv[i + j]) ? 1 : 0;
		pipe_son(flag, fds, param, j);
		sons++;
		flag[0] = 0;
		switch_pipes(fds);
		j += !param->argv[j + i] ? i : i + 1;
	}
	free(flag);
	return (sons);
}

void		command_or_pipe(t_data *param, int j)
{
	int fds[4];
	int std_out;
	int sons;
	int i;

	std_out = dup(0);
	i = 0;
	while (param->argv[i] && ft_memcmp(param->argv[i], "|", 2))
		i++;
	if (!param->argv[i])
		//param->envp = check_command(param->cmds[j], param);
		//printf("check_command");
	else if (param->cmds[j])
	{
		pipe(fds);
		pipe(fds + 2);
		sons = check_pipe(fds, param);
		while (sons-- > 0)
			wait(&param->retour);
		param->retour /= 256;
		i = -1;
		while (++i < 4)
			close(fds[i]);
	}
	dup2(std_out, 0);
}

