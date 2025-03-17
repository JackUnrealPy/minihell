/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:37:05 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/02/01 17:16:38 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	cmd_init(int argc, char *argv[], t_hell *data)
{
	data->cmd = NULL;
	data->path = NULL;
	data->input_redir = NULL;
	data->output_redir = NULL;
	data->append = NULL;
    // if (data->input_redir)
	// data->input_fd = open(argv[1], O_RDONLY);
	// if (data->input_fd < 0)
	// 	perror(argv[1]);
	// // if (append)
	// // 	data->output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	// else
	// 	data->output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// if (data->output_fd < 0)
	// {
	// 	perror(argv[argc - 1]);
	// 	close(data->input_fd);
	// 	free_struct(data, 1);
	// }
}

int	single_cmd(char **argv, t_hell *data)
{
	data->cmd = ft_split(argv[1], ' ');
	if (!data->cmd || data->cmd[0] == NULL)
		return(1);
	if (ft_strncmp(data->cmd[0], "/bin/", 5) == 0 || ft_strncmp(data->cmd[0], "/usr/bin/", 9) == 0 || ft_strncmp(data->cmd[0], "../", 3) == 0)
		data->path = ft_strdup(data->cmd[0]);
	else
		data->path = ft_strjoin("/bin/", data->cmd[0]);
	if (!data->path)
		return(ft_freedata(data->cmd), 1);
	if (access(data->path, R_OK | X_OK) == -1)
		perror(data->cmd[0]);
}

void	cmd_exec(t_hell *data, char *argv[], char *envp[])
{
	int status;
	single_cmd(argv, data);
	data->pid = fork();
	if (data->pid == 0)
	{
		execve(data->path, data->cmd, envp);
		exit(0);
	}
	waitpid(data->pid, &status, 0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_hell	*data;
	int		i;
	if (determine_builtin(argv, envp) == 1)
		return(0);
	data = malloc(sizeof(t_hell));
	if (!data)
		exit(errno);
	cmd_init(argc, argv, data);
	cmd_exec(data, argv, envp);
	ft_freedata(data->cmd);
	free(data->path);
	free(data);
}
